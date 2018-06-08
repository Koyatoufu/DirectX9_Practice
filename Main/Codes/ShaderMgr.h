#pragma once
#include "Define.h"
#include "Effect.h"
class C_ShaderMgr
{
	DECLARE_SINGLETONE(C_ShaderMgr);
private:
	std::map<EFFECTTYPE, C_Effect*> m_mapEffect;
public:
	HRESULT AddEffect(LPDIRECT3DDEVICE9 pDevice,EFFECTTYPE Type,const TCHAR* pFileName);
	void Release();
public:
	LPD3DXEFFECT GetEffect(EFFECTTYPE Type);

	void Begin_Render(EFFECTTYPE Type,UINT nPassCnt=0);
	void End_Render(LPDIRECT3DDEVICE9 pDevice, EFFECTTYPE Type);
private:
	C_ShaderMgr();
	C_ShaderMgr(const C_ShaderMgr&);
public:
	~C_ShaderMgr();
};

