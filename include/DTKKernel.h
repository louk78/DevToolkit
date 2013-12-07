#pragma once

namespace DevToolkit
{
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
    
    /**
    * \brief ����APIHook
    * \param ppSystemFunction ҪHOOK��API��ַ
    * \param pHookFunction �Զ����HOOK������ַ���ɹ������ԭʼAPIʱ���ȵ��øú���
    * \return HOOK�ɹ�����TRUE,ʧ�ܷ���FALSE
    */
    EXPORTS_FUNC BOOL HookAPI( PVOID *ppSystemFunction, PVOID pHookFunction );
    
    /**
    * \brief ж������APIHook
    * \param ppHookedFunction Ҫж�ص�API��ַ
    * \return ж�سɹ�����TRUE,ʧ�ܷ���FALSE
    */
    EXPORTS_FUNC BOOL UnHookAPI( PVOID *ppHookedFunction );
    
    /**
    * \brief ����һ����ַ���ڵ�DLL�ľ�������DLL�����Ѿ������ý��̼��ص��ڴ���
    * \param address
    * \return ����address�����ַ���ڵ�DLL�ľ��
    */
    HMODULE GetModuleFromAddress( LPCVOID address );
    
    /**
    * \brief RVAת��Ϊָ��
    * \param pbImage
    * \param dwRva
    * \return
    */
    PBYTE RvaToPointer( PBYTE pbImage, DWORD dwRva );
    
    /**
    * \brief �ļ�ƫ��ת��ΪRVA
    * \param pbImage
    * \param dwOffset
    * \return
    */
    DWORD OffsetToRva( PBYTE pbImage, DWORD dwOffset );

	/**
    * \brief ģ��ʵ��GetProcAddress����
    * \param phModule Ҫ��ȡ������ģ����
    * \param pProcName Ҫ��ȡ�ĺ���������
    * \return Ҫ��ȡ�ĺ�����phModule�еĵ�ַ
    */
    DWORD GetFunctionAddress( HMODULE phModule, TCHAR* pProcName );
    
}