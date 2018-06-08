#include "SoundLoader.h"

IMPLEMENT_SINGLETONE_RESDLL(C_SoundLoader);

C_SoundLoader::C_SoundLoader() :m_pSound(NULL), m_nSize(0)
{
}


C_SoundLoader::~C_SoundLoader()
{
}

HRESULT C_SoundLoader::InitSoundDevice(HWND hWnd)
{
	//사운드 디바이스 생성
	if (FAILED(DirectSoundCreate(NULL, &m_pSound, NULL)))
	{
		return E_FAIL;
	}

	//사운드 디바이스 협조레벨 설정.
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void C_SoundLoader::SoundPlay(int nIndex,DWORD dwFlag)
{
	if (nIndex < 0 || nIndex >(signed)m_vecSound.size())
		return;

	m_vecSound[nIndex]->SetCurrentPosition(0);

	DWORD			dwFre;

	m_vecSound[nIndex]->GetFrequency(&dwFre);
	m_vecSound[nIndex]->Play(0, 0, dwFlag);
}

void C_SoundLoader::SoundStop(int nIndex)
{
	if (nIndex < 0 || nIndex >(signed)m_vecSound.size())
		return;

	m_vecSound[nIndex]->Stop();
}

bool C_SoundLoader::IsSoundPlay(int nIndex)
{
	DWORD	dwStatus = 0;
	m_vecSound[nIndex]->GetStatus(&dwStatus);

	if (dwStatus & DSBSTATUS_PLAYING)
		return true;
	return false;
}

HRESULT C_SoundLoader::LoadSound(TCHAR* pFileName)
{
	HMMIO	hFile;

	//CreateFile
 	hFile = mmioOpen(pFileName, NULL, MMIO_READ);//open wavefile
 
	//Junkstruct
	MMCKINFO	pParent;
	memset(&pParent, 0, sizeof(pParent));
	pParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hFile, &pParent, NULL, MMIO_FINDRIFF);

	MMCKINFO	pChild;
	memset(&pChild, 0, sizeof(pChild));
	pChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	WAVEFORMATEX	wft;
	memset(&wft, 0, sizeof(wft));
	mmioRead(hFile, (char*)&wft, sizeof(wft));

	mmioAscend(hFile, &pChild, 0);
	pChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	DSBUFFERDESC	BuffInfo;
	memset(&BuffInfo, 0, sizeof(DSBUFFERDESC));
	BuffInfo.dwBufferBytes = pChild.cksize;
	BuffInfo.dwSize = sizeof(DSBUFFERDESC);
	BuffInfo.dwFlags = DSBCAPS_STATIC;
	BuffInfo.lpwfxFormat = &wft;

	LPDIRECTSOUNDBUFFER		SoundBuff;

	if (FAILED(m_pSound->CreateSoundBuffer(&BuffInfo, &SoundBuff
		, NULL)))
	{
		return E_FAIL;
	}

	void *pWrite1 = NULL, *pWrite2 = NULL;
	DWORD dwlength1, dwlength2;

	SoundBuff->Lock(0, pChild.cksize, &pWrite1, &dwlength1
		, &pWrite2, &dwlength2, 0);

	if (pWrite1 > 0)
		mmioRead(hFile, (char*)pWrite1, dwlength1);
	if (pWrite2 > 0)
		mmioRead(hFile, (char*)pWrite2, dwlength2);

	SoundBuff->Unlock(pWrite1, dwlength1, pWrite2, dwlength2);

	mmioClose(hFile, 0);

	m_vecSound.resize(m_nSize + 1);
	m_vecSound.reserve(m_nSize + 1);

	m_vecSound[m_nSize] = SoundBuff;

	m_nSize++;

	return S_OK;
}

void C_SoundLoader::Release()
{
	for (int i = 0; i < m_nSize;i++)
	{
		m_vecSound[i]->Release();
		m_vecSound[i] = NULL;
	}

	m_vecSound.clear();
}

void C_SoundLoader::ReleaseSoundVector()
{
	m_vecSound.~vector<LPDIRECTSOUNDBUFFER>();
}
