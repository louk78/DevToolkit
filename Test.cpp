#include "stdafx.h"
#include "FileMap.h"

extern "C" int __stdcall AsmFunc();
extern "C" void __stdcall CPLUSPLUSFunc();

void Test_FileMap()
{
    const TCHAR* sFile = _T("E:\\Project\\bin\\Debug\\BugReport.exe");
    CFileMap fileMap;

    if(fileMap.Create(sFile, PAGE_READWRITE))
    {
        DWORD dwFileSize = fileMap.GetFileSize();
        LPVOID lpAddr = fileMap.GetMapAddress();
        memset(lpAddr, 0, dwFileSize);
        fileMap.Close();
    }
}

void __stdcall CPLUSPLUSFunc()
{
	MessageBox(NULL,_T("Hello,World"),_T("������C++����"),MB_OK);
}

int main()
{
	// C++�ͻ�໥�����
	int x=AsmFunc();

    Test_FileMap();
    return 0;
}