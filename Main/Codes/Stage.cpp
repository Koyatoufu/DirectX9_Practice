#include "StdAfx.h"
#include "Stage.h"



C_Stage::C_Stage()
{
}


C_Stage::~C_Stage()
{
}

HRESULT C_Stage::Initialize()
{
	C_BufferMgr::InitInst();
	C_MeshMgr::InitInst();

	C_BoundaryMgr::InitInst();

	C_ObjMgr::InitInst();
	C_SortMgr::InitInst();
	C_ShaderMgr::InitInst();

	return S_OK;
}

void C_Stage::Progress()
{

}

void C_Stage::Render()
{

}

void C_Stage::Release()
{

}

HRESULT C_Stage::LoadResource()
{
	return S_OK;
}
