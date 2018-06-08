#pragma once
#include "Define.h"
#include "HashTable.h"
#include "Object.h"
class C_ObjMgr
{
	DECLARE_SINGLETONE(C_ObjMgr);
public:
	C_HashTable m_hashTable;
public:
	void InsertObject(const TCHAR* pObjectKey,C_Object* pObject);
	STATEID Progress();
	void Render();
	void Release();
public:
	C_Object* GetObj(const TCHAR* pObjectKey);
private:
	C_ObjMgr();
public:
	~C_ObjMgr();
};

