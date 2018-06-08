#pragma once
#include "UI.h"
class C_PStatusBar:public C_UI
{
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
public:
	C_PStatusBar();
	virtual ~C_PStatusBar();
};

