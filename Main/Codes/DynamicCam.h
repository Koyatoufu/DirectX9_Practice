#pragma once
#include "Camera.h"
class C_DynamicCam:public C_Camera
{
private:
	float m_fCamSpeed;
private:
	void MoveCamForwardBack(float fForce);
	void MoveCamWide(float fForce);
protected:
	virtual void KeyCheck();
	virtual void MouseCheck();
public:
	virtual void Initialize();
	virtual void Progress();
private:
	C_DynamicCam(const C_DynamicCam&);
public:
	C_DynamicCam();
	virtual ~C_DynamicCam();
};

