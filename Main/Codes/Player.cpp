#include "StdAfx.h"
#include "Player.h"

#include "Time.h"
#include "CamMgr.h"

#include "Factory.h"
#include "ObjMgr.h"
#include "Dash.h"

C_Player::C_Player() :C_DynamicObj(), m_fMoveForce(0.0f), m_fDashForce(0.0f), m_bDash(false),m_bJump(false),
m_fDashIntervalTime(0.0f), m_fFrontRid(0.0f),m_fShiftTerm(0.0f)
{
}


C_Player::~C_Player()
{
	Release();
}

HRESULT C_Player::Initialize()
{
	m_sortID = SORTID_PLAYER;

	OBJINFO* pStartInfo=C_ObjMgr::GetInst()->GetObj(L"Road1")->GetInfo();

	m_Info.vPosition = pStartInfo->vPosition+D3DXVECTOR3(20.0f,0.0f,20.0f);
	m_Info.vDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Info.vLook = D3DXVECTOR3(0.0f,0.0f,1.0f);
	m_Info.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixIdentity(&m_Info.matWorld);

	m_arAngle[E_ANGLE_Y] = D3DX_PI;	
	m_fFrontRid = D3DX_PI;

	m_fShiftTerm = 0.5f;

	return S_OK;
}

void C_Player::Render()
{
	C_DirectX::GetInst()->SetTransformState(D3DTS_WORLD, &m_Info.matWorld);
	C_ShaderMgr::GetInst()->Begin_Render(EFFECT_TEST);

	m_pAnimationCtrl->FrameMove(m_pMeshKey, C_Time::GetInst()->GetTime());

	m_pAnimationCtrl->SetAnimationSet(m_nCurAnimSet);

	C_MeshMgr::GetInst()->Mesh_Render(C_DirectX::GetInst()->GetDevice(), m_pMeshKey);

	C_ShaderMgr::GetInst()->End_Render(C_DirectX::GetInst()->GetDevice(),EFFECT_TEST);
}

void C_Player::Release()
{
	m_pMeshKey = NULL;

	if (m_pAnimationCtrl)
	{
		m_pAnimationCtrl = NULL;
	}
}

