#pragma once

#define RESOURCE_EXPORT
#include "ResourceDef.h"


EXTERN class RESOURCE_DLL C_AnimationCtrl
{
private:
LPD3DXANIMATIONCONTROLLER			m_pAniCtrl;


DWORD							m_dwCurrentTrack;
DWORD							m_dwNewTrack;
DWORD							m_dwCurrentAniSet;

int								m_numAnimationSets;	
float							m_fCurrentTime;

const float m_fKMoveTransitionTime;

public:
	void SetAnimationSet(int nIdx);
	
	void FrameMove(const TCHAR* pMeshKey, float fTime);


	LPD3DXANIMATIONCONTROLLER* GetAniCtrl(void);

	C_AnimationCtrl* Clone(void);


	void Release(void);

public:
	C_AnimationCtrl(void);
	C_AnimationCtrl(const C_AnimationCtrl& Ani);
	~C_AnimationCtrl(void);
};

