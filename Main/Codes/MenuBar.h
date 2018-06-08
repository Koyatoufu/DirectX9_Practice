#pragma once
#include "UI.h"
class C_MenuBar:public C_UI
{
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
public:
	C_MenuBar();
	virtual ~C_MenuBar();
};

