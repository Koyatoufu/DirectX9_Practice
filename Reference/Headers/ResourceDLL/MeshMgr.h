#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "SkinedMesh.h"
#include "StaticMesh.h"

class C_AnimationCtrl;
class C_Mesh;
EXTERN class RESOURCE_DLL C_MeshMgr
{
	DECLARE_SINGLETONE_RESDLL(C_MeshMgr);
private:
	std::map<const TCHAR*, C_Mesh*>		m_MapMesh;
public:
	void GetBoneMatrix(const TCHAR* pMeshKey
		, const CHAR* pBoneName
		, D3DXMATRIX* pOut);
	void GetFrame(const TCHAR* pMeshKey, const CHAR* pBoneName, D3DXFRAME* pOut);
	void GetMesh(const TCHAR* pMeshKey,LPD3DXMESH pMesh);
public:
	HRESULT AddMesh(LPDIRECT3DDEVICE9 pDevice
		, const TCHAR* pPath
		, const TCHAR* pFileName 
		, const TCHAR* pMeshKey
		, MESHTYPE MeshType);

	void InvalidateMesh(const TCHAR* pMeshKey, D3DXMATRIX* pMatWorld);

	HRESULT CloneMesh(LPDIRECT3DDEVICE9 pDevice , const TCHAR* pMeshKey
		, C_AnimationCtrl** ppAniCtrl);

	void Mesh_Render(LPDIRECT3DDEVICE9 pDevice
		, const TCHAR* pMeshKey);

	void Release(void);

private:
	C_MeshMgr(void);
	C_MeshMgr(const C_MeshMgr&);
public:
	~C_MeshMgr(void);
};

