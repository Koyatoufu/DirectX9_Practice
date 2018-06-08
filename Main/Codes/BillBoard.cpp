#include "StdAfx.h"
#include "BillBoard.h"


C_BillBoard::C_BillBoard() :C_StaticObj(), m_pTexInfo(NULL), m_pTexKey(NULL)
{
	D3DXMatrixIdentity(&m_matViewInv);
	D3DXMatrixIdentity(&m_matOrtho);
}


C_BillBoard::~C_BillBoard()
{
	Release();
}

HRESULT C_BillBoard::Initialize()
{
	m_sortID = SORTID_EFFECT;

	m_Info.vPosition = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
	m_Info.vDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Info.vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXMatrixIdentity(&m_Info.matWorld);

	m_pTexKey = L"Bill";

	m_pTexInfo=C_TextureMgr::GetInst()->GetTexInfo(m_pTexKey);

	return S_OK;
}

STATEID C_BillBoard::Progress()
{
	m_Info.matWorld._41 = m_Info.vPosition.x;
	m_Info.matWorld._42 = m_Info.vPosition.y;
	m_Info.matWorld._43 = m_Info.vPosition.z;

	D3DXMATRIX matIden;

	D3DXMatrixIdentity(&matIden);

	C_DirectX::GetInst()->GetTransform(D3DTS_VIEW, &m_matViewInv);

	D3DXMatrixInverse(&m_matViewInv, 0, &m_matViewInv);

	m_Info.matWorld.m[0][0] = m_matViewInv.m[0][0];
	m_Info.matWorld.m[0][2] = m_matViewInv.m[0][2];
	m_Info.matWorld.m[2][0] = m_matViewInv.m[2][0];
	m_Info.matWorld.m[2][2] = m_matViewInv.m[2][2];

	return STATE_NONE;
}

void C_BillBoard::Render()
{
	C_DirectX::GetInst()->GetDevice()->SetTexture(0, m_pTexInfo->pTexture);
	C_DirectX::GetInst()->SetTransformState(D3DTS_WORLD, &m_Info.matWorld);
	C_DirectX::GetInst()->SetRenderState(D3DRS_LIGHTING, false);
	C_BufferMgr::GetInst()->Buffer_Render(C_DirectX::GetInst()->GetDevice(), L"Rect");
}

void C_BillBoard::Release()
{

}

// const TEXINFO* pTexInfo = GetTexture(L"BillBoard", L"heyri");
// 
// if (pTexInfo == NULL)
// return;
// 
// GetDevice()->SetTexture(0, pTexInfo->pTexture);
// 
// D3DXMATRIX matIden;
// 
// D3DXMatrixIdentity(&matIden);
// 
// GetTransform(D3DTS_VIEW, &m_matView);
// 
// D3DXMatrixInverse(&m_matViewInv, 0, &m_matView);
// 
// 
// //y√‡∫Ù∫∏µÂ
// m_Info.matWorld.m[0][0] = m_matViewInv.m[0][0];
// m_Info.matWorld.m[0][2] = m_matViewInv.m[0][2];
// m_Info.matWorld.m[2][0] = m_matViewInv.m[2][0];
// m_Info.matWorld.m[2][2] = m_matViewInv.m[2][2];
// 
// 
// 
// 
// 
// SetTransform(D3DTS_WORLD, &m_Info.matWorld);
// SetRenderState(D3DRS_LIGHTING, false);
// Buffer_Render(GetDevice(), L"RectTexture");