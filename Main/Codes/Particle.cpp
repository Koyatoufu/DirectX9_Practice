#include "StdAfx.h"
#include "Particle.h"


C_Particle::C_Particle() :m_dwParticleCnt(0),
m_pVB(NULL), m_dwVtxSize(0), m_dwVtxTotalCnt(0),
m_dwVtxFVF(0), m_dwOffset(0), m_dwBlockCnt(0)
{
}


C_Particle::~C_Particle()
{
}

void C_Particle::AddAttribute()
{
	ATTRIBUTE* pAttribute = new ATTRIBUTE();

	ResetParticle(pAttribute);

	m_AttList.push_back(pAttribute);
}

HRESULT C_Particle::InitParticleBuffer(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(pDevice->CreateVertexBuffer(m_dwVtxSize * m_dwVtxTotalCnt
		, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS
		, m_dwVtxFVF, D3DPOOL_DEFAULT, &m_pVB, NULL)))
		return E_FAIL;
	return S_OK;
}

void C_Particle::Pre_Render(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	float fSize = 1.f;

	pDevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&fSize));
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);

	float fSizeA = 0.f;
	float fSizeB = 0.f;
	float fSizeC = 1.f;

	pDevice->SetRenderState(D3DRS_POINTSCALE_A, *((DWORD*)&fSizeA));
	pDevice->SetRenderState(D3DRS_POINTSCALE_B, *((DWORD*)&fSizeB));
	pDevice->SetRenderState(D3DRS_POINTSCALE_C, *((DWORD*)&fSizeC));

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

void C_Particle::ResetRender(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


void C_Particle::Release(void)
{
	for (std::list<ATTRIBUTE*>::iterator iter = m_AttList.begin();iter != m_AttList.end(); iter++)
	{
		delete (*iter);
		(*iter) = NULL;

	}
	m_AttList.clear();

	if (m_pVB)
	{
		m_pVB->Release();
		m_pVB = NULL;
	}
		
}

