#pragma once

namespace DevToolkit
{
    class CProcess
    {
    public:
        CProcess();
        virtual ~CProcess();
        
        /**
        * \brief Զ�߳�ע��DLL
        * \param dwPID Ҫע��DLL�Ľ���PID
        * \param lpszDllName Ҫע���DLL��·��
        * \return ע��ɹ�����TRUE,���򷵻�FALSE
        */
        static BOOL RemoteInjectDll( DWORD dwPID, LPCTSTR lpszDllName );
        
        /**
        * \brief Զ�߳�ж��DLL
        * \param dwPID Ҫж�صĽ���PID
        * \param lpszDllName Ҫж�ص�DLL�����ƻ���·��
        * \return ж�سɹ�����TRUE,���򷵻�FALSE
        */
        static BOOL RemoteUnInjectDll( DWORD dwPID, LPCTSTR lpszDllName );
    };
}