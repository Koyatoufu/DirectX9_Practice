#pragma once
#include "Object.h"
#include "BufferMgr.h"
class C_Grid:public C_Object
{
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
public:
	C_Grid();
	virtual ~C_Grid();
};

