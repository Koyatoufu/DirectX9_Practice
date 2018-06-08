#pragma once

#pragma comment( lib, "winmm" )
#pragma comment( lib, "comctl32" )
#pragma comment( lib, "imm32" )
#pragma comment( lib, "Version" )

#define RESOURCE_EXPORT

#include "ResourceDef.h"
#include <dsound.h>

EXTERN class RESOURCE_DLL C_SoundLoader
{
	DECLARE_SINGLETONE_RESDLL(C_SoundLoader);
private:
	int m_nSize;
	LPDIRECTSOUND m_pSound;
	std::vector<LPDIRECTSOUNDBUFFER> m_vecSound;
public:
	HRESULT InitSoundDevice(HWND hWnd);
	HRESULT LoadSound(TCHAR* pFileName);
	void SoundPlay(int nIndex, DWORD dwFlag);
	void SoundStop(int nIndex);
	bool IsSoundPlay(int nIndex);

	void Release();
	void ReleaseSoundVector();
public:
	C_SoundLoader();
	~C_SoundLoader();
};

