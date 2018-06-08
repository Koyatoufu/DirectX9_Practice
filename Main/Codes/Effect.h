#pragma once
#include "Define.h"
class C_Effect
{
private:
	LPD3DXEFFECT m_pEffect;
	LPD3DXBUFFER m_pError;
public:
	HRESULT InitShader(LPDIRECT3DDEVICE9 pDevice,const TCHAR* pFileName);
	void Realese();

	void Begin_Render(UINT nPassCnt);
	void End_Render(LPDIRECT3DDEVICE9 pDevice);
public:
	LPD3DXEFFECT GetEffect();
public:
	C_Effect();
	~C_Effect();
};

