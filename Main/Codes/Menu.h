#pragma once
#include "State.h"
class C_Menu:public C_State
{
protected:
	virtual HRESULT LoadResource();
	virtual void AddObject();
	virtual void SoundPlay();
public:
	virtual HRESULT Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();
public:
	C_Menu();
	~C_Menu();
};

