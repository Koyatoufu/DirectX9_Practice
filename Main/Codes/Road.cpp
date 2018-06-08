#include "StdAfx.h"
#include "Road.h"


C_Road::C_Road() :C_StaticObj()
{
}


C_Road::~C_Road()
{
	Release();
}

HRESULT C_Road::Initialize()
{
	m_sortID = SOTRID_OBSTACLE;

	m_Info.vPosition = D3DXVECTOR3(-20.0f, 0.0f, -20.0f);
	m_Info.vDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Info.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixIdentity(&m_Info.matWorld);
	D3DXMatrixTranslation(&m_Info.matWorld, m_Info.vPosition.x, m_Info.vPosition.y, m_Info.vPosition.z);

	m_pMeshKey = L"Road";

	LPDIRECT3DDEVICE9 pDevice = C_DirectX::GetInst()->GetDevice();

	return S_OK;
}

STATEID C_Road::Progress()
{
	SetConstandTable();
	return STATE_NONE;
}

void C_Road::Render()
{
	C_DirectX::GetInst()->SetTransformState(D3DTS_WORLD, &m_Info.matWorld);

	C_ShaderMgr::GetInst()->Begin_Render(EFFECT_DEFAULT);

	C_MeshMgr::GetInst()->Mesh_Render(C_DirectX::GetInst()->GetDevice(), m_pMeshKey);
	
	C_ShaderMgr::GetInst()->End_Render(C_DirectX::GetInst()->GetDevice(),EFFECT_DEFAULT);
}

void C_Road::Release()
{
	m_pMeshKey = NULL;
}

void C_Road::SetConstandTable()
{
	LPD3DXEFFECT pEffect = C_ShaderMgr::GetInst()->GetEffect(EFFECT_DEFAULT);

	D3DXMATRIX		matView, matProj;
	C_DirectX::GetInst()->GetTransform(D3DTS_VIEW, &matView);
	C_DirectX::GetInst()->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("matWorld", &m_Info.matWorld);
	pEffect->SetMatrix("matView", &matView);
	pEffect->SetMatrix("matProj", &matProj);

	D3DXVECTOR4 vLightDir = D3DXVECTOR4(1.f, -1.f, 1.f, 0.f);
	pEffect->SetVector("vLightDir", &vLightDir);

	D3DXVECTOR4 vDiffuseMtrl = D3DXVECTOR4(1.f, 1.f, 1.f, 0.f);
	D3DXVECTOR4 vDiffuseLight = D3DXVECTOR4(1.f, 1.f, 1.f, 0.f);

	pEffect->SetVector("vDiffuseMtrl", &vDiffuseMtrl);
	pEffect->SetVector("vDiffuseLight", &vDiffuseLight);
}
