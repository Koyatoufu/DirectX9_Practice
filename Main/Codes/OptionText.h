#pragma once
#include "UI.h"
class C_OptionText:public C_UI
{
protected:
	virtual void CollCheck();
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
public:
	C_OptionText();
	virtual ~C_OptionText();
};

