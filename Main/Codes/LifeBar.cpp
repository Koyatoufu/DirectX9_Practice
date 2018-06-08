#include "StdAfx.h"
#include "LifeBar.h"
#include "ObjMgr.h"
#include "Player.h"
#include "PStatusBar.h"

C_LifeBar::C_LifeBar() :C_UI(), m_fCurLife(0.0f), m_fMaxLife(0.0f), m_fNowLifeBar(0.0f), m_pStatusInfo(NULL)
{
}


C_LifeBar::~C_LifeBar()
{
	Release();
}

HRESULT C_LifeBar::Initialize()
{
	m_sortID = SORTID_UI;
	m_pTexKey = L"LifeBar";

	if (FAILED(C_TextureMgr::GetInst()->InsertTexture(C_DirectX::GetInst()->GetDevice(), TEX_GENERAL, L"../../Resource/Texture/UI/LifeBar.bmp", m_pTexKey)))
	{
		return E_FAIL;
	}

	m_pStatusInfo = ((C_Player*)C_ObjMgr::GetInst()->GetObj(L"Player"))->GetStatusInfo();

	m_pTexInfo = C_TextureMgr::GetInst()->GetTexInfo(m_pTexKey);

	m_fSizeX = (float)m_pTexInfo->TexInfo.Width;
	m_fSizeY = (float)m_pTexInfo->TexInfo.Height;

	m_vCenter = D3DXVECTOR3(m_fSizeX*0.5f,m_fSizeY*0.5f,0.0f);

	m_fCurLife = m_pStatusInfo->fLife;
	m_fMaxLife = m_pStatusInfo->fMaxLife;
	m_fNowLifeBar = m_pStatusInfo->fLife;

	OBJINFO* pInfo = C_ObjMgr::GetInst()->GetObj(L"PStatusUI")->GetInfo();

	m_Info.vPosition.x = pInfo->vPosition.x+42.0f;
	m_Info.vPosition.y = pInfo->vPosition.y - 27.5f;
	m_Info.vPosition.z = 0.0f;

	D3DXMatrixIdentity(&m_Info.matWorld);

	return S_OK;
}

STATEID C_LifeBar::Progress()
{
	m_fCurLife = m_pStatusInfo->fLife;
	m_fNowLifeBar = m_fSizeX - ((m_fCurLife / m_fMaxLife)*m_fSizeX);

	m_Info.matWorld._41 = m_Info.vPosition.x;
	m_Info.matWorld._42 = m_Info.vPosition.y;
	m_Info.matWorld._43 = m_Info.vPosition.z;

	return STATE_NONE;
}

void C_LifeBar::Render()
{
	RECT rect = { LONG(m_Info.vPosition.x - m_fSizeX / 2.f)
		, LONG(m_Info.vPosition.y - m_fSizeY / 2.f)
		, LONG(m_Info.vPosition.x + m_fSizeX / 2.f-m_fNowLifeBar)
		, LONG(m_Info.vPosition.y + m_fSizeY / 2.f) };
	m_rect = rect;

	D3DXVECTOR3 vPos = D3DXVECTOR3(m_Info.vPosition.x/2.0f,0.0f,0.0f);

	C_DirectX::GetInst()->GetSprite()->SetTransform(&m_Info.matWorld);
	C_DirectX::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	C_DirectX::GetInst()->GetSprite()->Draw(m_pTexInfo->pTexture, &m_rect,
		&m_vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	C_DirectX::GetInst()->GetSprite()->End();
}
// const TEXINFO* pTexInfo = GET_SINGLE(CTextureMgr)->GetTexture(m_pObjKey);
// 
// TEXINFO* TexInfo = new TEXINFO;
// TexInfo->ImgInfo = pTexInfo->ImgInfo;
// TexInfo->pTexture = pTexInfo->pTexture;
// 
// if (TexInfo == NULL)
// return;
// 
// m_Info.vCenter = D3DXVECTOR3(pTexInfo->ImgInfo.Width / 2.f,
// 	pTexInfo->ImgInfo.Height / 2.f, 0.f);
// 
// RECT rcSrcRect = { 0, fNowHpBar, 80, 80 };
// D3DXVECTOR3 MpPos = D3DXVECTOR3(0.f, fNowHpBar, 0.f);
// 
// GET_SINGLE(CDevice)->GetSprite()->SetTransform(&m_Info.matWorld);
// GET_SINGLE(CDevice)->GetSprite()->Draw(TexInfo->pTexture, &rcSrcRect,
// 	&m_Info.vCenter, &MpPos, D3DCOLOR_ARGB(255, 255, 255, 255));

void C_LifeBar::Release()
{

}
