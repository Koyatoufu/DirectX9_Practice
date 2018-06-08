#pragma once
#include "Player.h"
#include "Bullet.h"
class C_PlayerX:public C_Player
{
private:
	int m_nBulletCount;
	bool m_bBShoot;
private:
	bool m_bCharged;
	float m_fChargeTime;
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
protected:
	virtual void KeyCheck();
	virtual void MouseCheck();
	virtual void StateCheck();
private:
	void CreateCollsion(char* pFrameName,PLAYERCOLLISION PLCOLL);
public:
	C_PlayerX();
	virtual ~C_PlayerX();
};

