#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"
#include "SPHANNOTE.h"
#include "AES.h"

#ifdef _WIN64
#pragma comment (linker, "/INCLUDE:_tls_used")  // See p. 1 below
#pragma comment (linker, "/INCLUDE:tls_callback_func")  // See p. 3 below
#else
#pragma comment (linker, "/INCLUDE:__tls_used")  // See p. 1 below
#pragma comment (linker, "/INCLUDE:_tls_callback_func")  // See p. 3 below
#endif

void NTAPI tls_callback(PVOID DllHandle, DWORD dwReason, PVOID pv) {
	if (dwReason == DLL_THREAD_ATTACH) {
		if (IsDebuggerPresent()) {
			::MessageBox(NULL, L"Debugger is Catched!!\nProgram is stopped!!", L"AntiDebug", MB_OK);
			exit(0);
		}
		else {
			AES enc;
			std::string data;
			data = enc.AESDecrypt("53C724BE3E2F91448894930D9D8B6D85A84C4B16880FA9F7BE95A9238275C8D02B1D62108DC0FD8DBD6638DE8A4A44A6");
			CString cstr(data.c_str());
		}
	}	
}

// Explained in p. 3 below
#ifdef _WIN64
#pragma const_seg(".CRT$XLAAA")
EXTERN_C const
#else
#pragma data_seg(".CRT$XLAAA")
EXTERN_C
#endif
PIMAGE_TLS_CALLBACK tls_callback_func = tls_callback;
#ifdef _WIN64
#pragma const_seg()
#else
#pragma data_seg()
#endif //_WIN64