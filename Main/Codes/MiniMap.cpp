#include "StdAfx.h"
#include "MiniMap.h"
#include "WinApi.h"


C_MiniMap::C_MiniMap() :C_UI()
{
}


C_MiniMap::~C_MiniMap()
{
	Release();
}

HRESULT C_MiniMap::Initialize()
{
	m_sortID = SORTID_UI;

	int nWinSizeX = 0, nWinSizeY = 0;

	C_WinApi::GetInst()->GetSize(nWinSizeX, nWinSizeY);

	m_pTexKey = L"MiniMap";

	if (FAILED(C_TextureMgr::GetInst()->InsertTexture(C_DirectX::GetInst()->GetDevice(), TEX_GENERAL, L"../../Resource/Texture/UI/MiniMap.png", m_pTexKey)))
	{
		return E_FAIL;
	}

	m_pTexInfo = C_TextureMgr::GetInst()->GetTexInfo(m_pTexKey);

	m_vCenter = D3DXVECTOR3(m_pTexInfo->TexInfo.Width / 2.f,
		m_pTexInfo->TexInfo.Height / 2.f, 0.f);

	m_Info.vPosition.x = (float)nWinSizeX-m_vCenter.x;
	m_Info.vPosition.y = m_vCenter.y;
	m_Info.vPosition.z = 0.0f;

	m_fSizeX = (float)(m_pTexInfo->TexInfo.Width);
	m_fSizeY = (float)(m_pTexInfo->TexInfo.Height);

	D3DXMatrixIdentity(&m_Info.matWorld);

	RECT		rect = { LONG(m_Info.vPosition.x - m_fSizeX / 2.f)
		, LONG(m_Info.vPosition.y - m_fSizeY / 2.f)
		, LONG(m_Info.vPosition.x + m_fSizeX / 2.f)
		, LONG(m_Info.vPosition.y + m_fSizeY / 2.f) };

	m_rect = rect;

	return S_OK;
}

STATEID C_MiniMap::Progress()
{
	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(C_WinApi::GetInst()->GetHwnd(), &ptMouse);

	D3DXMatrixTranslation(&m_Info.matWorld, m_Info.vPosition.x, m_Info.vPosition.y, m_Info.vPosition.z);

	return STATE_NONE;
}

void C_MiniMap::Render()
{
	C_DirectX::GetInst()->GetSprite()->SetTransform(&m_Info.matWorld);
	C_DirectX::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	C_DirectX::GetInst()->GetSprite()->Draw(m_pTexInfo->pTexture,NULL,
		&m_vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	C_DirectX::GetInst()->GetSprite()->End();
}

void C_MiniMap::Release()
{

}
