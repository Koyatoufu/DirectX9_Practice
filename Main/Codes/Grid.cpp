#include "StdAfx.h"
#include "Grid.h"


C_Grid::C_Grid()
{
}


C_Grid::~C_Grid()
{
	Release();
}

HRESULT C_Grid::Initialize()
{
	m_sortID = SORTID_TERRAIN;
	m_Info.vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.vDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Info.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixIdentity(&m_Info.matWorld);

	m_pBufferKey = L"Grid";

	LPDIRECT3DDEVICE9 pDevice=C_DirectX::GetInst()->GetDevice();

	if (FAILED(C_BufferMgr::GetInst()->AddBuffer(pDevice, m_pBufferKey, BUFF_GRID)))
	{
		return E_FAIL;
	}

	return S_OK;
}

STATEID C_Grid::Progress()
{
	return STATE_NONE;
}

void C_Grid::Render()
{
	C_DirectX::GetInst()->SetTransformState(D3DTS_WORLD, &m_Info.matWorld);

	C_DirectX::GetInst()->SetRenderState(D3DRS_LIGHTING, false);
	C_BufferMgr::GetInst()->Buffer_Render(C_DirectX::GetInst()->GetDevice(), m_pBufferKey);
	C_DirectX::GetInst()->SetRenderState(D3DRS_LIGHTING, true);
}

void C_Grid::Release()
{
	m_pBufferKey = NULL;
}
