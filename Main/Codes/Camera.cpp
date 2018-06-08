#include "StdAfx.h"
#include "Camera.h"


C_Camera::C_Camera() :m_vPos(0.0f, 0.0f, 0.0f),
m_vLook(0.0f, 0.0f, 0.0f), m_vDir(0.0f, 0.0f, 0.0f), m_vUp(0.0f, 0.0f, 0.0f),
m_fFov(0.0f), m_fAspect(0.0f), m_fZn(0.0f), m_fZf(0.0f)
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}


C_Camera::~C_Camera()
{
}

void C_Camera::SetCamera(D3DXVECTOR3 vPosition, D3DXVECTOR3 vLookAt, float fFov, float fAspect, float fZn, float fZf)
{
	m_vPos = vPosition;
	m_vLook = vLookAt;
	m_vDir = vLookAt - vPosition;
	D3DXVec3Normalize(&m_vDir, &m_vDir);
	float fDot = D3DXVec3Dot(&m_vDir, &m_vLook);
	float fRadius = acos(1.0f-fDot);

	D3DXMATRIX matRot;
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixRotationZ(&matRot, fRadius);

	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vLook, &m_vUp);
	C_DirectX::GetInst()->SetTransformState(D3DTS_VIEW, &m_matView);

	m_fFov = fFov;
	m_fAspect = fAspect;
	m_fZn = fZn;
	m_fZf = fZf;

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFov, m_fAspect, m_fZn, m_fZf);
	C_DirectX::GetInst()->SetTransformState(D3DTS_PROJECTION, &m_matProj);
}

void C_Camera::UpdateCamera()
{
	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vLook, &m_vUp);
	C_DirectX::GetInst()->SetTransformState(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFov, m_fAspect, m_fZn, m_fZf);
	C_DirectX::GetInst()->SetTransformState(D3DTS_PROJECTION, &m_matProj);
}
