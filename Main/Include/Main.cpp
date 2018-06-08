// Main.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
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

 	// TODO: 여기에 코드를 입력합니다.

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


