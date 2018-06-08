#pragma once
#include "UI.h"
class C_LifeBar:public C_UI
{
private:
	float m_fCurLife;
	float m_fMaxLife;
	float m_fNowLifeBar;
	STATUSINFO* m_pStatusInfo;
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
public:
	C_LifeBar();
	virtual ~C_LifeBar();
};

