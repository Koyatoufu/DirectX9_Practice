#pragma once
#include "Bound.h"
class C_BoundaryBox:public C_Bound
{
protected:
	virtual void SetComputeBound();
public:
	virtual HRESULT InitBound(LPDIRECT3DDEVICE9 pDevice);
public:
	C_BoundaryBox();
	virtual ~C_BoundaryBox();
};

