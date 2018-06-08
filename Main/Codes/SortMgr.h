#pragma once
#include "Define.h"
#include "Object.h"
class C_SortMgr
{
	DECLARE_SINGLETONE(C_SortMgr);
private:
	std::list<C_Object*> m_Sortlist[SORTID_END];
public:
	void AddSortObject(C_Object* pObj);
	void RemoveSortObj(C_Object* pObj);
	void RenderSortObj();
	void ReleaseSortObj();
private:
	C_SortMgr();
	C_SortMgr(C_SortMgr&);
public:
	~C_SortMgr();
};

