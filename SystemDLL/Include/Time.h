#pragma once

#define SYSTEM_EXPORT

#include "SystemDef.h"

EXTERN class SYSTEM_DLL C_Time
{
	DECLARE_SINGLETONE_SYSDLL(C_Time);
private:
	LARGE_INTEGER m_FrameTime;
	LARGE_INTEGER m_FixTime;
	LARGE_INTEGER m_LastTime;
	LARGE_INTEGER m_CpuTick;
	float m_fTime;
public:
	void InitTime();
	void UpdateTime();

	float GetTime();
private:
	C_Time();
	C_Time(const C_Time&);
	const C_Time& operator=(const C_Time&);
public:
	~C_Time();
};

