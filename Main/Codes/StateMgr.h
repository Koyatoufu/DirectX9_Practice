#pragma once
#include "Define.h"
#include "Logo.h"
#include "Menu.h"
#include "TestStage.h"
class C_StateMgr
{
	DECLARE_SINGLETONE(C_StateMgr);
private:
	C_State* m_pState;
public:
	HRESULT Initialize();
	HRESULT SetState(STATEID stateID);
	void Release();
	void Progress();
	void Render();
private:
	C_StateMgr(void);
	C_StateMgr(const C_StateMgr&);
public:
	~C_StateMgr(void);
};

