#pragma once

#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "AnimationCtrl.h"

EXTERN class RESOURCE_DLL C_Mesh
{
protected:
	LPD3DXMESH m_pMesh;

	LPD3DXBUFFER m_pSubsetBuff;
	DWORD m_dwSubsetCnt;

	LPD3DXMATERIAL m_pSubsets;

	LPDIRECT3DTEXTURE9* m_pTextures;
	D3DMATERIAL9* m_pMtrls;
public:
	virtual HRESULT InitMesh(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pPath, const TCHAR* pFileName)PURE;
	virtual HRESULT CloneMesh(LPDIRECT3DDEVICE9 pDevice
		, C_AnimationCtrl** ppAniCtrl);
	virtual void Render(LPDIRECT3DDEVICE9 pDevice
		, const BONE* pRootBone = NULL)PURE;
	virtual void Release();
public:
	virtual void GetBoneMatrix(const CHAR* pBoneName, D3DXMATRIX* pOut) {}
	virtual void GetFrame(const CHAR* pBoneName, D3DXFRAME* pFrame){}
	LPD3DXMESH GetMesh();
public:
	virtual void InvalidateMesh(D3DXMATRIX* pMatWorld) {}
public:
	C_Mesh();
	virtual ~C_Mesh();
};

