#pragma once

#include "../usr_common.h"
#include "mem_t.hpp"

class CMemFromFileResource
{
protected:
	mem_t m_rsrc;
public:
	mem_t* operator->() { return &m_rsrc; }

	CMemFromFileResource(
		__inX const std::string& fname
		)
	{
		std::unique_ptr<char> cfname(new char[fname.size() + 1]);
		if (!cfname)
			return;
		memset(cfname.get(), 0, fname.size() + 1);
		//wcsncpy
		strncpy(cfname.get(), fname.c_str(), fname.size());
		std::unique_ptr<FILE, decltype(&fclose)> file(fopen(cfname.get(), "rb"), fclose);
		if (!file)
			return;
		
		fseek(file.get(), 0, SEEK_END);
		size_t size = static_cast<size_t>(ftell(file.get()));

		if (UNDEF == size)
			return;

		m_rsrc.reset(size);
		if (m_rsrc.size() != size)
			return;
		
		rewind(file.get());
		fread(m_rsrc.get<char>(), 1, size, file.get());
	}
};
