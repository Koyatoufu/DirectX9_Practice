#pragma once
#include "StaticObj.h"
class C_Dash:public C_StaticObj
{
private:
	bool m_bRender;
	D3DXMATRIX* m_pMatBase;

	D3DXMATRIX m_matChar;
	D3DXMATRIX m_matScale;
	D3DXMATRIX m_matRot;
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
	virtual void SetConstandTable();
public:
	C_Dash();
	virtual ~C_Dash();
};

