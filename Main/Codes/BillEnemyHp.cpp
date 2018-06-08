#include "StdAfx.h"
#include "BillEnemyHp.h"


C_BillEnemyHp::C_BillEnemyHp() :C_BillBoard()
{
}

C_BillEnemyHp::C_BillEnemyHp(D3DXMATRIX* pParent) : C_BillBoard(), m_pMatParent(pParent)
{
}


C_BillEnemyHp::~C_BillEnemyHp()
{
}

HRESULT C_BillEnemyHp::Initialize()
{
	m_sortID = SORTID_UI;

	D3DXMatrixIdentity(&m_Info.matWorld);

	m_Info.vPosition = D3DXVECTOR3(0.0f, 3.0f, 0.0f);

	return S_OK;
}

STATEID C_BillEnemyHp::Progress()
{
	D3DXMATRIX			matScale;
	D3DXMATRIX			matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 0.2f, 1.f);

	D3DXMatrixTranslation(&matTrans, m_Info.vPosition.x, m_Info.vPosition.y, m_Info.vPosition.z);

	D3DXMATRIX			matView;

	C_DirectX::GetInst()->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixIdentity(&m_matBill);

	m_matBill = matView;
	m_matBill._41 = 0.f;
	m_matBill._42 = 0.f;
	m_matBill._43 = 0.f;

	D3DXMatrixInverse(&m_matBill, 0, &m_matBill);

	m_Info.matWorld = matScale * m_matBill * matTrans * (*m_pMatParent);

	return STATE_NONE;
}

void C_BillEnemyHp::Render()
{
	C_DirectX::GetInst()->GetDevice()->SetTexture(0, NULL);

	C_DirectX::GetInst()->SetTransformState(D3DTS_WORLD, &(m_Info.matWorld));

	C_BufferMgr::GetInst()->Buffer_Render(C_DirectX::GetInst()->GetDevice(), L"RectColor");
}

void C_BillEnemyHp::Release()
{

}

void C_BillEnemyHp::SetConstandTable()
{

}
