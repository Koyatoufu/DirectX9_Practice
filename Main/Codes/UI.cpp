#include "StdAfx.h"
#include "UI.h"


C_UI::C_UI() :C_Object(),m_pTexKey(NULL), m_pTexInfo(NULL), m_vCenter(0.0f, 0.0f, 0.0f), m_fSizeX(0.0f), m_fSizeY(0.0f), m_rect()
{
	m_sortID = SORTID_UI;
}


C_UI::~C_UI()
{
}
