#include "StdAfx.h"
#include "ObjMgr.h"
#include "SortMgr.h"

IMPLEMENT_SINGLETONE(C_ObjMgr);

C_ObjMgr::C_ObjMgr() :m_hashTable()
{
}


C_ObjMgr::~C_ObjMgr()
{
	Release();
}

void C_ObjMgr::InsertObject(const TCHAR* pObjectKey, C_Object* pObject)
{
	if (!pObject)
	{
		TCHAR szTmp[128] = L"This Object Is NULL::";
		lstrcat(szTmp, pObjectKey);
		MSGBOX_OK(szTmp);
		return;
	}

	m_hashTable.InsertData(pObjectKey, (void*)pObject);

	C_SortMgr::GetInst()->AddSortObject(pObject);
}

STATEID C_ObjMgr::Progress()
{
	std::map<UINT, std::list<C_HashTable::DATASET*>*>::iterator iter;
	
	for (iter = m_hashTable.GetHashMap()->begin(); iter != m_hashTable.GetHashMap()->end();iter++)
	{
		for (std::list<C_HashTable::DATASET*>::iterator iter1 = iter->second->begin();iter1!=iter->second->end();iter1++)
		{
			C_Object* pObject = (C_Object*)((*iter1)->pData);
			if (!pObject->GetAllive())
			{
				C_SortMgr::GetInst()->RemoveSortObj(pObject);
				m_hashTable.RemoveData(*iter1);
				return STATE_NONE;
			}
			else
			{
				STATEID stateID=pObject->Progress();
				if (stateID != STATE_NONE)
					return stateID;
			}
		}
	}

	return STATE_NONE;
}

void C_ObjMgr::Render()
{
// 	std::map<UINT, std::list<C_HashTable::DATASET*>*>::iterator iter;
// 
// 	for (iter = m_hashTable.GetHashMap()->begin(); iter != m_hashTable.GetHashMap()->end(); iter++)
// 	{
// 		for (std::list<C_HashTable::DATASET*>::iterator iter1 = iter->second->begin(); iter1 != iter->second->end(); iter1++)
// 		{
// 			C_HashTable::DATASET* pDataSet = *iter1;
// 			C_Object* pObject = (C_Object*)(pDataSet->pData);
// 			pObject->Render();
// 		}
// 	}

	C_SortMgr::GetInst()->RenderSortObj();
}

void C_ObjMgr::Release()
{
	C_SortMgr::GetInst()->ReleaseSortObj();

	m_hashTable.Release();
}

C_Object* C_ObjMgr::GetObj(const TCHAR* pObjectKey)
{
	C_Object* pObject=(C_Object*)(m_hashTable.Find(pObjectKey));

	return pObject;
}
