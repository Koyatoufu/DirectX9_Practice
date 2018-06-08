#include "StdAfx.h"
#include "Bullet.h"

#include "MeshMgr.h"
#include "BufferMgr.h"
#include "ObjMgr.h"
#include "Time.h"

C_Bullet::C_Bullet() :C_StaticObj(), m_fDistance(0.0f)
{
	D3DXMatrixIdentity(&m_matChar);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matTrans);
	D3DXMatrixIdentity(&m_matBase);
}


C_Bullet::~C_Bullet()
{
	Release();
}

HRESULT C_Bullet::Initialize()
{
	m_sortID = SORTID_EFFECT;

	m_fDistance = 50.0f;

	const OBJINFO* pPlayerInfo = C_ObjMgr::GetInst()->GetObj(L"Player")->GetInfo();

	m_matBase = pPlayerInfo->matWorld;

	m_Info.vPosition = pPlayerInfo->vPosition;
	m_Info.vDir = pPlayerInfo->vDir;
	m_Info.vUp = pPlayerInfo->vUp;
	m_Info.vLook = pPlayerInfo->vLook;
	
	D3DXMATRIX matTmp;
	D3DXMatrixIdentity(&matTmp);
	C_MeshMgr::GetInst()->GetBoneMatrix(L"NormalX", "L_Hand_end", &matTmp);
	m_matChar._41 = matTmp._41;
	m_matChar._42 = matTmp._42;
	m_matChar._43 = matTmp._43;

	D3DXMatrixIdentity(&m_Info.matWorld);

	D3DXMatrixScaling(&m_matScale, 0.001f, 0.001f, 0.001f);

	m_pMeshKey = L"Bullet";

	return S_OK;
}

STATEID C_Bullet::Progress()
{

	MoveBullet();

	m_Info.matWorld = m_matScale * m_matChar * m_matBase;

	return STATE_NONE;
}

void C_Bullet::Render()
{
	SetConstandTable();

	C_DirectX::GetInst()->SetTransformState(D3DTS_WORLD, &m_Info.matWorld);
	C_DirectX::GetInst()->SetRenderState(D3DRS_LIGHTING, false);
	C_MeshMgr::GetInst()->Mesh_Render(C_DirectX::GetInst()->GetDevice(), m_pMeshKey);

	C_DirectX::GetInst()->SetRenderState(D3DRS_LIGHTING, true);
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

void C_Bullet::Release()
{

}

void C_Bullet::SetConstandTable()
{
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // 알파블렌딩을 켬.
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // (As, As, As, As)
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); // (1-As, 1-As, 1-As, 1-As)
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); // 알파테스트 ALPHAREF값을 ALPHAFUNC함수로 
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0x8);  // 비교하여 프레임버퍼처리할 픽셀과 
	C_DirectX::GetInst()->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);  // 하지않을 픽셀을 구분.
}

void C_Bullet::MoveBullet()
{
	const OBJINFO* pPlayerInfo = C_ObjMgr::GetInst()->GetObj(L"Player")->GetInfo();

	if (m_bAlive)
	{
		m_Info.vPosition += m_Info.vLook*C_Time::GetInst()->GetTime()*10.0f;
		D3DXVECTOR3 vTmp = m_Info.vPosition - pPlayerInfo->vPosition;
		float fDistance = D3DXVec3Length(&vTmp);

		if (fDistance >= 5.0f)
		{
			m_bAlive = false;
		}
		else
		{
			D3DXMatrixTranslation(&m_matBase, m_Info.vPosition.x, m_Info.vPosition.y, m_Info.vPosition.z);
		}
		return;
	}
}
