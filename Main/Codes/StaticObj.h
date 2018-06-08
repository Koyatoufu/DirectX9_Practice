#pragma once
#include "Object.h"
class C_StaticObj:public C_Object
{
public:
	virtual HRESULT Initialize() = 0;
	virtual STATEID Progress() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void SetConstandTable(){};
public:
	C_StaticObj();
	virtual ~C_StaticObj();
};

