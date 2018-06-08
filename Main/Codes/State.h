#pragma once
#include "Define.h"

#include "DirectX.h"
#include "Time.h"

#include "TextureMgr.h"
#include "BufferMgr.h"
#include "MeshMgr.h"
#include "BoundaryMgr.h"
#include "SoundLoader.h"

#include "ObjMgr.h"
#include "ShaderMgr.h"
#include "SortMgr.h"
#include "Factory.h"
#include "CamMgr.h"
class C_State
{
protected:
	virtual HRESULT LoadResource(){ return S_OK; }
	virtual void AddObject(){}
	virtual void SoundPlay(){}
public:
	virtual HRESULT Initialize()=0;
	virtual void Progress() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
public:
	C_State();
	virtual ~C_State();
};

