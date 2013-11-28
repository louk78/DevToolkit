#include "stdafx.h"
#include "DTKPe.h"
#include <winnt.h>
#include <iostream>
#include <string>
#include <atlconv.h>
using namespace std;
using namespace DevToolkit;

CPe::CPe()
{

}

CPe::~CPe()
{

}

BOOL DevToolkit::CPe::IATHook( IN HMODULE hModule,IN LPCTSTR pImageName,IN LPCVOID pTargetFuncAddr,IN LPCVOID pReplaceFuncAddr )
{
	IMAGE_DOS_HEADER* pImgDosHdr = ( IMAGE_DOS_HEADER* )hModule;
	IMAGE_OPTIONAL_HEADER* pImgOptHdr = ( IMAGE_OPTIONAL_HEADER* )( ( DWORD )hModule + pImgDosHdr->e_lfanew + 24 );
	IMAGE_IMPORT_DESCRIPTOR* pImgImportDes = ( IMAGE_IMPORT_DESCRIPTOR* )( ( DWORD )hModule + pImgOptHdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress );
	IMAGE_THUNK_DATA* pImgThunkData = NULL;
	wstring TargetLibraryName;
	DWORD Value = 0;
	DWORD OldProtect = 0;
	DWORD NewProtect = 0;
	LPDWORD FuncAddress = NULL;

	while ( pImgImportDes->Characteristics  != 0 )
	{
		USES_CONVERSION;
		LPCTSTR lpszName = A2W( ( ( LPCSTR )( DWORD )hModule + pImgImportDes->Name ) );
		TargetLibraryName = lpszName;
		if ( TargetLibraryName.compare( pImageName ) == 0 )
		{
			pImgThunkData = ( IMAGE_THUNK_DATA* )( ( DWORD )hModule + pImgImportDes->FirstThunk );
			break;
		}
		pImgImportDes++;
	}
	if ( pImgThunkData == NULL )
	{
		return FALSE;
	}
	while ( pImgThunkData->u1.Function )
	{
		//ѭ������Ŀ�꺯����ַ���ڵ�λ��
		FuncAddress = ( LPDWORD ) & ( pImgThunkData->u1.Function );
		if ( *FuncAddress == ( DWORD )pTargetFuncAddr )
		{
			//�ҵ�Ŀ�꺯���ĵ�ַ��Ȼ���޸�Ϊ���Ӻ����ĵ�ַ
			VirtualProtect( FuncAddress, sizeof( DWORD ), PAGE_READWRITE, &OldProtect );
			if ( !WriteProcessMemory( ( HANDLE ) - 1, FuncAddress, &pReplaceFuncAddr, 4, NULL ) )
			{
				return FALSE;
			}
			VirtualProtect( FuncAddress, sizeof( DWORD ), OldProtect, 0 );
			return TRUE;
		}
		pImgThunkData++;
	}
	return FALSE;
}
