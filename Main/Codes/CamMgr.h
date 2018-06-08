#pragma once
#include "Define.h"
#include "DynamicCam.h"
#include "StaticCam.h"
class C_CamMgr
{
	DECLARE_SINGLETONE(C_CamMgr);
private:
	C_Camera* m_pCamera;
public:
	void Initilize(E_CAMMODE camMode);
	void SetCamera(D3DXVECTOR3 vPosition, D3DXVECTOR3 vLookAt, float fFov, float fAspect, float fZn, float fZf);
	void Progress();
	void Release();
public:
	C_CamMgr();
	~C_CamMgr();
};

