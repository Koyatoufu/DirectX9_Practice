#pragma once
#include "Object.h"
#include "TextureMgr.h"
class C_UI:public C_Object
{
protected:
	TCHAR* m_pTexKey;
	const TEXINFO* m_pTexInfo;
protected:
	float m_fSizeX;
	float m_fSizeY;
protected:
	RECT m_rect;
	D3DXVECTOR3 m_vCenter;
protected:
	virtual void CollCheck(){}
public:
	virtual HRESULT Initialize() = 0;
	virtual STATEID Progress() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;	
public:
	C_UI();
	virtual ~C_UI();
};

