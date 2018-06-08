#include "StdAfx.h"
#include "Menu.h"

#include "StateMgr.h"

#include "StartText.h"
#include "OptionText.h"
#include "ExitText.h"

C_Menu::C_Menu()
{
}


C_Menu::~C_Menu()
{
	Release();
}

HRESULT C_Menu::Initialize()
{
	C_ObjMgr::InitInst();
	C_SortMgr::InitInst();

	LoadResource();

	AddObject();

	SoundPlay();

	return S_OK;
}

void C_Menu::Progress()
{
	STATEID stateID=C_ObjMgr::GetInst()->Progress();
	if (stateID!=STATE_NONE)
	{
		C_StateMgr::GetInst()->SetState(stateID);
	}
}

void C_Menu::Render()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	C_DirectX::GetInst()->GetSprite()->SetTransform(&matWorld);
	C_DirectX::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	LPDIRECT3DTEXTURE9 pTexture = C_TextureMgr::GetInst()->GetTexInfo(L"MainBack")->pTexture;

	RECT rect = { 0, 0, 1024, 768 };

	C_DirectX::GetInst()->GetSprite()->Draw(pTexture, &rect, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	C_ObjMgr::GetInst()->Render();

	C_DirectX::GetInst()->GetSprite()->End();
}

void C_Menu::Release()
{
	C_ObjMgr::GetInst()->Release();
	C_SoundLoader::GetInst()->Release();
	C_TextureMgr::GetInst()->Release();
}

HRESULT C_Menu::LoadResource()
{
	if (FAILED(C_TextureMgr::GetInst()->InsertTexture(C_DirectX::GetInst()->GetDevice(), TEX_GENERAL, L"../../Resource/Texture/Main/MainBack.jpg", L"MainBack")))
	{
		return E_FAIL;
	}
	if (FAILED(C_TextureMgr::GetInst()->InsertTexture(C_DirectX::GetInst()->GetDevice(), TEX_GENERAL, L"../../Resource/Texture/Main/MenuText.png", L"MenuText")))
	{
		return E_FAIL;
	}

	return S_OK;
}

void C_Menu::AddObject()
{
	C_ObjMgr::GetInst()->InsertObject(L"StartText", C_Factory<C_Object, C_StartText>::CreateFactoryOjbect());
	C_ObjMgr::GetInst()->InsertObject(L"OptionText", C_Factory<C_Object, C_OptionText>::CreateFactoryOjbect());
	C_ObjMgr::GetInst()->InsertObject(L"ExitText", C_Factory<C_Object, C_ExitText>::CreateFactoryOjbect());
}

void C_Menu::SoundPlay()
{

}
