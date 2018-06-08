#include "Input.h"


IMPLEMENT_SINGLETONE_SYSDLL(C_Input);

C_Input::C_Input() :m_pInput(NULL), m_pKeyboard(NULL), m_pMouse(NULL)
{
	ZeroMemory(&m_arKeyboardState, sizeof(BYTE) * 128);
	ZeroMemory(&m_MouseState, sizeof(DIMOUSESTATE));
}


C_Input::~C_Input()
{
}

HRESULT C_Input::InitInputDevice(HWND hWnd, HINSTANCE hInst)
{
	if (FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}


	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pKeyboard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	m_pKeyboard->Acquire();

	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL)))
	{
		return E_FAIL;
	}

	if (FAILED(m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	if (FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	m_pMouse->Acquire();

	return S_OK;
}

void C_Input::Release()
{
	if (m_pKeyboard)
	{
		m_pKeyboard->Unacquire();
		m_pKeyboard->Release();
		m_pKeyboard = NULL;
	}
	if (m_pMouse)
	{
		m_pMouse->Unacquire();
		m_pMouse->Release();
		m_pMouse = NULL;
	}
	if (m_pInput)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

void C_Input::SetKeyState()
{
	if (FAILED(m_pKeyboard->GetDeviceState(sizeof(m_arKeyboardState), m_arKeyboardState)))
	{
		return;
	}
	if (FAILED(m_pMouse->GetDeviceState(sizeof(m_MouseState), &m_MouseState)))
	{
		return;
	}
}

BYTE C_Input::GetKeyboardState(short nState)
{
	return m_arKeyboardState[nState];
}

const DIMOUSESTATE C_Input::GetMouseState()
{
	return m_MouseState;
}

bool C_Input::IsKeyDown(unsigned int nState)
{
	return (m_arKeyboardState[nState] & 0x80) ? true : false;
}