#include "StdAfx.h"
#include "Enemy.h"
#include "ObjMgr.h"

C_Enemy::C_Enemy() :C_DynamicObj(), m_pAi(NULL), m_pPlayerInfo(NULL)
{
}


C_Enemy::~C_Enemy()
{
}

void C_Enemy::setEnemyObjInfo(OBJINFO* pObjInfo)
{
	m_Info.vPosition = pObjInfo->vPosition;
	m_Info.vDir = pObjInfo->vDir;
	m_Info.vUp = pObjInfo->vUp;
	m_Info.vLook = pObjInfo->vLook;
}

HRESULT C_Enemy::Initialize()
{
	m_sortID = SORTID_ENEMY;

	m_pPlayerInfo = C_ObjMgr::GetInst()->GetObj(L"Player")->GetInfo();

	return S_OK;
}

