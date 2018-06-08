#pragma once
#include "DynamicObj.h"
#include "AI.h"
class C_Enemy:public C_DynamicObj
{
protected:
	C_AI* m_pAi;
	OBJINFO* m_pPlayerInfo;
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
public:
	void setEnemyObjInfo(OBJINFO* pObjInfo);
public:
	C_Enemy();
	virtual ~C_Enemy();
};