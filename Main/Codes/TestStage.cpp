#include "StdAfx.h"
#include "TestStage.h"

#include "Grid.h"
#include "Road.h"
#include "Skybox.h"

#include "PlayerX.h"
#include "PlayerZero.h"

#include "MBossBee.h"
#include "WheelZako.h"

#include "BillBoard.h"
#include "Dash.h"

#include "MenuBar.h"
#include "PStatusBar.h"
#include "MiniMap.h"
#include "SkillBar.h"

#include "LifeBar.h"
#include "EnBar.h"

C_TestStage::C_TestStage() :C_Stage()
{
}


C_TestStage::~C_TestStage()
{
}

HRESULT C_TestStage::Initialize()
{
	C_Stage::Initialize();

	C_CamMgr::InitInst();
	
	LPDIRECT3DDEVICE9 pDevice = C_DirectX::GetInst()->GetDevice();

	if (FAILED(LoadResource()))
	{
		return E_FAIL;
	}

	AddObject();

	if (FAILED(C_ShaderMgr::GetInst()->AddEffect(pDevice, EFFECT_DEFAULT, L"Default.fx")))
	{
		return E_FAIL;
	}
	if (FAILED(C_ShaderMgr::GetInst()->AddEffect(pDevice, EFFECT_TEST, L"TestEffect.fx")))
	{
		return E_FAIL;
	}
	
	C_CamMgr::GetInst()->Initilize(CAMMODE_STATIC);

	SoundPlay();

	return S_OK;
}

void C_TestStage::Progress()
{
	C_ObjMgr::GetInst()->Progress();
	C_CamMgr::GetInst()->Progress();
}

void C_TestStage::Render()
{
	C_ObjMgr::GetInst()->Render();
}

void C_TestStage::Release()
{
	C_SoundLoader::GetInst()->SoundStop(0);
	C_SoundLoader::GetInst()->Release();

	C_CamMgr::GetInst()->Release();
	C_CamMgr::ReleaseInst();

	C_SortMgr::GetInst()->ReleaseSortObj();
	C_ObjMgr::GetInst()->Release();
}

HRESULT C_TestStage::LoadResource()
{
	LPDIRECT3DDEVICE9 pDevice = C_DirectX::GetInst()->GetDevice();

	if (FAILED(C_BufferMgr::GetInst()->AddBuffer(pDevice, L"Cube", BUFF_CUBE)))
	{
		return E_FAIL;
	}

	if (FAILED(C_BufferMgr::GetInst()->AddBuffer(pDevice, L"Rect", BUFF_RECT)))
	{
		return E_FAIL;
	}

	if (FAILED(C_MeshMgr::GetInst()->AddMesh(pDevice, L"../../Resource/Mesh/Dynamic/Enemy/MBoss/MBossBee/", L"MBossBee.x", L"MBossBee", MESH_DYNAMIC)))
	{
		return E_FAIL;
	}
	if (FAILED(C_MeshMgr::GetInst()->AddMesh(pDevice, L"../../Resource/Mesh/Dynamic/Enemy/Zako/WheelZako/", L"WheelZako.x", L"WheelZako", MESH_DYNAMIC)))
	{
		return E_FAIL;
	}
	if (FAILED(C_MeshMgr::GetInst()->AddMesh(pDevice, L"../../Resource/Mesh/Static/Effect/Dash/", L"Dash.x", L"Dash", MESH_STATIC)))
	{
		return E_FAIL;
	}
	if (FAILED(C_MeshMgr::GetInst()->AddMesh(pDevice, L"../../Resource/Mesh/Static/Bullet/", L"Bullet.x", L"Bullet", MESH_STATIC)))
	{
		return E_FAIL;
	}
	if (FAILED(C_MeshMgr::GetInst()->AddMesh(pDevice, L"../../Resource/Mesh/Static/Road/", L"Road.x", L"Road", MESH_STATIC)))
	{
		return E_FAIL;
	}
	if (FAILED(C_TextureMgr::GetInst()->InsertTexture(pDevice,TEX_GENERAL,L"../../Resource/Texture/Effect/Aura.tga",L"Bill")))
	{
		return E_FAIL;
	}
	if (FAILED(C_TextureMgr::GetInst()->InsertTexture(pDevice, TEX_GENERAL, L"../../Resource/Texture/Effect/Dash.png", L"Dash")))
	{
		return E_FAIL;
	}

	if (FAILED(C_SoundLoader::GetInst()->LoadSound(L"../../Resource/Sound/StageBgm/OpeningStage.wav")))
	{
		return E_FAIL;
	}

	return S_OK;
}

void C_TestStage::AddObject()
{
	C_ObjMgr::GetInst()->InsertObject(L"Sky", C_Factory<C_Object, C_Skybox>::CreateFactoryOjbect());
	C_ObjMgr::GetInst()->InsertObject(L"Grid", C_Factory<C_Object, C_Grid>::CreateFactoryOjbect());
	C_ObjMgr::GetInst()->InsertObject(L"Road1", C_Factory<C_Object, C_Road>::CreateFactoryOjbect());
	C_ObjMgr::GetInst()->InsertObject(L"Player", C_Factory<C_Object, C_PlayerX>::CreateFactoryOjbect());

	C_ObjMgr::GetInst()->InsertObject(L"MBossBee", C_Factory<C_Object, C_MBossBee>::CreateFactoryOjbect());
	C_ObjMgr::GetInst()->InsertObject(L"WheelZako", C_Factory<C_Object, C_WheelZako>::CreateFactoryOjbect());
	
	C_ObjMgr::GetInst()->InsertObject(L"BillBoard", C_Factory<C_Object, C_BillBoard>::CreateFactoryOjbect());

	C_ObjMgr::GetInst()->InsertObject(L"MenuBarUI", C_Factory<C_Object, C_MenuBar>::CreateFactoryOjbect());
	C_ObjMgr::GetInst()->InsertObject(L"PStatusUI", C_Factory<C_Object, C_PStatusBar>::CreateFactoryOjbect());
	C_ObjMgr::GetInst()->InsertObject(L"SkillSlotUI", C_Factory<C_Object, C_SkillBar>::CreateFactoryOjbect());

	C_ObjMgr::GetInst()->InsertObject(L"LIfeBar", C_Factory<C_Object, C_LifeBar>::CreateFactoryOjbect());
	C_ObjMgr::GetInst()->InsertObject(L"EnBar", C_Factory<C_Object, C_EnBar>::CreateFactoryOjbect());
}

void C_TestStage::SoundPlay()
{
	C_SoundLoader::GetInst()->SoundPlay(0,1);
}
