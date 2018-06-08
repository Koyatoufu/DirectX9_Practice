#include "StdAfx.h"
#include "PlayerX.h"

#include "Factory.h"
#include "ObjMgr.h"

C_PlayerX::C_PlayerX() :C_Player(), m_bCharged(false), m_fChargeTime(0.0f), m_nBulletCount(0), m_bBShoot(false)
{
}


C_PlayerX::~C_PlayerX()
{
	Release();
}

HRESULT C_PlayerX::Initialize()
{
	C_Player::Initialize();

	m_pMeshKey = L"NormalX";

	LPDIRECT3DDEVICE9 pDevice = C_DirectX::GetInst()->GetDevice();

	if (FAILED(C_MeshMgr::GetInst()->AddMesh(pDevice, L"../../Resource/Mesh/Dynamic/Player/NormalX/"
		, L"NormalX.x", m_pMeshKey, MESH_DYNAMIC)))
		return E_FAIL;

	if (FAILED(C_MeshMgr::GetInst()->CloneMesh(pDevice, m_pMeshKey, &m_pAnimationCtrl)))
	{
		return E_FAIL;
	}

	LPD3DXANIMATIONCONTROLLER* pAnim = m_pAnimationCtrl->GetAniCtrl();

	m_nMaxAnimSet = (*pAnim)->GetNumAnimationSets();
	m_nCurAnimSet = 0;

	m_pAnimationCtrl->SetAnimationSet(m_nCurAnimSet);

	m_statusInfo.fMaxLife = 100.0f;
	m_statusInfo.fMaxEnergy = 100.0f;
	m_statusInfo.fLife = m_statusInfo.fMaxLife;
	m_statusInfo.fEnergy = m_statusInfo.fMaxEnergy;
	m_statusInfo.fAtk = 10.0f;

	m_fDashForce = 10.0f;
	m_fMoveForce = 2.0f;

	m_fDashIntervalTime = 0.3f;
	m_fAtkIntervalTime = 0.5f;

	CreateCollsion("Helmet_Regroup02_005", PlCOLL_HEAD);
	CreateCollsion("upper_body_Regroup02_001", PlCOLL_BODY);
	CreateCollsion("arms_Regroup04_001", PlCOLL_ARM);
	CreateCollsion("lower_body_Regroup02_004", PlCOLL_LEG);

	return S_OK;
}

STATEID C_PlayerX::Progress()
{
	m_bMove = false;
	m_bDash = false;

	D3DXMATRIX matRot;
	D3DXMatrixRotationY(&matRot, m_arAngle[E_ANGLE_Y]);

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, m_Info.vPosition.x, m_Info.vPosition.y, m_Info.vPosition.z);

	m_Info.matWorld = matRot*matTrans;

	KeyCheck();
	MouseCheck();
	StateCheck();

	return STATE_NONE;
}

void C_PlayerX::Render()
{
	SetContantTable();

	C_Player::Render();
}

void C_PlayerX::Release()
{
	C_Player::Release();
}

void C_PlayerX::KeyCheck()
{
	C_Player::KeyCheck();

	if (KeyDown(DIK_RSHIFT))
	{
		if (m_fAtkIntervalTime >= 0.0f)
		{
			m_bAtk = true;
		}
	}
}

void C_PlayerX::MouseCheck()
{
	C_Player::MouseCheck();


	DIMOUSESTATE mousetState = C_Input::GetInst()->GetMouseState();
	if (mousetState.rgbButtons[0] & 0x80)
	{
		if (m_fAtkIntervalTime >= 0.0f)
		{
			m_bAtk = true;
		}
	}
	if (mousetState.rgbButtons[1] & 0x80)
	{
		m_statusInfo.fEnergy -= 10.0f*C_Time::GetInst()->GetTime();
		if (m_statusInfo.fEnergy < 0.0f)
		{
			m_statusInfo.fEnergy = 0.0f;
		}
	}
}

void C_PlayerX::StateCheck()
{
	m_nCurAnimSet = 0;

	if (m_bMove)
	{
		m_Info.vPosition += m_Info.vLook*m_fMoveForce*C_Time::GetInst()->GetTime();
		m_nCurAnimSet = 4;
	}
	if (m_bDash)
	{
		m_Info.vPosition += m_Info.vLook*m_fDashForce*C_Time::GetInst()->GetTime();
		m_nCurAnimSet = 9;
	}
	if (m_bAtk)
	{
		m_nCurAnimSet = 2;
		if (m_bMove)
		{
			m_nCurAnimSet = 5;
		}
		if (m_bDash)
		{
			m_nCurAnimSet = 10;

		}

		if (!m_bBShoot)
		{
			TCHAR szTmp[128];
			swprintf_s(szTmp, L"Bullet%d", m_nBulletCount);
			C_ObjMgr::GetInst()->InsertObject(szTmp, C_Factory<C_Object, C_Bullet>::CreateFactoryOjbect());
			m_nBulletCount++;
			m_bBShoot = true;
			if (m_nBulletCount>256)
			{
				m_nBulletCount = 0;
			}
		}

		m_fAtkIntervalTime -= C_Time::GetInst()->GetTime();
		if (m_fAtkIntervalTime<=0.0f)
		{
			m_bAtk = false;
			m_bBShoot = false;
			m_fAtkIntervalTime = 0.5f;
		}
	}
}

void C_PlayerX::CreateCollsion(char* pFrameName, PLAYERCOLLISION PLCOLL)
{
	D3DXFRAME frameTmp;
	C_MeshMgr::GetInst()->GetFrame(m_pMeshKey, pFrameName, &frameTmp);

	void* pVtx = NULL;

	frameTmp.pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pVtx);

	DWORD dwVtxCnt = frameTmp.pMeshContainer->MeshData.pMesh->GetNumVertices();
	DWORD dwVtxFVF = frameTmp.pMeshContainer->MeshData.pMesh->GetFVF();
	UINT nVtxSize = D3DXGetFVFVertexSize(dwVtxFVF);

	D3DXComputeBoundingBox((D3DXVECTOR3*)pVtx, dwVtxCnt, nVtxSize, &m_arCollsionInfo[PLCOLL].vMin, &m_arCollsionInfo[PLCOLL].vMax);

	frameTmp.pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
}
