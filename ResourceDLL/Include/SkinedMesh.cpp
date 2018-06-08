#include "SkinedMesh.h"


C_SkinedMesh::C_SkinedMesh(void) :C_DynamicMesh()
{
}


C_SkinedMesh::~C_SkinedMesh(void)
{
	Release();
}

HRESULT C_SkinedMesh::InitMesh(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pPathName, const TCHAR* pFileName)
{
	TCHAR szPath[128] = L"";

	lstrcpy(szPath, pPathName);
	lstrcat(szPath, pFileName);

	m_pLoader = new C_HierarchyLoader(pPathName);

	m_pAniCtrl = new C_AnimationCtrl();

	if (FAILED(D3DXLoadMeshHierarchyFromX(szPath, D3DXMESH_MANAGED
		, pDevice, m_pLoader, NULL, &m_pRootBone, m_pAniCtrl->GetAniCtrl())))
		return E_FAIL;

	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);

	UpdateMatrix((BONE*)m_pRootBone, &matrix);

	SetUpBoneMatrixPointer((BONE*)m_pRootBone);

	return S_OK;
}

void C_SkinedMesh::InvalidateMesh(D3DXMATRIX* pMatWorld)
{
	UpdateMatrix((BONE*)m_pRootBone, pMatWorld);
}

void C_SkinedMesh::UpdateMatrix(BONE* pBone, D3DXMATRIX* pParentMatrix)
{

	if (!pBone)
		return;

	D3DXMatrixMultiply(&pBone->matWorld, &pBone->TransformationMatrix
		, pParentMatrix);

	if (pBone->pFrameSibling)
	{
		UpdateMatrix((BONE*)pBone->pFrameSibling
			, pParentMatrix);
	}

	if (pBone->pFrameFirstChild)
	{
		UpdateMatrix((BONE*)pBone->pFrameFirstChild
			, &pBone->matWorld);
	}

}

void C_SkinedMesh::SetUpBoneMatrixPointer(BONE* pBone)
{
	if (pBone->pMeshContainer)
	{
		BONEMESH* pBoneMesh = (BONEMESH*)pBone->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			int nNumBone = pBoneMesh->pSkinInfo->GetNumBones();

			pBoneMesh->ppBoneMatrix = new D3DXMATRIX*[nNumBone]();

			for (int i = 0; i < nNumBone; i++)
			{
				BONE* pLinkedBone = (BONE*)D3DXFrameFind(m_pRootBone, pBoneMesh->pSkinInfo->GetBoneName(i));

				pBoneMesh->ppBoneMatrix[i] = NULL;
				if (pLinkedBone)
					pBoneMesh->ppBoneMatrix[i] = &pLinkedBone->matWorld;
					
			}
		}
	}

	if (pBone->pFrameSibling)
	{
		SetUpBoneMatrixPointer((BONE*)pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		SetUpBoneMatrixPointer((BONE*)pBone->pFrameFirstChild);
	}
}


void C_SkinedMesh::Render(LPDIRECT3DDEVICE9 pDevice, const BONE* pBone /*= NULL*/)
{
	if (!pBone)
		pBone = (BONE*)m_pRootBone;

	if (pBone->pMeshContainer)
	{
		BONEMESH*			pBoneMesh = (BONEMESH*)pBone->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			int		nNumBone = pBoneMesh->pSkinInfo->GetNumBones();

			for (int i = 0; i < nNumBone; ++i)
			{
				D3DXMatrixMultiply(&pBoneMesh->pCurrentBoneMatrix[i]
					, &pBoneMesh->pBoneoffSetMatrix[i]
					, pBoneMesh->ppBoneMatrix[i]);
			}

			BYTE*		pSour;
			BYTE*		pDest;

			pBoneMesh->pOriMesh->LockVertexBuffer(0, (void**)&pSour);

			pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&pDest);

			pBoneMesh->pSkinInfo->UpdateSkinnedMesh(pBoneMesh->pCurrentBoneMatrix
				, NULL, pSour, pDest);

			pBoneMesh->pOriMesh->UnlockVertexBuffer();
			pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();

			for (unsigned long i = 0; i < pBoneMesh->NumMaterials; ++i)
			{
				int		mtrl = pBoneMesh->pAttTable[i].AttribId;

				pDevice->SetMaterial(&pBoneMesh->vecMtrl[mtrl]);
				pDevice->SetTexture(0, pBoneMesh->vecTexture[mtrl]);

				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}
	if (pBone->pFrameSibling)
	{
		Render(pDevice, (BONE*)pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		Render(pDevice, (BONE*)pBone->pFrameFirstChild);
	}
}

void C_SkinedMesh::Release(void)
{
	C_DynamicMesh::Release();
}