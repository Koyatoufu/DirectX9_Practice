// Main.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//
#include "stdafx.h"
#include "../Codes/WinApi.h"
#include "Main.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.

	C_WinApi::InitInst();
	if (FAILED(C_WinApi::GetInst()->InitWindow(hInstance, nCmdShow)))
	{
		C_WinApi::GetInst()->Reelase();
		C_WinApi::ReleaseInst();
		return 0;
	}
	C_WinApi::GetInst()->UpdateMessage();
	C_WinApi::GetInst()->Reelase();
	C_WinApi::ReleaseInst();

	return 0;
}


