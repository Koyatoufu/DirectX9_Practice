#include "StdAfx.h"
#include "StateMgr.h"

IMPLEMENT_SINGLETONE(C_StateMgr);

C_StateMgr::C_StateMgr(void) :m_pState(NULL)
{

}

C_StateMgr::~C_StateMgr(void)
{
}

HRESULT C_StateMgr::Initialize()
{
	m_pState = new C_Logo();

	if (FAILED(m_pState->Initialize()))
	{
		return E_FAIL;
	}

	return S_OK;
}

void C_StateMgr::Release()
{
	m_pState->Release();
	delete m_pState;
	m_pState = NULL;
}

HRESULT C_StateMgr::SetState(STATEID stateID)
{
	C_State* pStateTmp = m_pState;
	m_pState = NULL;

	switch (stateID)
	{
	case STATE_STAGE:
		m_pState = new C_Stage();
		break;
	case STATE_MENU:
		m_pState = new C_Menu();
		break;
	case STATE_TEST:
		m_pState = new C_TestStage();
		break;
// 	case STATE_END:
// 		exit(1);
// 		break;
	default:
		break;
	}

	if (!m_pState)
	{
		return E_FAIL;
	}

	pStateTmp->Release();
	delete pStateTmp;
	pStateTmp = NULL;

	if (FAILED(m_pState->Initialize()))
	{
		return E_FAIL;
	}

	return S_OK;
}

void C_StateMgr::Progress()
{
	m_pState->Progress();
}

void C_StateMgr::Render()
{
	m_pState->Render();
}
