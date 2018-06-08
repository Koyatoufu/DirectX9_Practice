#include "../include/StdAfx.h"
#include "Factory.h"


template<typename T, typename T1>
C_Factory<typename T, typename T1>::C_Factory()
{
}

template<typename T, typename T1>
C_Factory<typename T, typename T1>::~C_Factory()
{
}

template<typename T, typename T1>
T* C_Factory<T, T1>::CreateFactoryOjbect()
{
	T* pTmp = new T1();
	pTmp->Initialize();
	return pTmp;
}
