#ifndef HOOK_H_
#define HOOK_H_

#include "../../Detours/include/detours.h"

BOOL APIENTRY InstallHook();
BOOL APIENTRY UnInstallHook();
HANDLE WINAPI HookGetClipboardData(UINT uFormat);
HANDLE WINAPI HookSetClipboardData(UINT uFormat, HANDLE hMem);


#endif // HOOK_H_
