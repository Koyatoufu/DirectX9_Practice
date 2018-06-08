#pragma once
#include "BillBoard.h"
class C_BillEnemyHp:public C_BillBoard
{
private:
	D3DXMATRIX m_matEnemy;
	D3DXMATRIX m_matBill;
	D3DXMATRIX* m_pMatParent;
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
	virtual void SetConstandTable();
public:
	C_BillEnemyHp();
	C_BillEnemyHp(D3DXMATRIX* pParent);
	virtual ~C_BillEnemyHp();
};

