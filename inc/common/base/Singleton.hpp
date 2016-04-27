#pragma once

/*
# CSingleton usage : 

class CClass :
	public CSingleton<CClass>
{
	friend class CSingleton<CClass>;
	CClass(...)
	{
	}
public:
}

CClass CClass::m_instance;
*/

template<typename type_t>
class CSingleton
{
	CSingleton(const CSingleton&) = delete;
	void operator=(CSingleton const&) = delete;
protected:
	static type_t m_instance;
	CSingleton()
	{
	}
public:
	static
	type_t& GetInstance()
	{
		return m_instance;
	}
};

template<typename type_t>
type_t CSingleton<type_t>::m_instance;
