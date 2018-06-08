#pragma once
#include "Enemy.h"
class C_MBoss:public C_Enemy
{
public:
	virtual HRESULT Initialize() = 0;
	virtual STATEID Progress() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
public:
	C_MBoss();
	virtual ~C_MBoss();
};

