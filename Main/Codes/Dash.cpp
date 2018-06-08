#include "StdAfx.h"
#include "Dash.h"
#include "MeshMgr.h"
#include "ObjMgr.h"
#include "ShaderMgr.h"
#include "Player.h"

C_Dash::C_Dash() :C_StaticObj(), m_bRender(false), m_pMatBase(NULL)
{
	D3DXMatrixIdentity(&m_matChar);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRot);
}


C_Dash::~C_Dash()
{
	Release();
}

HRESULT C_Dash::Initialize()
{
	m_sortID = SORTID_EFFECT;

	m_Info.vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.vDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Info.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Info.vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXMatrixIdentity(&m_Info.matWorld);

	D3DXMatrixScaling(&m_matScale, 0.01f, 0.01f, 0.01f);

	D3DXMatrixRotationX(&m_matRot, 3.141592f*-0.5f);
	

	m_pMeshKey = L"Dash";

	return S_OK;
}

STATEID C_Dash::Progress()
{
	C_Player* pPlayer = (C_Player*)C_ObjMgr::GetInst()->GetObj(L"Player");

	if (this == C_ObjMgr::GetInst()->GetObj(L"Dash1"))
	{
		C_MeshMgr::GetInst()->GetBoneMatrix(L"NormalX", "L_Foot", &m_matChar);
	}
	else if (this == C_ObjMgr::GetInst()->GetObj(L"Dash2"))
	{
		C_MeshMgr::GetInst()->GetBoneMatrix(L"NormalX", "R_Foot", &m_matChar);
	}

	const OBJINFO* pPlayerInfo = pPlayer->GetInfo();

	m_Info.matWorld = m_matScale * m_matRot * m_matChar * (pPlayerInfo->matWorld);

	if (!pPlayer->GetDash())
	{
		m_bAlive = false;
	}

	return STATE_NONE;
}

void C_Dash::Render()
{
	SetConstandTable();

	C_DirectX::GetInst()->SetTransformState(D3DTS_WORLD, &m_Info.matWorld);
	C_DirectX::GetInst()->SetRenderState(D3DRS_LIGHTING, false);
	C_MeshMgr::GetInst()->Mesh_Render(C_DirectX::GetInst()->GetDevice(), m_pMeshKey);
	C_DirectX::GetInst()->SetRenderState(D3DRS_LIGHTING, true);
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

void C_Dash::Release()
{

}

void C_Dash::SetConstandTable()
{
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // 알파블렌딩을 켬.
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // (As, As, As, As)
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); // (1-As, 1-As, 1-As, 1-As)
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); // 알파테스트 ALPHAREF값을 ALPHAFUNC함수로 
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0x8);  // 비교하여 프레임버퍼처리할 픽셀과 
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);  // 하지않을 픽셀을 구분.
}


