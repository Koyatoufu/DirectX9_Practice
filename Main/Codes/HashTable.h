#pragma once
#include "Define.h"
class C_HashTable
{
public:
	typedef struct tagDataSet
	{
		const TCHAR* pKey;
		void* pData;
	}DATASET;
private:
	std::map<unsigned int, std::list<DATASET*>*> m_hashMap;
	int m_nHashSize;
public:
	void InsertData(const TCHAR* pKey,void* pData);
	const void* Find(const TCHAR* pKey);
	void RemoveData(DATASET* pDataSet);
	void Release();
public:
	std::map<unsigned int, std::list<DATASET*>*>* GetHashMap();
private:
	unsigned int Hasing(const TCHAR* pKey);
public:
	std::map<unsigned int, std::list<DATASET*>*> operator [](int nId);
	C_HashTable();
	~C_HashTable();
};