void C_Player::KeyCheck()
{
	D3DXVECTOR3 vRight=D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVec3Cross(&vRight, &m_Info.vDir, &m_Info.vUp);
	D3DXVec3Normalize(&vRight, &vRight);
	float fDot = 0.0f, fRid = 0.0f;
	D3DXMATRIX matRot;
	D3DXMatrixIdentity(&matRot);

	if (KeyDown(DIK_W))
	{
		m_arAngle[E_ANGLE_Y] = m_fFrontRid;
		m_Info.vLook = m_Info.vDir;
		m_bMove = true;
	}
	if (KeyDown(DIK_S))
	{
		m_arAngle[E_ANGLE_Y] = m_fFrontRid + D3DXToRadian(180.0f);
		m_Info.vLook = -m_Info.vDir;
		m_bMove = true;
	}
	if (KeyDown(DIK_D))
	{
		fDot = D3DXVec3Dot(&vRight, &m_Info.vDir);
		fRid = acos(fDot);

		m_arAngle[E_ANGLE_Y] = m_fFrontRid + fRid;

		m_Info.vLook = -vRight;

		D3DXMatrixIdentity(&matRot);

		if (KeyDown(DIK_W))
		{
			fRid = m_arAngle[E_ANGLE_Y] - D3DXToRadian(45.0f);
			m_arAngle[E_ANGLE_Y] = fRid;
			D3DXMatrixRotationY(&matRot, -D3DXToRadian(45.0f));
			D3DXVec3TransformNormal(&m_Info.vLook, &m_Info.vLook, &matRot);
		}
		else if (KeyDown(DIK_S))
		{
			fRid = m_arAngle[E_ANGLE_Y] + D3DXToRadian(45.0f);
			m_arAngle[E_ANGLE_Y] = fRid;
			D3DXMatrixRotationY(&matRot, D3DXToRadian(45.0f));
			D3DXVec3TransformNormal(&m_Info.vLook, &m_Info.vLook, &matRot);
		}

		m_bMove = true;
	}
	if (KeyDown(DIK_A))
	{
		float fTmp = m_arAngle[E_ANGLE_Y];
		fDot = D3DXVec3Dot(&vRight, &m_Info.vDir);
		fRid = acos(fDot);
		
		m_arAngle[E_ANGLE_Y] = m_fFrontRid - fRid;

		m_Info.vLook = vRight;

		D3DXMatrixIdentity(&matRot);
		if (KeyDown(DIK_W))
		{
			fRid = m_arAngle[E_ANGLE_Y] + D3DXToRadian(45.0f);
			m_arAngle[E_ANGLE_Y] = fRid;
			D3DXMatrixRotationY(&matRot, D3DXToRadian(45.0f));
			D3DXVec3TransformNormal(&m_Info.vLook, &m_Info.vLook, &matRot);
		}
		else if (KeyDown(DIK_S))
		{
			fRid = m_arAngle[E_ANGLE_Y] - D3DXToRadian(45.0f);
			m_arAngle[E_ANGLE_Y] = fRid;
			D3DXMatrixRotationY(&matRot, -D3DXToRadian(45.0f));
			D3DXVec3TransformNormal(&m_Info.vLook, &m_Info.vLook, &matRot);
		}

		m_bMove = true;
	}
	
	if (KeyDown(DIK_SPACE))
	{
		float fTime = C_Time::GetInst()->GetTime();
		m_fDashIntervalTime -= fTime;
		if (m_fDashIntervalTime>0.0f)
		{
			m_bDash = true;
			if (!C_ObjMgr::GetInst()->GetObj(L"Dash1"))
			{
				C_ObjMgr::GetInst()->InsertObject(L"Dash1", C_Factory<C_Object, C_Dash>::CreateFactoryOjbect());
			}
			if (!C_ObjMgr::GetInst()->GetObj(L"Dash2"))
			{
				C_ObjMgr::GetInst()->InsertObject(L"Dash2", C_Factory<C_Object, C_Dash>::CreateFactoryOjbect());
			}
		}
		else
		{
			m_bDash = false;
		}
	}
	else
	{
		m_fDashIntervalTime = 0.3f;
	}
	if (KeyDown(DIK_LCONTROL))
	{
		if (!m_bJump)
		{
			m_bJump = true;
		}
	}

	if (KeyDown(DIK_LSHIFT))
	{
		if (m_fShiftTerm>=0.5f)
		{
			fDot = D3DXVec3Dot(&m_Info.vDir, &m_Info.vLook);
			D3DXVec3TransformNormal(&m_Info.vDir, &D3DXVECTOR3(0.0f, 0.0f, -1.0f), &m_Info.matWorld);
			D3DXVec3TransformNormal(&m_Info.vUp, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &m_Info.matWorld);
			m_Info.vLook = m_Info.vDir;
			m_fFrontRid = m_arAngle[E_ANGLE_Y];
			m_fShiftTerm = 0.0f;
		}
	}
	else
	{
		m_fShiftTerm += C_Time::GetInst()->GetTime();
		if (m_fShiftTerm>0.5f)
		{
			m_fShiftTerm = 0.5f;
		}
	}
}

void C_Player::MouseCheck()
{
}

void C_Player::StateCheck()
{
}

void C_Player::SetContantTable()
{
	LPD3DXEFFECT pEffect = C_ShaderMgr::GetInst()->GetEffect(EFFECT_TEST);

	D3DXMATRIX		matView, matProj;
	C_DirectX::GetInst()->GetTransform(D3DTS_VIEW, &matView);
	C_DirectX::GetInst()->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("matWorld", &m_Info.matWorld);
	pEffect->SetMatrix("matView", &matView);
	pEffect->SetMatrix("matProj", &matProj);
}

bool C_Player::GetDash()
{
	return m_bDash;
}


