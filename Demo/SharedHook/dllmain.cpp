// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "Hook.h"

std::shared_ptr<std::string> g_pData;
std::shared_ptr<std::wstring> g_pwData;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_pData = std::shared_ptr<std::string>(new std::string("TestData,测测中文！"));
        g_pwData = std::shared_ptr<std::wstring>(new std::wstring(L"TestData,测测中文！"));
        if (InstallHook()) {

            MessageBox(NULL, L"hook 成功！", L"TEST", MB_OK);
        }
        else {
            MessageBox(NULL, L"hook 失败！", L"TEST", MB_OK);
        }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

