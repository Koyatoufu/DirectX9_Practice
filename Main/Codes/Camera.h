#pragma once
#include "Define.h"
#include "DirectX.h"
#include "Input.h"
#include "Time.h"
class C_Camera
{
protected:
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vLook;
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vUp;

	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;

	float m_fFov, m_fAspect, m_fZn, m_fZf;

protected:
	virtual void KeyCheck()=0;
	virtual void MouseCheck() = 0;
public:
	virtual void Initialize()=0;
	virtual void Progress()=0;
	void SetCamera(D3DXVECTOR3 vPosition, D3DXVECTOR3 vLookAt, float fFov, float fAspect, float fZn, float fZf);
protected:
	void UpdateCamera();
public:
	C_Camera();
	virtual ~C_Camera();
};

