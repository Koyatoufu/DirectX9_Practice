#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"
EXTERN class SYSTEM_DLL C_Input
{
	DECLARE_SINGLETONE_SYSDLL(C_Input)
private:
	LPDIRECTINPUT8 m_pInput;

	LPDIRECTINPUTDEVICE8 m_pKeyboard;
	LPDIRECTINPUTDEVICE8 m_pMouse;

	BYTE m_arKeyboardState[256];
	DIMOUSESTATE m_MouseState;
public:
	HRESULT InitInputDevice(HWND hWnd, HINSTANCE hInst);
	void Release();

	void SetKeyState();

	BYTE GetKeyboardState(short nState);
	bool IsKeyDown(unsigned int nState);
	const DIMOUSESTATE GetMouseState();
private:
	C_Input();
	C_Input(const C_Input&);
	const C_Input& operator=(const C_Input&);
public:
	~C_Input();
};
