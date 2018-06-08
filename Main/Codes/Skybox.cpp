#include "StdAfx.h"
#include "Skybox.h"

#include "ObjMgr.h"
#include "DirectX.h"
#include "TextureMgr.h"
#include "BufferMgr.h"

C_Skybox::C_Skybox() :C_StaticObj(), m_pTexKey(NULL)
{
}


C_Skybox::~C_Skybox()
{
	Release();
}

HRESULT C_Skybox::Initialize()
{
	m_sortID = SORTID_SKY;

	m_Info.vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_Info.matWorld);

	m_pTexKey = L"SkyBox";
	m_pBufferKey = L"Cube";

	if (FAILED(C_TextureMgr::GetInst()->InsertTexture(C_DirectX::GetInst()->GetDevice(), TEX_CUBE, L"../../Resource/Texture/Environment/SkyBox/city.dds", m_pTexKey)))
	{
		return E_FAIL;
	}

	return S_OK;
}

STATEID C_Skybox::Progress()
{
	m_Info.vPosition.x = C_ObjMgr::GetInst()->GetObj(L"Player")->GetInfo()->vPosition.x;
	m_Info.vPosition.y = C_ObjMgr::GetInst()->GetObj(L"Player")->GetInfo()->vPosition.y;
	m_Info.vPosition.z = C_ObjMgr::GetInst()->GetObj(L"Player")->GetInfo()->vPosition.z;

	D3DXMATRIX matScale;
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixScaling(&matScale, 100.f, 100.f, 100.f);

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixTranslation(&matTrans, m_Info.vPosition.x, m_Info.vPosition.y, m_Info.vPosition.z);

	m_Info.matWorld = matScale*matTrans;

	return STATE_NONE;
}

void C_Skybox::Render()
{

	const TEXINFO* pTexInfo = C_TextureMgr::GetInst()->GetTexInfo(m_pTexKey);

	if (!pTexInfo)
		return;

	C_DirectX::GetInst()->SetTransformState(D3DTS_WORLD, &m_Info.matWorld);
	C_DirectX::GetInst()->GetDevice()->SetTexture(0, pTexInfo->pCubeTexture);

	PreRender();

	C_BufferMgr::GetInst()->Buffer_Render(C_DirectX::GetInst()->GetDevice(), m_pBufferKey);

	ResetRender();

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	C_DirectX::GetInst()->SetTransformState(D3DTS_WORLD, &matWorld);
}

void C_Skybox::Release()
{
	
}

void C_Skybox::SetConstandTable()
{

}

void C_Skybox::PreRender()
{
	C_DirectX::GetInst()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	C_DirectX::GetInst()->SetRenderState(D3DRS_ZENABLE, FALSE);
	C_DirectX::GetInst()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	C_DirectX::GetInst()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void C_Skybox::ResetRender()
{
	C_DirectX::GetInst()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	C_DirectX::GetInst()->SetRenderState(D3DRS_ZENABLE, TRUE);
	C_DirectX::GetInst()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	C_DirectX::GetInst()->SetRenderState(D3DRS_LIGHTING, true);
}
