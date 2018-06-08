#pragma once
#include "Stage.h"
class C_TestStage:public C_Stage
{
protected:
	virtual HRESULT LoadResource();
	virtual void AddObject();
	virtual void SoundPlay();
public:
	virtual HRESULT Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();
public:
	C_TestStage();
	virtual ~C_TestStage();
};

