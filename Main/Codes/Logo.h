#pragma once
#include "State.h"
class C_Logo:public C_State
{
private:
	float m_fTime;
protected:
	virtual HRESULT LoadResource();
public:
	virtual HRESULT Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();
public:
	C_Logo();
	virtual ~C_Logo();
};

