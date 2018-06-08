#include "StdAfx.h"
#include "ExitText.h"

#include "WinApi.h"
#include "Collision.h"

C_ExitText::C_ExitText() :C_UI()
{
}


C_ExitText::~C_ExitText()
{
	Release();
}

HRESULT C_ExitText::Initialize()
{
	m_pTexKey = L"MenuText";

	m_pTexInfo = C_TextureMgr::GetInst()->GetTexInfo(m_pTexKey);

	m_fSizeX = (float)(m_pTexInfo->TexInfo.Width);
	m_fSizeY = (float)(m_pTexInfo->TexInfo.Height);

	int nWinSizeX, nWinSizeY;
	C_WinApi::GetInst()->GetSize(nWinSizeX, nWinSizeY);

	m_vCenter = D3DXVECTOR3(m_fSizeX / 4.0f,
		m_fSizeY / 6.0f, 0.f);

	m_Info.vPosition.x = (float)nWinSizeX / 2.0f;
	m_Info.vPosition.y = (float)nWinSizeY - m_vCenter.y*2.0f;
	m_Info.vPosition.z = 0.0f;


	D3DXMatrixIdentity(&m_Info.matWorld);

	return S_OK;
}

STATEID C_ExitText::Progress()
{
	POINT	ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(C_WinApi::GetInst()->GetHwnd(), &ptMouse);

	D3DXVECTOR3 vMouse = D3DXVECTOR3((float)ptMouse.x, (float)ptMouse.y, 0.0f);

	m_bColl = C_Collision::CollSpriteMouse(vMouse, m_Info.vPosition, m_vCenter);

	CollCheck();

	m_Info.matWorld._41 = m_Info.vPosition.x;
	m_Info.matWorld._42 = m_Info.vPosition.y;
	m_Info.matWorld._43 = m_Info.vPosition.z;

	return STATE_NONE;
}

void C_ExitText::Render()
{
	C_DirectX::GetInst()->GetSprite()->SetTransform(&m_Info.matWorld);
	C_DirectX::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	C_DirectX::GetInst()->GetSprite()->Draw(m_pTexInfo->pTexture, &m_rect,
		&m_vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	C_DirectX::GetInst()->GetSprite()->End();
}

void C_ExitText::Release()
{

}

void C_ExitText::CollCheck()
{
	RECT rect = {};

	if (m_bColl)
	{
		DIMOUSESTATE mousetState = C_Input::GetInst()->GetMouseState();

		rect.left = 0;
		rect.top = LONG(m_fSizeY) - (LONG(m_fSizeY / 3.f));
		rect.right = LONG(m_fSizeX / 2.f);
		rect.bottom = LONG(m_fSizeY);
		
		if (mousetState.rgbButtons[0] & 0x80)
		{
			exit(1);
		}
	}
	else
	{
		rect.left = LONG(m_fSizeX / 2.f);
		rect.top = LONG(m_fSizeY) - (LONG(m_fSizeY / 3.f));
		rect.right = LONG(m_fSizeX);
		rect.bottom = LONG(m_fSizeY);
	}

	m_rect = rect;
}
