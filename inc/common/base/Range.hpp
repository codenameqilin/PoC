#pragma once

#include "../usr_common.h"

using namespace std;

struct CRange
{
	//implicit
	template<typename type_t>
	CRange(
		__inX type_t* begin, 
		__inX type_t* end = nullptr
		) : m_begin(reinterpret_cast<size_t>(begin)), 
			m_end(reinterpret_cast<size_t>(end ? end : begin)) 
	{
		assert(SBegin() <= SEnd());
	};

	CRange(
		__inX size_t begin = 0, 
		__inX size_t end = 0
		) : m_begin(begin), 
			m_end(end ? end : begin)
	{
		assert(SBegin() <= SEnd());
	};

public:
	void 
	Reset(
		__inX void* begin
		)
	{
		Set(begin, begin);
	};
	void 
	Set(
		__inX void* begin,
		__inX void* end
		)
	{
		Begin<void>() = begin;
		End<void>() = end;

		assert(SBegin() <= SEnd());
	};

	bool 
	IsInRange(
		__inX const void* address
		) const
	{
		return IsInRange(reinterpret_cast<size_t>(address));
	};

	template<typename type_t>
	bool 
	IsInTypeRange(
		__inX type_t address
		) const
	{
		return ((type_t)m_end >= address && address >= (type_t)m_begin);
	};

	bool 
	IsInRange(
		__inX size_t address
		) const
	{
		return (m_end >= address && address >= m_begin);
	};

	void 
	SetSize(
		__inX size_t size
		)
	{ 
		m_end = max(m_begin + size - 1, m_end);
		assert(SBegin() <= SEnd());
	};

	size_t 
	GetSize()
	{ 
		return (m_end - m_begin + 1); 
	};

	template<typename type_t>
	type_t*&
	Begin() const
	{
		return (type_t*&)(m_begin);
	};

	template<typename type_t>
	type_t*& 
	End() const
	{
		return (type_t*&)(m_end);
	};
	
	size_t const&
	SBegin() const
	{
		return m_begin;
	};

	size_t const&
	SEnd() const
	{
		return m_end;
	};
	
	static 
	inline 
	bool 
	IsOverlaping(
		__inX const CRange &left, 
		__inX const CRange &right
		)
	{
		return !(left.m_begin > right.m_end || right.m_begin > left.m_end);
	}

protected:
	friend
	bool 
	operator>(
		__inX const CRange &left,
		__inX const CRange &right
		)
	{
		if (IsOverlaping(left, right))
			return false;

		return (left.m_begin > right.m_begin);
	}

	friend
	bool 
	operator<(
		__inX const CRange &left, 
		__inX const CRange &right
		)
	{
		return (right > left);
	}

	friend
	bool 
	operator==(
		__inX const CRange &left, 
		__inX const CRange &right
		)
	{
		return IsOverlaping(left, right);
	}

private:
	size_t m_begin;
	size_t m_end;
};

template<typename type_t>
class CTypedRange :
	public CRange
{
	type_t m_dummy = 0;
public:
	CTypedRange(
		__inX const type_t* begin,
		__inX const type_t* end = nullptr
		) : CRange(begin, end)
	{
	};

	CTypedRange(
		__inX size_t begin = 0,
		__inX size_t end = 0
		) : CRange(begin, end)
	{
	};

	type_t&
	operator[](
		__inX size_t index
		)
	{
		if (!IsInRange(SBegin() + index))
			return m_dummy;

		return Begin<type_t>()[index];
	}
};
