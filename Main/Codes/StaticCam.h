#pragma once
#include "Camera.h"
#include "ObjMgr.h"
class C_StaticCam:public C_Camera
{
private:
	float m_fDistance;
	OBJINFO* m_pInfo;
	float m_fRotX;
	float m_fRotY;
	float m_fPosX;
private:
	void UpdateStaticCamState();
protected:
	virtual void KeyCheck();
	virtual void MouseCheck();
public:
	virtual void Initialize();
	virtual void Progress();
private:
	C_StaticCam(const C_StaticCam&);
public:
	C_StaticCam();
	~C_StaticCam();
};

