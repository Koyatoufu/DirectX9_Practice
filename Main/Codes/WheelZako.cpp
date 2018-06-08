#include "StdAfx.h"
#include "WheelZako.h"

C_WheelZako::C_WheelZako() :C_Enemy()
{
}


C_WheelZako::~C_WheelZako()
{
}

HRESULT C_WheelZako::Initialize()
{
	C_Enemy::Initialize();

	m_pMeshKey = L"WheelZako";

	if (FAILED(C_MeshMgr::GetInst()->CloneMesh(C_DirectX::GetInst()->GetDevice(), m_pMeshKey, &m_pAnimationCtrl)))
	{
		return E_FAIL;
	}

	m_Info.vPosition = D3DXVECTOR3(-5.0f, 0.0f, -5.0f);
	m_Info.vDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Info.vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Info.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixIdentity(&m_Info.matWorld);

	m_nCurAnimSet = 1;

	return S_OK;
}

STATEID C_WheelZako::Progress()
{
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, m_Info.vPosition.x, m_Info.vPosition.y, m_Info.vPosition.z);
	m_Info.matWorld = matTrans;

	return STATE_NONE;
}

void C_WheelZako::Render()
{
	SetContantTable();

	C_DirectX::GetInst()->SetTransformState(D3DTS_WORLD, &m_Info.matWorld);
	C_ShaderMgr::GetInst()->Begin_Render(EFFECT_TEST);

	m_pAnimationCtrl->FrameMove(m_pMeshKey, C_Time::GetInst()->GetTime());

	m_pAnimationCtrl->SetAnimationSet(m_nCurAnimSet);

	C_MeshMgr::GetInst()->Mesh_Render(C_DirectX::GetInst()->GetDevice(), m_pMeshKey);

	C_ShaderMgr::GetInst()->End_Render(C_DirectX::GetInst()->GetDevice(), EFFECT_TEST);
}

void C_WheelZako::Release()
{

}

void C_WheelZako::SetContantTable()
{
	LPD3DXEFFECT pEffect = C_ShaderMgr::GetInst()->GetEffect(EFFECT_TEST);

	D3DXMATRIX		matView, matProj;
	C_DirectX::GetInst()->GetTransform(D3DTS_VIEW, &matView);
	C_DirectX::GetInst()->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("matWorld", &m_Info.matWorld);
	pEffect->SetMatrix("matView", &matView);
	pEffect->SetMatrix("matProj", &matProj);
}
