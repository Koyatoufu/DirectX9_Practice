#include "StdAfx.h"
#include "StaticCam.h"


C_StaticCam::C_StaticCam() :C_Camera(), m_fDistance(0.0f), m_pInfo(NULL), m_fRotX(0.0f), m_fRotY(0.0f), m_fPosX(0.0f)
{
}


C_StaticCam::~C_StaticCam()
{
}

void C_StaticCam::Initialize()
{
	m_pInfo = C_ObjMgr::GetInst()->GetObj(L"Player")->GetInfo();

	m_fRotX = D3DXToRadian(20.f);
	m_fDistance = 5.0f;

	D3DXVECTOR3		vTmpDir = m_pInfo->vDir * -1.f * m_fDistance;

	D3DXVECTOR3		vRight;
	D3DXVec3Cross(&vRight, &m_pInfo->vUp, &m_pInfo->vDir);

	D3DXMATRIX		matAxis;
	D3DXMatrixRotationAxis(&matAxis, &vRight, m_fRotX);

	D3DXVec3TransformNormal(&vTmpDir, &vTmpDir, &matAxis);

	m_vPos = m_pInfo->vPosition + vTmpDir;

	m_vLook = m_pInfo->vPosition;
	m_vDir = m_vLook - m_vPos;
	
	m_vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXVECTOR3 vTmp = D3DXVECTOR3(0.0f,0.0f,1.0f);
	D3DXMATRIX matTmp;
	D3DXMatrixIdentity(&matTmp);
	float fDot = D3DXVec3Dot(&vTmp, &m_vDir);
	float fRid = acos(fDot);
	D3DXMatrixRotationX(&matTmp,fRid);
	D3DXVec3TransformNormal(&m_vUp, &m_vUp, &matTmp);
	
	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vLook, &m_vUp);
	C_DirectX::GetInst()->SetTransformState(D3DTS_VIEW, &m_matView);

	m_fFov = D3DX_PI / 4.0f;
	m_fAspect = 1.0f;
	m_fZn = 1.0f;
	m_fZf = 1000.0f;

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFov, m_fAspect, m_fZn, m_fZf);
	C_DirectX::GetInst()->SetTransformState(D3DTS_PROJECTION, &m_matProj);

}
void C_StaticCam::Progress()
{
	UpdateCamera();

	KeyCheck();
	MouseCheck();

	UpdateStaticCamState();
	
}

void C_StaticCam::KeyCheck()
{
	float fTime = C_Time::GetInst()->GetTime();
	float fRid = D3DXToRadian(90.0f*fTime);

	if (KeyDown(DIK_UP))
	{
		m_fRotX += fRid;
		if (m_fRotX>=D3DXToRadian(70))
		{
			m_fRotX = D3DXToRadian(70);
		}
	}
	if (KeyDown(DIK_DOWN))
	{
		m_fRotX -= fRid;
		if (m_fRotX <= -D3DXToRadian(70))
		{
			m_fRotX = -D3DXToRadian(70);
		}
	}
	if (KeyDown(DIK_LEFT))
	{
		m_fRotY -= fRid;
		if (m_fRotY <= -D3DXToRadian(90))
		{
			m_fRotY = -D3DXToRadian(90);
		}
	}
	if (KeyDown(DIK_RIGHT))
	{
		m_fRotY += fRid;
		if (m_fRotY >= D3DXToRadian(90))
		{
			m_fRotY = D3DXToRadian(90);
		}
	}

	if (KeyDown(DIK_LSHIFT))
	{
		m_fRotX = D3DXToRadian(20.0f);
		m_fRotY = 0.0f;
	}
	
}

void C_StaticCam::MouseCheck()
{
	//캐릭터방향벡터를 중심으로 디스턴스의 배까지 원을 그려 그 사이에 충돌 걸리는 객체에 록온을 검(왼쪽버튼시)
	DIMOUSESTATE mouseState = C_Input::GetInst()->GetMouseState();

	if (mouseState.lZ)
	{
		m_fDistance += (mouseState.lZ / 80.0f)*C_Time::GetInst()->GetTime()*100;
		if (m_fDistance<2.0f)
		{
			m_fDistance = 2.0f;
		}
		if (m_fDistance>10.0f)
		{
			m_fDistance = 10.0f;
		}
	}

	if (!(mouseState.rgbButtons[1] & 0x80))
		return;
}

void C_StaticCam::UpdateStaticCamState()
{
	D3DXVECTOR3		vTmpDir = m_pInfo->vDir * -1.f * m_fDistance;

	D3DXVECTOR3		vRight;
	D3DXVec3Cross(&vRight, &m_pInfo->vUp, &m_pInfo->vDir);

	D3DXMATRIX		matAxis;
	D3DXMATRIX		matAxis2;
	D3DXMatrixRotationAxis(&matAxis, &vRight, m_fRotX);

	D3DXMatrixRotationAxis(&matAxis2, &m_pInfo->vUp, m_fRotY);

	D3DXVec3TransformNormal(&vTmpDir, &vTmpDir, &matAxis);
	D3DXVec3TransformNormal(&vTmpDir, &vTmpDir, &matAxis2);

	m_vPos = m_pInfo->vPosition + vTmpDir;

	m_vLook = m_pInfo->vPosition;

	m_vDir = m_vLook - m_vPos;

	m_vUp = m_pInfo->vUp;
}
