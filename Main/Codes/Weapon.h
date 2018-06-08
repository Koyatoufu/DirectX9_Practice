#pragma once
#include "StaticObj.h"
class C_Weapon:public C_StaticObj
{
public:
	virtual HRESULT Initialize() = 0;
	virtual STATEID Progress() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
public:
	C_Weapon();
	C_Weapon(const C_Weapon&);
	virtual ~C_Weapon();
};

