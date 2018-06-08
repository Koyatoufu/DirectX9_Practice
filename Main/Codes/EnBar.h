#pragma once
#include "UI.h"
class C_EnBar:public C_UI
{
private:
	float m_fCurEn;
	float m_fMaxEn;
	float m_fNowEnBar;
	STATUSINFO* m_pStatusInfo;
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
public:
	C_EnBar();
	virtual ~C_EnBar();
};

