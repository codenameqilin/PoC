#pragma once

#include <common/usr_common.h>
#include <common/base/Singleton.hpp>

class CDataManager :
	public CSingleton<CDataManager>
{
	char m_sData[0x10000];

	friend class CSingleton<CDataManager>;
	CDataManager()
	{
	}
	static
	void
	Mutator()
	{
		while (true)
		{
			CDataManager::GetInstance().Mutate();
			Sleep(300);
		}
	}
public:
	void
	Start()
	{
		std::thread mutator(Mutator);
		mutator.detach();		
	}
	template<typename type_t>
	__checkReturn
	type_t*
	Buffer(
		__inX size_t size
		)
	{
		assert(size <= sizeof(m_sData));
		if (size > sizeof(m_sData))
			return nullptr;

		size_t offset = 0;
		if (size != sizeof(m_sData))
			offset = std::rand() % (sizeof(m_sData) - size);

		return (type_t*)(m_sData + offset);
	}
	__checkReturn
	bool
	Randomize(
		__inout_bcount(size) void* buf,
		__inX size_t size
		)
	{
		auto data = Buffer<char>(size);
		if (!data)
			return false;
		memcpy(buf, data, size);
		return true;
	}
protected:
	void
	Mutate()
	{
		for (size_t i = 0; i < _countof(m_sData); i++)
			m_sData[i] = static_cast<char>(std::rand() % 0xFF);
	}
};
