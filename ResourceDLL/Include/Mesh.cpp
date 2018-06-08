#include "Mesh.h"


C_Mesh::C_Mesh():m_pMesh(NULL),m_pSubsetBuff(NULL),m_pSubsets(NULL),
	m_dwSubsetCnt(0),m_pTextures(NULL),m_pMtrls(NULL)
{

}


C_Mesh::~C_Mesh()
{
}

void C_Mesh::Release()
{
	if(m_pMesh)
	{
		m_pMesh->Release();
		m_pMesh=NULL;
	}
	if (m_pSubsets)
	{
		m_pSubsets=NULL;
	}
	if (m_pSubsetBuff)
	{
		m_pSubsetBuff->Release();
		m_pSubsetBuff=NULL;
	}
	if (m_pTextures)
	{
		for (DWORD i=0;i<m_dwSubsetCnt;i++)
		{
			m_pTextures[i]->Release();
		}
		delete [] m_pTextures;
		m_pTextures=NULL;
	}
	if (m_pMtrls)
	{
		delete [] m_pMtrls;
		m_pMtrls=NULL;
	}
}

HRESULT C_Mesh::CloneMesh( LPDIRECT3DDEVICE9 pDevice , C_AnimationCtrl** ppAniCtrl )
{
	return S_OK;
}

LPD3DXMESH C_Mesh::GetMesh()
{
	return m_pMesh;
}
