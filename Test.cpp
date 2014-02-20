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
	MessageBox(NULL,_T("Hello,World"),_T("汇编调用C++函数"),MB_OK);
}

int main()
{
	// C++和汇编互相调用
	int x=AsmFunc();

    Test_FileMap();
    return 0;
}