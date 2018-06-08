#pragma once
#include "DynamicObj.h"
#include "Input.h"
#include "ShaderMgr.h"
#include "ObjMgr.h"
#include "Dash.h"
class C_Player:public C_DynamicObj
{
protected:
	CollsionInfo m_arCollsionInfo[PlCOLL_MAX];
	float m_fMoveForce;
	float m_fDashForce;
	bool m_bDash;
	bool m_bJump;
	float m_fDashIntervalTime;
	float m_fAtkIntervalTime;
	float m_fFrontRid;
	float m_fShiftTerm;
protected:
	virtual void KeyCheck();
	virtual void MouseCheck();
	virtual void StateCheck();
protected:
	virtual void SetContantTable();
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress()=0;
	virtual void Render();
	virtual void Release();
public:
	bool GetDash();
public:
	C_Player();
	virtual ~C_Player();
};

