#include "AnimationCtrl.h"
#include "MeshMgr.h"

C_AnimationCtrl::C_AnimationCtrl(void)
	:m_pAniCtrl(NULL), m_dwCurrentAniSet(0), m_dwNewTrack(0),m_dwCurrentTrack(0),
	m_numAnimationSets(0),m_fCurrentTime(0.0f),
	m_fKMoveTransitionTime(0.25f)
{

}

C_AnimationCtrl::C_AnimationCtrl(const C_AnimationCtrl& Ani)
	:m_pAniCtrl(NULL), m_dwCurrentAniSet(0), m_dwNewTrack(0),
	m_numAnimationSets(0),m_fCurrentTime(0.0f)
	,m_fKMoveTransitionTime(0.25f)//m_dwCurrentTrack(0) is Error
{
	Ani.m_pAniCtrl->CloneAnimationController(Ani.m_pAniCtrl->GetMaxNumAnimationOutputs()
		, Ani.m_pAniCtrl->GetMaxNumAnimationSets()
		, Ani.m_pAniCtrl->GetMaxNumTracks()
		, Ani.m_pAniCtrl->GetMaxNumEvents()
		, &m_pAniCtrl);
}

C_AnimationCtrl::~C_AnimationCtrl(void)
{
	Release();
}

// 본에 무기붙이는 작업
// const float kMoveTransitionTime=0.25f;

void C_AnimationCtrl::SetAnimationSet( int nIdx)
{
	m_dwNewTrack = (m_dwCurrentTrack == 0 ? 1 : 0);

	LPD3DXANIMATIONSET			pAS = NULL;

	m_pAniCtrl->GetAnimationSet(nIdx, &pAS);

	m_pAniCtrl->SetTrackAnimationSet(m_dwNewTrack, pAS);

	pAS->Release();

	if (m_dwCurrentAniSet == nIdx)
		return;

	m_dwCurrentAniSet = nIdx;

	m_pAniCtrl->UnkeyAllTrackEvents(m_dwNewTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_dwCurrentTrack);

	m_pAniCtrl->SetTrackPosition(m_dwNewTrack, 0.f);
	m_pAniCtrl->SetTrackPosition(m_dwCurrentTrack, 0.f);


	m_pAniCtrl->SetTrackEnable(m_dwNewTrack, TRUE);

	m_pAniCtrl->KeyTrackSpeed(m_dwNewTrack, 1.f, m_fCurrentTime, m_fKMoveTransitionTime, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->KeyTrackWeight(m_dwNewTrack, 1.f, m_fCurrentTime, m_fKMoveTransitionTime, D3DXTRANSITION_LINEAR);

}

void C_AnimationCtrl::FrameMove( const TCHAR* pMeshKey, float fTime )
{
	if (m_pAniCtrl != NULL)
		m_pAniCtrl->AdvanceTime(fTime, NULL);
	m_fCurrentTime += fTime;

	D3DXMATRIX		matWorld;
	D3DXMatrixIdentity(&matWorld);
	C_MeshMgr::GetInst()->InvalidateMesh(pMeshKey, &matWorld);
}

LPD3DXANIMATIONCONTROLLER* C_AnimationCtrl::GetAniCtrl( void )
{
	return &m_pAniCtrl;
}

C_AnimationCtrl* C_AnimationCtrl::Clone( void )
{
	return new C_AnimationCtrl(*this);
}

void C_AnimationCtrl::Release( void )
{
	if (m_pAniCtrl)
	{
		m_pAniCtrl->Release();
		m_pAniCtrl=NULL;
	}
}
