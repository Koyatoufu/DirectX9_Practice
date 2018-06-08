#pragma once
#include "Define.h"
#include "DirectX.h"
class C_Object
{
protected:
	OBJINFO m_Info;
	SORTID m_sortID;
	STATEID m_StateID;
protected:
	const TCHAR* m_pMeshKey;
	const TCHAR* m_pBufferKey;
	const TCHAR* m_pTexKey;
protected:
	bool m_bAlive;
	bool m_bColl;
public:
	virtual HRESULT Initialize() = 0;
	virtual STATEID Progress()= 0;
	virtual void Render() = 0;
	virtual void Release()=0;
protected:
	virtual void SetContantTable(){}
	virtual void CheckCollision(){}
public:
	SORTID GetSortID();
	OBJINFO* GetInfo();
	bool GetAllive();
public:
	C_Object(void);
	C_Object(const C_Object&);
	virtual ~C_Object(void);
};

