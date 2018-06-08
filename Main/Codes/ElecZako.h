#pragma once
#include "Enemy.h"
class C_ElecZako:public C_Enemy
{
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
protected:
	virtual void SetContantTable();
public:
	C_ElecZako();
	virtual ~C_ElecZako();
};

