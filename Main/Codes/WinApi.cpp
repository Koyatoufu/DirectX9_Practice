#include "StdAfx.h"
#include "WinApi.h"

IMPLEMENT_SINGLETONE(C_WinApi);

C_WinApi::C_WinApi() :m_hInst(NULL), m_hWnd(NULL), m_bQuit(false)
, m_nSizeX(0), m_nSizeY(0), m_dwStickKeyFlag(0), m_dwFilterKeyFlag(0)
{
}


C_WinApi::~C_WinApi()
{
}

HRESULT C_WinApi::InitWindow(HINSTANCE hInstance, int nCmdShow)
{

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;/*MAKEINTRESOURCE(IDC_MAIN);*/
	wcex.lpszClassName = L"Game";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);

	m_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	m_nSizeX = 1024;
	m_nSizeY = 768;

	m_hWnd = CreateWindow(L"Game", NULL, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, m_nSizeX, m_nSizeY, NULL, NULL, hInstance, NULL);

	if (!m_hWnd)
	{
		return E_FAIL;
	}

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	SetStickFilter();

	if (FAILED(InitDevice()))
	{
		return E_FAIL;
	}

	C_MainProgress::InitInst();
	if (FAILED(C_MainProgress::GetInst()->Initialize(m_hWnd)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void C_WinApi::UpdateMessage()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Progress();
			Render();

			if (m_bQuit)
			{
				msg.message = WM_QUIT;
			}
		}
	}
}

void C_WinApi::Reelase()
{
	C_MainProgress::GetInst()->Release();
	C_MainProgress::ReleaseInst();

	C_Input::GetInst()->Release();
	C_Input::ReleaseInst();

	C_Time::ReleaseInst();

	C_DirectX::GetInst()->Release();
	C_DirectX::ReleaseInst();

	ResetStickFilter();
}

LRESULT CALLBACK C_WinApi::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HRESULT C_WinApi::InitDevice()
{
	C_DirectX::InitInst();
	if (FAILED(C_DirectX::GetInst()->InitDevice(m_hWnd, m_nSizeX, m_nSizeY, true)))
	{
		return E_FAIL;
	}

	C_Time::InitInst();
	C_Time::GetInst()->InitTime();

	C_Input::InitInst();
	if (C_Input::GetInst()->InitInputDevice(m_hWnd,m_hInst))
	{
		return E_FAIL;
	}

	return S_OK;
}

void C_WinApi::Progress()
{
	C_Time::GetInst()->UpdateTime();
	C_Input::GetInst()->SetKeyState();
	C_MainProgress::GetInst()->Progress();
}

void C_WinApi::Render()
{
	C_DirectX::GetInst()->Begin_Render();

	C_MainProgress::GetInst()->Render();

	C_DirectX::GetInst()->End_Render();
}

void C_WinApi::GetSize(int& nSizeX, int& nSizeY) const
{
	nSizeX = m_nSizeX;
	nSizeY = m_nSizeY;
}

void C_WinApi::SetSize(int nSizeX, int nSizeY)
{
	m_nSizeX = nSizeX;
	m_nSizeY = nSizeY;
}

HWND C_WinApi::GetHwnd()const
{
	return m_hWnd;
}

void C_WinApi::SetStickFilter()
{
	STICKYKEYS sStickKeys;
	sStickKeys.cbSize = sizeof(STICKYKEYS);
	SystemParametersInfo(SPI_GETSTICKYKEYS, sizeof(STICKYKEYS), &sStickKeys, 0);
	m_dwStickKeyFlag = sStickKeys.dwFlags;

	// 설정
	sStickKeys.dwFlags &= ~(SKF_AVAILABLE | SKF_HOTKEYACTIVE);
	SystemParametersInfo(SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), &sStickKeys, 0);

	// 필터키 막기
	FILTERKEYS sFilterKeys;
	sFilterKeys.cbSize = sizeof(FILTERKEYS);
	SystemParametersInfo(SPI_GETFILTERKEYS, sizeof(FILTERKEYS), &sFilterKeys, 0);
	m_dwFilterKeyFlag = sFilterKeys.dwFlags;
	sFilterKeys.dwFlags &= ~(FKF_AVAILABLE | FKF_HOTKEYACTIVE);
	SystemParametersInfo(SPI_SETFILTERKEYS, sizeof(FILTERKEYS), &sFilterKeys, 0);
}

void C_WinApi::ResetStickFilter()
{
	STICKYKEYS sStickKeys;
	sStickKeys.cbSize = sizeof(STICKYKEYS);
	sStickKeys.dwFlags = m_dwStickKeyFlag;
	SystemParametersInfo(SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), &sStickKeys, 0);

	FILTERKEYS sFilterKeys;
	sFilterKeys.cbSize = sizeof(FILTERKEYS);
	sFilterKeys.dwFlags = m_dwFilterKeyFlag;
	SystemParametersInfo(SPI_SETFILTERKEYS, sizeof(FILTERKEYS), &sFilterKeys, 0);
}
