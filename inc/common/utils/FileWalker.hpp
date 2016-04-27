#pragma once

//#include <boost/noncopyable.hpp>
#include <windows.h>
#include <tchar.h>
#include <memory>
#include "../usr_common.h"

class CFileWalker// : public boost::noncopyable
{
	std::unique_ptr<void, decltype(&FindClose)> m_snap;
	WIN32_FIND_DATA m_file32;
public:
	CFileWalker(
		__inX const std::string& path
		) : m_snap(FindFirstFile(path.c_str(), &m_file32), FindClose)
	{
	}

	const
	WIN32_FIND_DATA&
	File() const
	{
		return m_file32;
	}

	const WIN32_FIND_DATA*
	operator++()
	{
		if (!FindNextFile(m_snap.get(), &m_file32))
			return nullptr;

		return &m_file32;
	}
};
