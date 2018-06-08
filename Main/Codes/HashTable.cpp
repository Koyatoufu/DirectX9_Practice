#include "StdAfx.h"
#include "HashTable.h"


C_HashTable::C_HashTable()
{
}


C_HashTable::~C_HashTable()
{
}

void C_HashTable::InsertData(const TCHAR* pKey, void* pData)
{
	DATASET* pDataSet = NULL;
	std::list<DATASET*>* pList = NULL;
	UINT nHash = Hasing(pKey);
	if (!m_hashMap.empty())
	{
		std::map<unsigned int, std::list<DATASET*>*>::iterator iter = m_hashMap.find(nHash);
		if (iter != m_hashMap.end())
		{
			pDataSet = new DATASET();
			pDataSet->pData = pData;
			pDataSet->pKey = pKey;
			iter->second->push_back(pDataSet);
			return;
		}
	}
	
	pList = new std::list<DATASET*>();

	pDataSet = new DATASET();
	pDataSet->pData = pData;
	pDataSet->pKey = pKey;

	pList->push_back(pDataSet);

	m_hashMap.insert(std::make_pair(nHash, pList));

}

const void* C_HashTable::Find(const TCHAR* pKey)
{
	int nIndex=Hasing(pKey);

	std::map<unsigned int, std::list<DATASET*>*>::iterator iter = m_hashMap.find(nIndex);

	if (iter==m_hashMap.end())
	{
		return NULL;
	}

	for (std::list<DATASET*>::iterator iter1 = iter->second->begin();iter1!=iter->second->end();iter1++)
	{
		if (!lstrcmp(pKey, (*iter1)->pKey))
		{
			return (*iter1)->pData;
		}
	}

	return NULL;
}

void C_HashTable::Release()
{
	for (std::map<unsigned int, std::list<DATASET*>*>::iterator iter = m_hashMap.begin(); iter != m_hashMap.end();iter++)
	{
		for (std::list<DATASET*>::iterator iter1 = iter->second->begin();iter1!=iter->second->end(); iter1++)
		{
			delete (*iter1)->pData;
			(*iter1)->pData = NULL;
		}
		iter->second->clear();
	}
	m_hashMap.clear();
}

unsigned int C_HashTable::Hasing(const TCHAR* pKey)
{
	UINT nHashVal = 0;

	for (; *pKey != NULL; pKey++)
	{
		nHashVal = *pKey + (nHashVal << 5) - nHashVal;
	}

	return nHashVal;
}

std::map<unsigned int, std::list<C_HashTable::DATASET*>*>* C_HashTable::GetHashMap()
{
	return &m_hashMap;
}

void C_HashTable::RemoveData(DATASET* pDataSet)
{
	for (std::map<unsigned int, std::list<DATASET*>*>::iterator iter = m_hashMap.begin(); iter != m_hashMap.end(); iter++)
	{
		for (std::list<DATASET*>::iterator iter1 = iter->second->begin(); iter1 != iter->second->end(); iter1++)
		{
			if ((*iter1)==pDataSet)
			{
				delete (*iter1)->pData;
				(*iter1)->pData = NULL;
				iter->second->erase(iter1);
				return;
			}
		}
	}
}




