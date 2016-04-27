#pragma once

//should be done in generic way for linux & osx as well .. TODO ..

#include "../common.hpp"
#include <internals/nt.h>

class CClose :
	public std::unique_ptr<void, decltype(&CloseHandle)>
{
public:
	CClose(
		__inX DEVICE dev
		) : std::unique_ptr<void, decltype(&CloseHandle)>(dev, CloseHandle)
	{			
	}
};
