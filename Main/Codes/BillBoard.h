#pragma once
#include "StaticObj.h"
#include "TextureMgr.h"
#include "BufferMgr.h"
class C_BillBoard:public C_StaticObj
{
protected:
	const TEXINFO* m_pTexInfo;
	D3DXMATRIX m_matViewInv;
	D3DXMATRIX m_matOrtho;
	TCHAR* m_pTexKey;
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
	virtual void SetConstandTable(){};
public:
	C_BillBoard();
	virtual ~C_BillBoard();
};

