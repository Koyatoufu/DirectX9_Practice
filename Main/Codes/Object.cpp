#include "StdAfx.h"
#include "Object.h"


C_Object::C_Object(void) :m_Info(), m_StateID(STATE_NONE),m_pBufferKey(NULL), m_pMeshKey(NULL), m_pTexKey(NULL), m_sortID(SORTID_END), m_bAlive(true), m_bColl(false)
{
}

C_Object::C_Object(const C_Object&) : m_Info(), m_StateID(STATE_NONE), m_pBufferKey(NULL), m_pMeshKey(NULL), m_pTexKey(NULL), m_sortID(SORTID_END), m_bAlive(true)
{
	
}


C_Object::~C_Object(void)
{
}

OBJINFO* C_Object::GetInfo()
{
	return &m_Info;
}

SORTID C_Object::GetSortID()
{
	return m_sortID;
}

bool C_Object::GetAllive()
{
	return m_bAlive;
}
