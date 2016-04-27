#pragma once

#include <common/usr_common.h>

#include <winternl.h>
#include <ntstatus.h>

#define _Out_
#define _In_
#define _In_opt_
#define _Out_opt_

NTSTATUS ZwCreateFile_fn(
  _Out_    PHANDLE            FileHandle,
  _In_     ACCESS_MASK        DesiredAccess,
  _In_     POBJECT_ATTRIBUTES ObjectAttributes,
  _Out_    PIO_STATUS_BLOCK   IoStatusBlock,
  _In_opt_ PLARGE_INTEGER     AllocationSize,
  _In_     ULONG              FileAttributes,
  _In_     ULONG              ShareAccess,
  _In_     ULONG              CreateDisposition,
  _In_     ULONG              CreateOptions,
  _In_opt_ PVOID              EaBuffer,
  _In_     ULONG              EaLength
);
extern
decltype(&ZwCreateFile_fn) ZwCreateFile;

NTSTATUS ZwDeviceIoControlFile_fn(
  _In_      HANDLE           FileHandle,
  _In_opt_  HANDLE           Event,
  _In_opt_  PIO_APC_ROUTINE  ApcRoutine,
  _In_opt_  PVOID            ApcContext,
  _Out_     PIO_STATUS_BLOCK IoStatusBlock,
  _In_      ULONG            IoControlCode,
  _In_opt_  PVOID            InputBuffer,
  _In_      ULONG            InputBufferLength,
  _Out_opt_ PVOID            OutputBuffer,
  _In_      ULONG            OutputBufferLength
);
extern
decltype(&ZwDeviceIoControlFile_fn) ZwDeviceIoControlFile;
