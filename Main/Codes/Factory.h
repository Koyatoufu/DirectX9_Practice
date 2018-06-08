#pragma once
template<typename T,typename T1>
class C_Factory
{
public:
	static T* CreateFactoryOjbect()
	{
		T* pTmp = new T1();
		if (FAILED(pTmp->Initialize()))
		{
			return NULL;
		}
		return pTmp;
	}
public:
	C_Factory();
	~C_Factory();
private:
	C_Factory(const C_Factory&);
};