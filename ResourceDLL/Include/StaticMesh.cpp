#include "StaticMesh.h"


C_StaticMesh::C_StaticMesh():C_Mesh()
{
}


C_StaticMesh::~C_StaticMesh()
{
}

HRESULT C_StaticMesh::InitMesh( LPDIRECT3DDEVICE9 pDevice, const TCHAR* pPath, const TCHAR* pFileName )
{
	TCHAR		szPath[128] = L"";

	lstrcpy(szPath, pPath);
	lstrcat(szPath, pFileName);

	if(FAILED(D3DXLoadMeshFromX(szPath, D3DXMESH_MANAGED, pDevice, NULL
		, &m_pSubsetBuff, NULL, &m_dwSubsetCnt, &m_pMesh)))
	{
		return E_FAIL;
	}

	m_pSubsets = (D3DXMATERIAL*)m_pSubsetBuff->GetBufferPointer();

	m_pTextures = new LPDIRECT3DTEXTURE9[m_dwSubsetCnt];

	m_pMtrls = new D3DMATERIAL9[m_dwSubsetCnt];

	
	TCHAR		szBuff[128] = L"";

	for (DWORD i = 0; i < m_dwSubsetCnt; ++i)
	{
		m_pMtrls[i] = m_pSubsets[i].MatD3D;

		lstrcpy(szPath, pPath);

		MultiByteToWideChar(CP_ACP, 0, m_pSubsets[i].pTextureFilename
			, strlen(m_pSubsets[i].pTextureFilename)
			, szBuff, 128);

		lstrcat(szPath, szBuff);
		
		if(FAILED(D3DXCreateTextureFromFile(pDevice, szPath, &m_pTextures[i])))
			return E_FAIL;
	}
	return S_OK;	
}

void C_StaticMesh::Release()
{
	C_Mesh::Release();
}

void C_StaticMesh::Render( LPDIRECT3DDEVICE9 pDevice , const BONE* pRootBone /*= NULL*/ )
{
	for (DWORD i = 0; i < m_dwSubsetCnt; ++i)
	{
		pDevice->SetTexture(0, m_pTextures[i]);
		pDevice->SetMaterial( &m_pMtrls[i]);
		m_pMesh->DrawSubset(i);
	}
}
