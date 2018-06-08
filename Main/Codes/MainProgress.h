#pragma once

#include "Define.h"

#include "Time.h"
#include "DirectX.h"

#include <Windows.h>
#include <mmsystem.h>

#include "TextureMgr.h"
#include "SoundLoader.h"

#include "StateMgr.h"

class C_MainProgress
{
	DECLARE_SINGLETONE(C_MainProgress);
private:
	TCHAR m_szFPS[128];
	int m_nFPSCnt;
	float m_fTime;
	HWND m_hWnd;
private:
	void CheckTime();
public:
	HRESULT Initialize(HWND hWnd);
	void Progress();
	void Render();
	void Release();
private:
	C_MainProgress();
	C_MainProgress(const C_MainProgress&);
	C_MainProgress& operator=(const C_MainProgress&);
public:
	~C_MainProgress();
};

