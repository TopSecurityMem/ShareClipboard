#include "pch.h"

#include "Hook.h"

extern std::shared_ptr<std::string> g_pData;
extern std::shared_ptr<std::wstring> g_pwData;

typedef HANDLE (WINAPI* PfuncGetClipboardData)(UINT uFormat);
typedef HANDLE (WINAPI* PfuncSetClipboardData)(UINT uFormat, HANDLE hMem);

PVOID g_pOldGetData;
PVOID g_pOldSetData;


BOOL APIENTRY InstallHook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	g_pOldGetData = DetourFindFunction("User32.dll", "GetClipboardData");
	g_pOldSetData = DetourFindFunction("User32.dll", "SetClipboardData");
	DetourAttach(&g_pOldGetData, HookGetClipboardData);
	DetourAttach(&g_pOldSetData, HookSetClipboardData);
	LONG ret = DetourTransactionCommit();
	return ret == NO_ERROR;
}


BOOL APIENTRY UnInstallHook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&g_pOldGetData, HookGetClipboardData);
	DetourDetach(&g_pOldSetData, HookSetClipboardData);
	LONG ret = DetourTransactionCommit();
	return ret == NO_ERROR;
}

HANDLE WINAPI HookGetClipboardData(UINT uFormat)
{
	HANDLE Data = NULL;
	switch (uFormat) {
	case CF_TEXT:
		Data = (HANDLE)g_pData->c_str();
		break;
	case CF_UNICODETEXT:
		Data = (HANDLE)g_pwData->c_str();
		break;
	}
	if (Data) {
		return Data;
	}

	return ((PfuncGetClipboardData)g_pOldGetData)(uFormat);
}


HANDLE WINAPI HookSetClipboardData(UINT uFormat, HANDLE hMem)
{
	return ((PfuncSetClipboardData)g_pOldSetData)(uFormat, hMem);
}


