#include "StdAfx.h"
#include "EnBar.h"
#include "ObjMgr.h"
#include "Player.h"
#include "PStatusBar.h"

C_EnBar::C_EnBar() :m_fCurEn(0.0f), m_fMaxEn(0.0f), m_fNowEnBar(0.0f), m_pStatusInfo(NULL)
{
}


C_EnBar::~C_EnBar()
{
	Release();
}

HRESULT C_EnBar::Initialize()
{
	m_sortID = SORTID_UI;
	m_pTexKey = L"EnBar";

	m_pStatusInfo = ((C_Player*)C_ObjMgr::GetInst()->GetObj(L"Player"))->GetStatusInfo();

	if (FAILED(C_TextureMgr::GetInst()->InsertTexture(C_DirectX::GetInst()->GetDevice(), TEX_GENERAL, L"../../Resource/Texture/UI/EnergyBar.bmp", m_pTexKey)))
	{
		return E_FAIL;
	}

	m_pTexInfo = C_TextureMgr::GetInst()->GetTexInfo(m_pTexKey);

	m_fSizeX = (float)m_pTexInfo->TexInfo.Width;
	m_fSizeY = (float)m_pTexInfo->TexInfo.Height;

	m_vCenter = D3DXVECTOR3(m_fSizeX*0.5f, m_fSizeY*0.5f, 0.0f);

	m_fCurEn = m_pStatusInfo->fEnergy;
	m_fMaxEn = m_pStatusInfo->fMaxEnergy;
	m_fNowEnBar = m_fSizeX;
	
	OBJINFO* pInfo = C_ObjMgr::GetInst()->GetObj(L"PStatusUI")->GetInfo();

	m_Info.vPosition.x = pInfo->vPosition.x + 42.0f;
	m_Info.vPosition.y = pInfo->vPosition.y - 13.0f;
	m_Info.vPosition.z = 0.0f;

	D3DXMatrixIdentity(&m_Info.matWorld);

	return S_OK;
}

STATEID C_EnBar::Progress()
{
	m_fCurEn = m_pStatusInfo->fEnergy; 
	m_fNowEnBar = m_fSizeX - ((m_fCurEn / m_fMaxEn)*m_fSizeX);

	m_Info.matWorld._41 = m_Info.vPosition.x;
	m_Info.matWorld._42 = m_Info.vPosition.y;
	m_Info.matWorld._43 = m_Info.vPosition.z;

	return STATE_NONE;
}

void C_EnBar::Render()
{
	RECT rect = { LONG(m_Info.vPosition.x - m_fSizeX / 2.f)
		, LONG(m_Info.vPosition.y - m_fSizeY / 2.f)
		, LONG(m_Info.vPosition.x + m_fSizeX / 2.f - m_fNowEnBar)
		, LONG(m_Info.vPosition.y + m_fSizeY / 2.f) };
	m_rect = rect;

	C_DirectX::GetInst()->GetSprite()->SetTransform(&m_Info.matWorld);
	C_DirectX::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	C_DirectX::GetInst()->GetSprite()->Draw(m_pTexInfo->pTexture, &m_rect,
		&m_vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	C_DirectX::GetInst()->GetSprite()->End();
}

void C_EnBar::Release()
{

}
