#pragma once
#include "State.h"




class C_Stage:public C_State
{
protected:
	virtual HRESULT LoadResource();
public:
	virtual HRESULT Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();
public:
	C_Stage();
	virtual ~C_Stage();
};

