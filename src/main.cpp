#include <internals/nt.h>
#include <pcommon/common.hpp>

int main()
{
	poc::Init();

	poc::DoPoC();//so link main.cpp with appropriate poc.cpp

	return 0;
}

namespace poc
{
	void
	Init()
	{
		CDataManager::GetInstance().Start();
	}
};

decltype(&ZwCreateFile_fn) ZwCreateFile = (decltype(&ZwCreateFile_fn))GetProcAddress(GetModuleHandle("ntdll.dll"), "ZwCreateFile");
decltype(&ZwDeviceIoControlFile_fn) ZwDeviceIoControlFile = (decltype(&ZwDeviceIoControlFile_fn))GetProcAddress(GetModuleHandle("ntdll.dll"), "ZwDeviceIoControlFile");
