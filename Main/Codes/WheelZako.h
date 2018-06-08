#pragma once
#include "Enemy.h"
class C_WheelZako:public C_Enemy
{
protected:
	virtual void SetContantTable();
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
public:
	C_WheelZako();
	virtual ~C_WheelZako();
};

