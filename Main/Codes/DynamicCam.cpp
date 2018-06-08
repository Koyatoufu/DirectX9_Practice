#include "StdAfx.h"
#include "DynamicCam.h"
#include "WinApi.h"

C_DynamicCam::C_DynamicCam() :C_Camera(), m_fCamSpeed(0.0f)
{
}


C_DynamicCam::~C_DynamicCam()
{
}

void C_DynamicCam::Initialize()
{
	m_vPos = D3DXVECTOR3(0.0f, 10.0f, -10.0f);
	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vLook, &m_vUp);
	C_DirectX::GetInst()->SetTransformState(D3DTS_VIEW, &m_matView);

	m_fFov = D3DX_PI / 4.0f;
	m_fAspect = 1.0f;
	m_fZn = 1.0f;
	m_fZf = 1000.0f;

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFov, m_fAspect,
		m_fZn, m_fZf);
	C_DirectX::GetInst()->SetTransformState(D3DTS_PROJECTION, &m_matProj);

	m_fCamSpeed = 30.0f;

}

void C_DynamicCam::Progress()
{
	KeyCheck();
	MouseCheck();
	UpdateCamera();
}

void C_DynamicCam::KeyCheck()
{
	float fForce = 0.0f;
	if (KeyDown(DIK_UP))
	{
		fForce = C_Time::GetInst()->GetTime()*m_fCamSpeed;
		MoveCamForwardBack(fForce);
	}
	if (KeyDown(DIK_DOWN))
	{
		fForce = -1.0f*(C_Time::GetInst()->GetTime()*m_fCamSpeed);
		MoveCamForwardBack(fForce);
	}
	if (KeyDown(DIK_LEFT))
	{
		fForce = -1.0f*(C_Time::GetInst()->GetTime()*m_fCamSpeed);
		MoveCamWide(fForce);
	}
	if (KeyDown(DIK_RIGHT))
	{
		fForce = C_Time::GetInst()->GetTime()*m_fCamSpeed;
		MoveCamWide(fForce);
	}

	

}

void C_DynamicCam::MouseCheck()
{
	DIMOUSESTATE mouseState = C_Input::GetInst()->GetMouseState();

	if (!(mouseState.rgbButtons[1] & 0x80))
		return;

	D3DXMATRIX matRot;
	D3DXMatrixIdentity(&matRot);

	if (mouseState.lX)
	{
		D3DXMatrixRotationAxis(&matRot, &m_vUp, D3DXToRadian(mouseState.lX / 5.0f));
	}
	if (mouseState.lY)
	{
		D3DXVECTOR3 vRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVec3Cross(&vRight, &m_vUp, &m_vDir);
		D3DXVec3Normalize(&vRight, &vRight);

		D3DXMatrixRotationAxis(&matRot, &vRight, D3DXToRadian(mouseState.lY / 5.0f));
	}

	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matRot);
	D3DXVec3TransformNormal(&m_vUp, &m_vUp, &matRot);

	m_vLook = m_vPos + m_vDir;
}

void C_DynamicCam::MoveCamForwardBack(float fForce)
{
	m_vPos += m_vDir*fForce;
	m_vLook += m_vDir*fForce;
}

void C_DynamicCam::MoveCamWide(float fForce)
{
	D3DXVECTOR3 vRIght = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3Cross(&vRIght, &m_vUp, &m_vDir);
	D3DXVec3Normalize(&vRIght, &vRIght);

	m_vPos += vRIght*fForce;
	m_vLook += vRIght*fForce;
}
