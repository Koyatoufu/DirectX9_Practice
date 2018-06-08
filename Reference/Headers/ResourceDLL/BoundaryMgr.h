#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

#include "BoundaryBox.h"
#include "BoundarySphere.h"
#include "BoundaryCylinder.h"

EXTERN class RESOURCE_DLL C_BoundaryMgr
{
	DECLARE_SINGLETONE_RESDLL(C_BoundaryMgr);
private:
	std::map<BOUNDTYPE, C_Bound*> m_mapBound;
public:
	HRESULT AddBoundary(LPDIRECT3DDEVICE9 pDevice,BOUNDTYPE Type);

	const D3DXVECTOR3* GetMin(BOUNDTYPE Type);
	const D3DXVECTOR3* GetMax(BOUNDTYPE Type);
	float GetRadius(BOUNDTYPE Type);
	void ScaleBound(BOUNDTYPE Type,float fScale);

	void Release();
private:
	C_BoundaryMgr();
	C_BoundaryMgr(const C_BoundaryMgr&);
public:
	~C_BoundaryMgr();
};

