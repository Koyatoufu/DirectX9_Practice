#pragma once
#include "UI.h"
class C_StartText :public C_UI
{
protected:
	virtual void CollCheck();
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
public:
	C_StartText();
	virtual ~C_StartText();
};

