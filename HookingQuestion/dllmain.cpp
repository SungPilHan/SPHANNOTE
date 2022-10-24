// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport)int Question(int a, int b) {
		int val1 = 0, val2 = 0, i;

		for (i = a * b; i >= 1; i--) {
			if (i % a == 0 && i % b == 0) val1 = i;
		}

		for (i = 1; i <= a && i <= b; ++i)
		{
			if (a % i == 0 && b % i == 0)
				val2 = i;
		}

		return val1 * val2;
	}
#ifdef __cplusplus
}
#endif