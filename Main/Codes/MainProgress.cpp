#include "StdAfx.h"
#include "MainProgress.h"

IMPLEMENT_SINGLETONE(C_MainProgress);

C_MainProgress::C_MainProgress() :m_nFPSCnt(0), m_fTime(0.0f)
{
	for (int i = 0; i < 128;i++)
	{
		m_szFPS[i] = 0;
	}
}


C_MainProgress::~C_MainProgress()
{
}

HRESULT C_MainProgress::Initialize(HWND hWnd)
{

	C_TextureMgr::InitInst();
	

	C_SoundLoader::InitInst();
	C_SoundLoader::GetInst()->InitSoundDevice(hWnd);



	C_StateMgr::InitInst();
	if (FAILED(C_StateMgr::GetInst()->Initialize()))
	{
		return E_FAIL;
	}
	

	return S_OK;
}

void C_MainProgress::Progress()
{
	m_nFPSCnt++;

	m_fTime += C_Time::GetInst()->GetTime();

	CheckTime();

	if (m_fTime > 1.0f)
	{
		swprintf_s(m_szFPS, L"%d", m_nFPSCnt);
		m_nFPSCnt = 0;
		m_fTime = 0;
	}

	C_StateMgr::GetInst()->Progress();
}

void C_MainProgress::Render()
{
	RECT rect = { 0 };

	C_StateMgr::GetInst()->Render();

	D3DXMATRIX matFontWorld;
	D3DXMatrixIdentity(&matFontWorld);
	C_DirectX::GetInst()->GetSprite()->SetTransform(&matFontWorld);
	C_DirectX::GetInst()->DrawFont(rect, m_szFPS, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void C_MainProgress::Release()
{
	C_ShaderMgr::GetInst()->Release();
	C_ShaderMgr::ReleaseInst();

	C_SortMgr::GetInst()->ReleaseSortObj();
	C_SortMgr::ReleaseInst();

	C_ObjMgr::GetInst()->Release();
	C_ObjMgr::ReleaseInst();

	C_SoundLoader::GetInst()->Release();
	C_SoundLoader::GetInst()->ReleaseSoundVector();
	C_SoundLoader::ReleaseInst();

	C_BoundaryMgr::GetInst()->Release();
	C_BoundaryMgr::ReleaseInst();

	C_MeshMgr::GetInst()->Release();
	C_MeshMgr::ReleaseInst();

	C_TextureMgr::GetInst()->Release();
	C_TextureMgr::ReleaseInst();

	C_BufferMgr::GetInst()->Release();
	C_BufferMgr::ReleaseInst();
}

void C_MainProgress::CheckTime()
{
	if (m_nFPSCnt > 60)
	{
		
	}
	else if (m_nFPSCnt<60)
	{
		
	}
}


