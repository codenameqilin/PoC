#pragma once

#include <memory>
#include <string.h>

class mem_t :
	public std::unique_ptr<char>
{
	size_t m_size;
public:
	//implicit
	mem_t(
		__in_bcount(size) char* mem = nullptr,
		__inX size_t size = 0
		) : std::unique_ptr<char>(mem),
			m_size(size)
	{
	}
	mem_t(
		__inX size_t size
		) : std::unique_ptr<char>(new char[size]),
			m_size(size)
	{
		memset(get<char>(), 0, m_size);
	}

	size_t
	size() const
	{
		return m_size;
	}

	template<typename type_t>
	type_t*
	get()
	{
		return reinterpret_cast<type_t*>(std::unique_ptr<char>::get());
	}

	void
	reset(
		__in_bcount(size) char* mem,
		__inX size_t size
		)
	{
		m_size = size;
		std::unique_ptr<char>::reset(mem);
	}
	void
	reset(
		__inX size_t size
		)
	{
		if (m_size == size)
			return;
		m_size = size;
		std::unique_ptr<char>::reset(new char[m_size]);
		memset(get<char>(), 0, m_size);
	}
};
