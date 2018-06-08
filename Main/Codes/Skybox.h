#pragma once
#include "StaticObj.h"
class C_Skybox:public C_StaticObj
{
private:
	const TCHAR* m_pTexKey;
private:
	void PreRender();
	void ResetRender();
public:
	virtual HRESULT Initialize();
	virtual STATEID Progress();
	virtual void Render();
	virtual void Release();
	virtual void SetConstandTable();
public:
	C_Skybox();
	virtual ~C_Skybox();
};

