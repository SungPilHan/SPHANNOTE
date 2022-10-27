#include "pch.h"

#pragma once
#define FLG_HEAP_ENABLE_TAIL_CHECK   0x10
#define FLG_HEAP_ENABLE_FREE_CHECK   0x20
#define FLG_HEAP_VALIDATE_PARAMETERS 0x40
#define NT_GLOBAL_FLAG_DEBUGGED (FLG_HEAP_ENABLE_TAIL_CHECK | FLG_HEAP_ENABLE_FREE_CHECK | FLG_HEAP_VALIDATE_PARAMETERS)

BOOL Detect_Patch() {
	BOOL debugged = false;

	PSAPI_WORKING_SET_INFORMATION workingSetInfo;
	QueryWorkingSet(GetCurrentProcess(), &workingSetInfo, sizeof workingSetInfo);
	DWORD requiredSize = sizeof PSAPI_WORKING_SET_INFORMATION * (workingSetInfo.NumberOfEntries + 20);
	PPSAPI_WORKING_SET_INFORMATION pWorkingSetInfo = (PPSAPI_WORKING_SET_INFORMATION)VirtualAlloc(0, requiredSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	BOOL s = QueryWorkingSet(GetCurrentProcess(), pWorkingSetInfo, requiredSize);
	for (int i = 0; i < pWorkingSetInfo->NumberOfEntries; i++)
	{
		PVOID physicalAddress = (PVOID)(pWorkingSetInfo->WorkingSetInfo[i].VirtualPage * 4096);
		MEMORY_BASIC_INFORMATION memoryInfo;
		VirtualQuery((PVOID)physicalAddress, &memoryInfo, sizeof memoryInfo);
		if (memoryInfo.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY))
		{
			if ((pWorkingSetInfo->WorkingSetInfo[i].Shared == 0) || (pWorkingSetInfo->WorkingSetInfo[i].ShareCount == 0))
			{
				debugged = true;
				break;
			}
		}
	}
	return debugged;
}

BOOL isDebugged_SEH = TRUE;

LONG WINAPI CustomUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionPointers)
{
	isDebugged_SEH = FALSE;
	return EXCEPTION_CONTINUE_EXECUTION;
}

BOOL Detect_SEH() {
	PTOP_LEVEL_EXCEPTION_FILTER previousUnhandledExceptionFilter = SetUnhandledExceptionFilter(CustomUnhandledExceptionFilter);
	RaiseException(EXCEPTION_FLT_DIVIDE_BY_ZERO, 0, 0, NULL);
	SetUnhandledExceptionFilter(previousUnhandledExceptionFilter);
	return isDebugged_SEH;
}