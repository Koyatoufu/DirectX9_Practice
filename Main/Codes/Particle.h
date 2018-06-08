#pragma once
#include "Define.h"
#include "DirectX.h"
class C_Particle
{
protected:
	std::list<ATTRIBUTE*> m_AttList;
	DWORD m_dwParticleCnt;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	DWORD m_dwVtxSize;
	DWORD m_dwVtxTotalCnt;

	DWORD m_dwVtxFVF;
	DWORD m_dwOffset;
	DWORD m_dwBlockCnt;
public:
	void AddAttribute();
	virtual HRESULT InitParticleBuffer(LPDIRECT3DDEVICE9 pDevice);
	virtual void Progress(void) {}
	virtual void Render(LPDIRECT3DDEVICE9 pDevice){};
	virtual void End_Render(void){};
	void Release(void);
protected:
	virtual void ResetParticle(ATTRIBUTE* pAttribute)PURE;
	virtual void Pre_Render(LPDIRECT3DDEVICE9 pDevice);
	void ResetRender(LPDIRECT3DDEVICE9 pDevice);
public:
	C_Particle();
	virtual ~C_Particle();
};

