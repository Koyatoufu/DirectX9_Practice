#pragma once
#include "StaticObj.h"

class C_Bullet:public C_StaticObj
{
private:
	float m_fDistance;
	
	D3DXMATRIX m_matChar;
	D3DXMATRIX m_matScale;
	D3DXMATRIX m_matTrans;
	D3DXMATRIX m_matBase;
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
	virtual void SetConstandTable();
private:
	void MoveBullet();
public:
	C_Bullet();
	virtual ~C_Bullet();
};

