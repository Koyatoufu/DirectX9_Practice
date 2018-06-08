#include "StdAfx.h"
#include "DynamicObj.h"



C_DynamicObj::C_DynamicObj(void) :C_Object(), m_pAnimationCtrl(NULL), m_statusInfo(), m_bMove(false), m_bAtk(false), m_nCurAnimSet(0), m_nMaxAnimSet(0)
{
	for (int i = 0; i < E_ANGLE_MAX; i++)
	{
		m_arAngle[i] = 0.0f;
	}
}


C_DynamicObj::~C_DynamicObj(void)
{
}

STATUSINFO* C_DynamicObj::GetStatusInfo()
{
	return &m_statusInfo;
}

void C_DynamicObj::SetContantTable()
{
}
