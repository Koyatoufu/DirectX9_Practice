#include "DynamicMesh.h"


C_DynamicMesh::C_DynamicMesh():C_Mesh(),m_pLoader(NULL),
	m_pRootBone(NULL),m_pAniCtrl(NULL)
{

}


C_DynamicMesh::~C_DynamicMesh()
{
	Release();
}

void C_DynamicMesh::Release()
{
	if (m_pLoader)
	{
		m_pLoader->DestroyFrame(m_pRootBone);
		delete m_pLoader;
		m_pLoader = NULL;
	}
	if (m_pAniCtrl)
	{
		m_pAniCtrl->Release();
		delete m_pAniCtrl;
		m_pAniCtrl = NULL;
	}
	C_Mesh::Release();
}

HRESULT C_DynamicMesh::InitMesh( LPDIRECT3DDEVICE9 pDevice, const TCHAR* pPath, const TCHAR* pFileName )
{
	return E_FAIL;
}

void C_DynamicMesh::Render( LPDIRECT3DDEVICE9 pDevice , const BONE* pRootBone /*= NULL*/ )
{

}

HRESULT C_DynamicMesh::CloneMesh( LPDIRECT3DDEVICE9 pDevice , C_AnimationCtrl** ppAniCtrl )
{
	*ppAniCtrl = m_pAniCtrl->Clone();

	return S_OK;
}

void C_DynamicMesh::GetBoneMatrix( const CHAR* pBoneName, D3DXMATRIX* pOut )
{
	FindBone(pBoneName,(BONE*)m_pRootBone,pOut);
}

void C_DynamicMesh::GetFrame(const CHAR* pBoneName, D3DXFRAME* pFrame)
{
	FineBoneFrame(pBoneName, (BONE*)m_pRootBone, pFrame);
}

void C_DynamicMesh::FindBone( const CHAR* pBoneName, BONE* pBone, D3DXMATRIX* pOut )
{
	if(pBone->Name)
	{
		if(!strcmp(pBone->Name, pBoneName))
		{
			*pOut = pBone->matWorld;
		}
	}

	if(pBone->pFrameSibling)
		FindBone(pBoneName, (BONE*)pBone->pFrameSibling, pOut);
	if(pBone->pFrameFirstChild)
		FindBone(pBoneName, (BONE*)pBone->pFrameFirstChild, pOut);
}

void C_DynamicMesh::FineBoneFrame(const CHAR* pBoneName, BONE* pBone, D3DXFRAME* pOutFrame)
{
	if (pBone->Name)
	{
		if (!strcmp(pBone->Name, pBoneName))
		{
			*pOutFrame = *(D3DXFRAME*)pBone;
		}
	}

	if (pBone->pFrameSibling)
		FineBoneFrame(pBoneName, (BONE*)pBone->pFrameSibling, pOutFrame);
	if (pBone->pFrameFirstChild)
		FineBoneFrame(pBoneName, (BONE*)pBone->pFrameFirstChild, pOutFrame);
}




