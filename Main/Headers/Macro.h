#pragma once

#define MSGBOX_OK(str) MessageBox(NULL,str,L"Message",MB_OK)

#define KeyDown(DIK) C_Input::GetInst()->IsKeyDown(DIK)

#define DECLARE_SINGLETONE(CLASSNAME)\
public:\
	static CLASSNAME* CLASSNAME::m_pInst;\
public:\
	static void InitInst();\
	static CLASSNAME* GetInst();\
	static void ReleaseInst();
#define IMPLEMENT_SINGLETONE(CLASSNAME)\
	CLASSNAME* CLASSNAME::m_pInst=NULL;\
	void CLASSNAME::InitInst()\
				{\
		if(m_pInst)\
			return;\
		m_pInst=new CLASSNAME();\
				}\
	CLASSNAME* CLASSNAME::GetInst()\
				{\
		if(!m_pInst)\
						{\
			return NULL;\
						}\
		return m_pInst;\
				}\
	void CLASSNAME::ReleaseInst()\
				{\
		if(m_pInst)\
						{\
			delete m_pInst;\
			m_pInst=NULL;\
						}\
				}