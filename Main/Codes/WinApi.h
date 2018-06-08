#pragma once
#include "Define.h"

#include "DirectX.h"
#include "Time.h"
#include "Input.h"
#include "MainProgress.h"

class C_WinApi
{
	DECLARE_SINGLETONE(C_WinApi);
private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	bool m_bQuit;
	int m_nSizeX, m_nSizeY;
	DWORD m_dwStickKeyFlag;
	DWORD m_dwFilterKeyFlag;
public:
	HRESULT InitWindow(HINSTANCE hInstance,int nCmdShow);
	void UpdateMessage();
	void Reelase();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	void GetSize(int& nSizeX,int& nSizeY)const;
	void SetSize(int nSizeX, int nSizeY);

	HWND GetHwnd()const;
private:
	HRESULT InitDevice();

	void SetStickFilter();
	void ResetStickFilter();
	
	void Progress();
	void Render();
private:
	C_WinApi();
	C_WinApi(const C_WinApi&);
public:
	~C_WinApi();
};

