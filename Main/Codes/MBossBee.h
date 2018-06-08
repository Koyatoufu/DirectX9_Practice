#pragma once
#include "MBoss.h"
class C_MBossBee:public C_MBoss
{
protected:
	virtual void SetContantTable();
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
public:
	C_MBossBee();
	virtual ~C_MBossBee();
};

