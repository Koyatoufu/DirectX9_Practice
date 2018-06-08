#pragma once
#include "Bound.h"
class C_BoundarySphere:public C_Bound
{
protected:
	virtual void SetComputeBound();
public:
	virtual HRESULT InitBound(LPDIRECT3DDEVICE9 pDevice);
public:
	C_BoundarySphere();
	virtual ~C_BoundarySphere();
};

