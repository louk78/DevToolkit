#pragma once

#ifdef _USRDLL
#ifndef DEVTOOLKIT_EXPORTS
#define EXPORTS_FUNC extern "C" __declspec(dllimport)
#else
#define EXPORTS_FUNC extern "C" __declspec(dllexport)
#endif
#else
#define EXPORTS_FUNC 
#endif

//#define EXPORTS_FUNC

///////////////////////////////////ϵͳ��غ���///////////////////////////////////////
EXPORTS_FUNC BOOL IsAdmin();

EXPORTS_FUNC LPCTSTR GetLastErrMsg();

EXPORTS_FUNC LPCTSTR FormatErrMsg( const DWORD dwErrID );

EXPORTS_FUNC BOOL runAsAdmin( LPCTSTR lpExeFile );

EXPORTS_FUNC BOOL IsVistaOrLater();

EXPORTS_FUNC BOOL EnablePrivilege( LPCTSTR PrivilegeName );

EXPORTS_FUNC HINSTANCE OpenURL( const LPCTSTR szURL,BOOL bPriorityIE=FALSE );

EXPORTS_FUNC BOOL IsIA64();

EXPORTS_FUNC HINSTANCE OpenFileInExplorer( const LPCTSTR lpszFile );

EXPORTS_FUNC LPCTSTR GetModulePathByHwnd( const HWND hWnd,LPTSTR lpszBuf,DWORD dwBufSize );

///////////////////////////////////�ڴ���غ���///////////////////////////////////////

///////////////////////////////////������غ���///////////////////////////////////////
EXPORTS_FUNC BOOL RemoteInjectDll( DWORD dwPID, LPCTSTR lpszDllName );

EXPORTS_FUNC BOOL RemoteUnInjectDll( DWORD dwPID, LPCTSTR lpszDllName );
