#pragma once
#include "UI.h"
class C_SkillBar :public C_UI
{
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
public:
	C_SkillBar();
	virtual ~C_SkillBar();
};

