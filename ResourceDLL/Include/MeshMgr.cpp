#include "MeshMgr.h"

IMPLEMENT_SINGLETONE_RESDLL(C_MeshMgr);

C_MeshMgr::C_MeshMgr(void)
{
}


C_MeshMgr::~C_MeshMgr(void)
{
	Release();
}

void C_MeshMgr::GetBoneMatrix( const TCHAR* pMeshKey , const CHAR* pBoneName , D3DXMATRIX* pOut )
{
	std::map<const TCHAR*, C_Mesh*>::iterator iter = m_MapMesh.find(pMeshKey);

	if (iter == m_MapMesh.end())
		return;

	iter->second->GetBoneMatrix(pBoneName, pOut);
}
void C_MeshMgr::GetFrame(const TCHAR* pMeshKey, const CHAR* pBoneName, D3DXFRAME* pOut)
{
	std::map<const TCHAR*, C_Mesh*>::iterator iter = m_MapMesh.find(pMeshKey);

	if (iter == m_MapMesh.end())
		return;

	iter->second->GetFrame(pBoneName, pOut);
}
void C_MeshMgr::GetMesh(const TCHAR* pMeshKey, LPD3DXMESH pMesh)
{
	std::map<const TCHAR*, C_Mesh*>::iterator iter = m_MapMesh.find(pMeshKey);

	if (iter == m_MapMesh.end())
		return;

	pMesh = iter->second->GetMesh();
}

HRESULT C_MeshMgr::AddMesh( LPDIRECT3DDEVICE9 pDevice , const TCHAR* pPath , const TCHAR* pFileName , const TCHAR* pMeshKey , MESHTYPE MeshType )
{
	std::map<const TCHAR*, C_Mesh*>::iterator iter=m_MapMesh.find(pMeshKey);

	if (iter!=m_MapMesh.end())
	{
		TCHAR sztmp[128] = L"This Mesh already exists in System::FileName";

		lstrcat(sztmp, pFileName);

		MSGBOX_OK(sztmp);
		return S_OK;
	}

	C_Mesh* pMesh=NULL;
	switch (MeshType)
	{
		case MESH_DYNAMIC:
			pMesh = new C_SkinedMesh();
			break;
		case MESH_STATIC:
			pMesh = new C_StaticMesh();
			break;
	}

	if (!pMesh)
	{
		MSGBOX_OK(L"None Mesh");
		return E_FAIL;
	}
	if (FAILED(pMesh->InitMesh(pDevice,pPath,pFileName)))
	{
		MSGBOX_OK(L"Don't InitMesh");
		return E_FAIL;
	}

	m_MapMesh.insert(std::make_pair(pMeshKey, pMesh));

	return S_OK;
}

void C_MeshMgr::InvalidateMesh( const TCHAR* pMeshKey, D3DXMATRIX* pMatWorld )
{
	std::map<const TCHAR*, C_Mesh*>::iterator iter = m_MapMesh.find(pMeshKey);

	if (iter == m_MapMesh.end())
		return;

	iter->second->InvalidateMesh(pMatWorld);
}

HRESULT C_MeshMgr::CloneMesh( LPDIRECT3DDEVICE9 pDevice , const TCHAR* pMeshKey , C_AnimationCtrl** ppAniCtrl )
{
	std::map<const TCHAR*, C_Mesh*>::iterator iter = m_MapMesh.find(pMeshKey);

	if (iter == m_MapMesh.end())
		return E_FAIL;

	return iter->second->CloneMesh(pDevice,ppAniCtrl);
}

void C_MeshMgr::Mesh_Render( LPDIRECT3DDEVICE9 pDevice , const TCHAR* pMeshKey )
{
	std::map<const TCHAR*, C_Mesh*>::iterator iter = m_MapMesh.find(pMeshKey);

	if (iter == m_MapMesh.end())
		return;

	iter->second->Render(pDevice);
}

void C_MeshMgr::Release( void )
{
	std::map<const TCHAR*, C_Mesh*>::iterator iter = m_MapMesh.begin();

	while (iter!=m_MapMesh.end())
	{
		if (iter->second)
		{
			iter->second->Release();
			delete iter->second;
			iter->second = NULL;
		}
		iter++;
	}

	m_MapMesh.clear();
}
