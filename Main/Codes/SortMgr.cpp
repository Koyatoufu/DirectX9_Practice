#include "StdAfx.h"
#include "SortMgr.h"

IMPLEMENT_SINGLETONE(C_SortMgr);

C_SortMgr::C_SortMgr()
{
}


C_SortMgr::~C_SortMgr()
{
}

void C_SortMgr::AddSortObject(C_Object* pObj)
{
	m_Sortlist[pObj->GetSortID()].push_back(pObj);
}

void C_SortMgr::RenderSortObj()
{
	for (int i = 0; i < SORTID_END; i++)
	{
		for (std::list<C_Object*>::iterator iter = m_Sortlist[i].begin(); iter != m_Sortlist[i].end(); iter++)
		{
			(*iter)->Render();
		}
	}
}

void C_SortMgr::ReleaseSortObj()
{
	for (int i = 0; i < SORTID_END;i++)
	{
		m_Sortlist[i].clear();
	}
}

void C_SortMgr::RemoveSortObj(C_Object* pObj)
{
	for (std::list<C_Object*>::iterator iter = m_Sortlist[pObj->GetSortID()].begin(); iter != m_Sortlist[pObj->GetSortID()].end();iter++)
	{
		if (*iter==pObj)
		{
			m_Sortlist[pObj->GetSortID()].erase(iter);
			return;
		}
	}
}

