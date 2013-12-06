#pragma once


/**
* \brief HOOK IAT
* \param hModule EXE�����ַ
* \param pImageName EXE�е����DLLģ������
* \param pTargetFuncAddr ҪHOOK�ĺ�������
* \param pReplaceFuncAddr HOOK�ɹ��󣬵��õ��Զ��庯��
* \return HOOK�ɹ�����TRUE,ʧ�ܷ���FALSE
*/
EXPORTS_FUNC BOOL IATHook( IN HMODULE hModule, IN LPCTSTR pImageName, IN LPCVOID pTargetFuncAddr, IN LPCVOID pReplaceFuncAddr );

/**
* \brief ����Ӧ�ó���Ȩ��ΪDEBUGȨ��
* \param PrivilegeName Ҫ������Ȩ������ ��SE_DEBUG
* \return �ɹ�����ΪDEBUGȨ�޷���TRUE,���򷵻�FALSE
*/
EXPORTS_FUNC BOOL EnablePrivilege( LPCTSTR PrivilegeName );

/**
* \brief Զ�߳�ע��DLL
* \param dwPID Ҫע��DLL�Ľ���PID
* \param lpszDllName Ҫע���DLL��·��
* \return ע��ɹ�����TRUE,���򷵻�FALSE
*/
EXPORTS_FUNC BOOL RemoteInjectDll( DWORD dwPID, LPCTSTR lpszDllName );

/**
* \brief Զ�߳�ж��DLL
* \param dwPID Ҫж�صĽ���PID
* \param lpszDllName Ҫж�ص�DLL�����ƻ���·��
* \return ж�سɹ�����TRUE,���򷵻�FALSE
*/
EXPORTS_FUNC BOOL RemoteUnInjectDll( DWORD dwPID, LPCTSTR lpszDllName );

EXPORTS_FUNC BOOL HookAPI(PVOID *ppSystemFunction, PVOID pHookFunction);

EXPORTS_FUNC BOOL UnHookAPI(PVOID *ppHookedFunction);