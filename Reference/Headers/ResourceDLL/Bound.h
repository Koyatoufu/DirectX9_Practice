#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
EXTERN class RESOURCE_DLL C_Bound
{
protected:
	LPD3DXMESH m_pMesh;
	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;
	float m_fRadius;
public:
	virtual HRESULT InitBound(LPDIRECT3DDEVICE9 pDevice)=0;
	virtual void BoundRender();
	virtual void Release();

	const D3DXVECTOR3* GetMin();
	const D3DXVECTOR3* GetMax();
	float GetRadius();
	virtual void ScaleBound(float fScale);
protected:
	virtual void SetComputeBound()=0;
public:
	C_Bound();
	virtual ~C_Bound();
};

