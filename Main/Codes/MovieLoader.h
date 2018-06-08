#pragma once

#include <Vfw.h>
#include "Define.h"

class C_MovieLoader
{
	DECLARE_SINGLETONE(C_MovieLoader);
private:
	PAVIFILE m_pavfile;
	TCHAR m_szFileName[128];
public:
	HRESULT LoadMovie(const TCHAR* pFileName);
	void PlayMovie();
	void Release();
public:
	C_MovieLoader();
	~C_MovieLoader();
};