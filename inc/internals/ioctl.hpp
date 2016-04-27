#pragma once

#include "nt.h"
#include <pcommon/common.hpp>

typedef HANDLE DEVICE;
typedef NTSTATUS STATUS;

namespace ioctl
{
	__checkReturn
	DEVICE
	Open(
		__inX const std::wstring& device
		)
	{
		OBJECT_ATTRIBUTES oa = { 0 };
		UNICODE_STRING u_dev = { 0 };
		RtlInitUnicodeString(&u_dev, device.c_str());
		InitializeObjectAttributes(&oa, &u_dev, OBJ_INHERIT, nullptr, 0);

		IO_STATUS_BLOCK io = { 0 };
		HANDLE devh = nullptr;
		auto status = ZwCreateFile(
			&devh,
			0x12019f,
			&oa,
			&io,
			nullptr,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			0,
			0,
			0,
			0);
		assert(!status);
		if (!NT_SUCCESS(status))
			return nullptr;
		return devh;
	}
	__checkReturn
	STATUS
	Ioctl(
		__inX DEVICE dev,
		__inX size_t code,
		__in_bcount(inSize) const void* in = nullptr,
		__inX size_t inSize = 0,
		__inout_bcount(outSize) void* out = nullptr,
		__inX size_t outSize = 0
		)
	{
		static IO_STATUS_BLOCK io = { 0 };
		return ZwDeviceIoControlFile(
			dev,
			nullptr,
			nullptr,
			nullptr,
			&io,
			code,
			const_cast<void*>(in),
			inSize,
			out,
			outSize);
	}

};
