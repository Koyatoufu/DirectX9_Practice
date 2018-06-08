#pragma once

#include "Mesh.h"
#include "HierarchyLoader.h"

class C_DynamicMesh:public C_Mesh
{
protected:
	C_HierarchyLoader*			m_pLoader;
	D3DXFRAME*					m_pRootBone;
	C_AnimationCtrl*				m_pAniCtrl;
public:
	virtual HRESULT InitMesh(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pPath, const TCHAR* pFileName)PURE;
	virtual HRESULT CloneMesh(LPDIRECT3DDEVICE9 pDevice
		, C_AnimationCtrl** ppAniCtrl);
	virtual void Render(LPDIRECT3DDEVICE9 pDevice
		, const BONE* pRootBone = NULL);
	virtual void Release();
public:
	virtual void GetBoneMatrix(const CHAR* pBoneName, D3DXMATRIX* pOut);
	virtual void GetFrame(const CHAR* pBoneName,D3DXFRAME* pFrame);
protected:
	void FindBone(const CHAR* pBoneName, BONE* pBone, D3DXMATRIX* pOut);
	void FineBoneFrame(const CHAR* pBoneName, BONE* pBone,D3DXFRAME* pOutFrame);
public:
	C_DynamicMesh();
	virtual ~C_DynamicMesh();
};

