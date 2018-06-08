#pragma once
#include "Object.h"
#include "AnimationCtrl.h"
#include "MeshMgr.h"
#include "Time.h"
#include "ShaderMgr.h"
class C_DynamicObj:public C_Object
{
protected:
	enum E_ANGLE
	{
		E_ANGLE_X,
		E_ANGLE_Y,
		E_ANGLE_Z,
		E_ANGLE_MAX
	};
protected:
	CollsionInfo m_CollBase;
protected:
	bool m_bMove;
	bool m_bAtk;
	bool m_bDie;
protected:
	float m_arAngle[E_ANGLE_MAX];
	C_AnimationCtrl* m_pAnimationCtrl;
	STATUSINFO m_statusInfo;
	int m_nCurAnimSet;
	int m_nMaxAnimSet;
public:
	virtual HRESULT Initialize() = 0;
	virtual STATEID Progress() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
protected:
	virtual void SetContantTable();
public:
	STATUSINFO* GetStatusInfo();
public:
	C_DynamicObj(void);
	virtual ~C_DynamicObj(void);
};

