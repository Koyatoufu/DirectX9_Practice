#pragma once
#include "UI.h"
class C_MiniMap:public C_UI
{
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
public:
	C_MiniMap();
	virtual ~C_MiniMap();
};

