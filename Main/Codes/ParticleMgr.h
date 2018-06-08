#pragma once
#include "Define.h"
#include "Particle.h"
class C_ParticleMgr
{
	DECLARE_SINGLETONE(C_ParticleMgr);
private:
	std::map<const TCHAR*,C_Particle*> m_MapParticle;
public:
	HRESULT Initiailize();
private:
	C_ParticleMgr();
	C_ParticleMgr(C_ParticleMgr&);
public:
	~C_ParticleMgr();
};

