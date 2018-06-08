#include "StdAfx.h"
#include "Logo.h"

#include "StateMgr.h"

C_Logo::C_Logo() :C_State(), m_fTime(0.0f)
{
}


C_Logo::~C_Logo()
{
	Release();
}

HRESULT C_Logo::Initialize()
{
	LoadResource();

	return S_OK;
}

void C_Logo::Progress()
{
	m_fTime += C_Time::GetInst()->GetTime();
	if (m_fTime>3.0f)
	{
		C_StateMgr::GetInst()->SetState(STATE_MENU);
	}
}

void C_Logo::Render()
{
	if (m_fTime<=3.0f)
	{
		C_DirectX::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);


		LPDIRECT3DTEXTURE9 pTexture = C_TextureMgr::GetInst()->GetTexInfo(L"Logo")->pTexture;

		RECT rect = { 0, 0, 1024, 768 };

		C_DirectX::GetInst()->GetSprite()->Draw(pTexture, &rect, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		C_DirectX::GetInst()->GetSprite()->End();
	}
}

void C_Logo::Release()
{
	C_TextureMgr::GetInst()->Release();
}

HRESULT C_Logo::LoadResource()
{
	if (FAILED(C_TextureMgr::GetInst()->InsertTexture(C_DirectX::GetInst()->GetDevice(), TEX_GENERAL, L"../../Resource/Texture/Logo/Logo.jpg", L"Logo")))
	{
		return E_FAIL;
	}

	return S_OK;
}
