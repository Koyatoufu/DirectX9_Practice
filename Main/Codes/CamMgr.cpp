#include "StdAfx.h"
#include "CamMgr.h"

IMPLEMENT_SINGLETONE(C_CamMgr);

C_CamMgr::C_CamMgr() :m_pCamera(NULL)
{
}


C_CamMgr::~C_CamMgr()
{
}

void C_CamMgr::Initilize(E_CAMMODE camMode)
{
	if (m_pCamera)
		return;

	switch (camMode)
	{
	case CAMMODE_STATIC:
		m_pCamera = new C_StaticCam();
		break;
	case CAMMODE_DYNAMIC:
		m_pCamera = new C_DynamicCam();
		break;
	default:
		break;
	}

	if (!m_pCamera)
		return;

	m_pCamera->Initialize();
}

void C_CamMgr::SetCamera(D3DXVECTOR3 vPosition, D3DXVECTOR3 vLookAt, float fFov, float fAspect, float fZn, float fZf)
{
	m_pCamera->SetCamera(vPosition, vLookAt, fFov, fAspect, fZn, fZf);
}

void C_CamMgr::Progress()
{
	m_pCamera->Progress();
}

void C_CamMgr::Release()
{
	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}
}
