#include <windows.h>
#include <tlhelp32.h>
#include <atlstr.h>

#include "../../../Detours/include/detours.h"


DWORD	GetProcessIdFromProcessName(CString processname)
{
	DWORD dwRet = 0;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap != INVALID_HANDLE_VALUE)
	{
		BOOL bMore = ::Process32First(hProcessSnap, &pe32);
		while (bMore)
		{
			if (processname.CompareNoCase(pe32.szExeFile))
			{
				dwRet = pe32.th32ProcessID;
				break;
			}
			bMore = ::Process32Next(hProcessSnap, &pe32);
		}
		::CloseHandle(hProcessSnap);
	}
	return dwRet;
}

HANDLE GetProcessHandle(DWORD nID)
{
	//PROCESS_ALL_ACCESS 所有能获得的权限
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, nID);
}

int main() {

	DWORD dwProcessId = GetProcessIdFromProcessName("WireCut.EXE");
	if (dwProcessId != 0)
	{
		
	}

}

