#include "HierarchyLoader.h"


C_HierarchyLoader::C_HierarchyLoader(void)
{
	ZeroMemory(m_szPath,sizeof(TCHAR)*128);
}

C_HierarchyLoader::C_HierarchyLoader( const TCHAR* pPath )
{
	lstrcpy(m_szPath,pPath);
}


C_HierarchyLoader::~C_HierarchyLoader(void)
{
}

STDMETHODIMP C_HierarchyLoader::CreateFrame(THIS_ LPCSTR Name, 
	LPD3DXFRAME *ppNewFrame) 
{
	BONE*		pBone = new BONE;
	ZeroMemory(pBone, sizeof(BONE));

	if (Name)
	{
		pBone->Name = new char[strlen(Name) + 1];
		strcpy_s(pBone->Name, strlen(Name) + 1, Name);
	}

	D3DXMatrixIdentity(&pBone->matWorld);
	D3DXMatrixIdentity(&pBone->TransformationMatrix);

	*ppNewFrame = (D3DXFRAME*)pBone;

	return S_OK;
}
STDMETHODIMP C_HierarchyLoader::CreateMeshContainer(THIS_ 
	LPCSTR Name, 
	CONST D3DXMESHDATA *pMeshData, 
	CONST D3DXMATERIAL *pMaterials, 
	CONST D3DXEFFECTINSTANCE *pEffectInstances, 
	DWORD NumMaterials, 
	CONST DWORD *pAdjacency, 
	LPD3DXSKININFO pSkinInfo, 
	LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	BONEMESH*			pBoneMesh = new BONEMESH();
	ZeroMemory(pBoneMesh, sizeof(BONEMESH));

	pBoneMesh->pOriMesh = pMeshData->pMesh;
	pBoneMesh->MeshData.pMesh = pMeshData->pMesh;
	pBoneMesh->MeshData.Type = pMeshData->Type;

	pMeshData->pMesh->AddRef();

	LPDIRECT3DDEVICE9			pDevice = NULL;
	pMeshData->pMesh->GetDevice(&pDevice);

	pBoneMesh->vecMtrl.reserve(NumMaterials);
	pBoneMesh->vecMtrl.resize(NumMaterials);
	pBoneMesh->vecTexture.resize(NumMaterials);
	pBoneMesh->vecTexture.resize(NumMaterials);

	for (unsigned long i = 0; i < NumMaterials; ++i)
	{

		D3DXMATERIAL			Mtrl;
		memcpy(&Mtrl, &pMaterials[i], sizeof(D3DXMATERIAL));
		pBoneMesh->vecMtrl[i] = Mtrl.MatD3D;


		LPDIRECT3DTEXTURE9		pTexture;
		TCHAR			szName[128] = L"";

		if (Mtrl.pTextureFilename)
		{
			TCHAR			szTmp[128] = L"";

			ZeroMemory(szName, sizeof(TCHAR) * 128);

			lstrcpy(szTmp, m_szPath);

			MultiByteToWideChar(CP_ACP, 0, Mtrl.pTextureFilename
				, strlen(Mtrl.pTextureFilename)
				, szName, 128);

			lstrcat(szTmp, szName);

			if (FAILED(D3DXCreateTextureFromFile(pDevice
				, szTmp, &pTexture)))
				return E_FAIL;
			pBoneMesh->vecTexture[i] = pTexture;
		}
	}

	if (pSkinInfo)
	{
		pBoneMesh->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		pMeshData->pMesh->CloneMeshFVF(D3DXMESH_MANAGED
			, pMeshData->pMesh->GetFVF()
			, pDevice
			, &pBoneMesh->MeshData.pMesh);

		pBoneMesh->MeshData.pMesh->GetAttributeTable(NULL, &pBoneMesh->NumMaterials);

		pBoneMesh->pAttTable = new D3DXATTRIBUTERANGE[pBoneMesh->NumMaterials];

		pBoneMesh->MeshData.pMesh->GetAttributeTable(pBoneMesh->pAttTable, NULL);

		int		iNumBone = pSkinInfo->GetNumBones();

		pBoneMesh->pBoneoffSetMatrix = new D3DXMATRIX[iNumBone];
		pBoneMesh->pCurrentBoneMatrix = new D3DXMATRIX[iNumBone];

		for (int i = 0; i < iNumBone; ++i)
		{
			pBoneMesh->pBoneoffSetMatrix[i] = *(pBoneMesh->pSkinInfo->GetBoneOffsetMatrix(i));
		}
	}

	*ppNewMeshContainer = pBoneMesh;

	return S_OK;
}
STDMETHODIMP C_HierarchyLoader::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree)
{
	D3DXFRAME* pSibling = pFrameToFree->pFrameSibling;
	D3DXFRAME* pChild = pFrameToFree->pFrameFirstChild;

	if (pSibling)
	{
		DestroyFrame(pSibling);
	}

	if (pChild)
	{
		DestroyFrame(pChild);
	}

	if (pFrameToFree)
	{
		if (pFrameToFree->pMeshContainer)
		{
			DestroyMeshContainer(pFrameToFree->pMeshContainer);
		}

		delete [] pFrameToFree->Name;
		pFrameToFree->Name = NULL;

		delete [] pFrameToFree;
		pFrameToFree = NULL;
	}
	return S_OK;
}
STDMETHODIMP C_HierarchyLoader::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	BONEMESH* pBoneMesh = (BONEMESH*)pMeshContainerToFree;

	pBoneMesh->vecMtrl.~vector<D3DMATERIAL9>();

	for (DWORD i = 0; i < ((BONEMESH*)pMeshContainerToFree)->vecTexture.size();i++)
	{
		((BONEMESH*)pMeshContainerToFree)->vecTexture[i]->Release();
	}

	pBoneMesh->vecTexture.~vector<LPDIRECT3DTEXTURE9>();


	if(((BONEMESH*)pMeshContainerToFree)->ppBoneMatrix)
	{
		delete [] ((BONEMESH*)pMeshContainerToFree)->ppBoneMatrix;
		((BONEMESH*)pMeshContainerToFree)->ppBoneMatrix = NULL;
	}

	if(((BONEMESH*)pMeshContainerToFree)->pAttTable)
	{
		delete [] ((BONEMESH*)pMeshContainerToFree)->pAttTable;
		((BONEMESH*)pMeshContainerToFree)->pAttTable = NULL;
	}

	if(((BONEMESH*)pMeshContainerToFree)->pBoneoffSetMatrix)
	{
		delete [] ((BONEMESH*)pMeshContainerToFree)->pBoneoffSetMatrix;
		((BONEMESH*)pMeshContainerToFree)->pBoneoffSetMatrix = NULL;
	}

	if(((BONEMESH*)pMeshContainerToFree)->pCurrentBoneMatrix)
	{
		delete [] ((BONEMESH*)pMeshContainerToFree)->pCurrentBoneMatrix;
		((BONEMESH*)pMeshContainerToFree)->pCurrentBoneMatrix = NULL;
	}

	delete pMeshContainerToFree;
	pMeshContainerToFree = NULL;

	return S_OK;
}