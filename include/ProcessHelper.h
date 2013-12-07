#pragma once
#include <Windows.h>

namespace DevToolkit
{
	enum INTEGRITYLEVEL {
		INTEGRITY_UNKNOWN,
		LOW_INTEGRITY,
		MEDIUM_INTEGRITY,
		HIGH_INTEGRITY,
	};

    class EXPORTS_CLASS CProcessHelper
    {
    public:
        CProcessHelper( );
        virtual ~CProcessHelper( void );
        
    public:
		// �Ե�ǰ��¼�û�Ȩ�޴򿪽���
        BOOL Open(DWORD dwID);

		// ��SE_DEBUGȨ�޴򿪽���
		BOOL OpenWithPrivileged(DWORD dwID);
		BOOL OpenWithAccess(DWORD dwID,DWORD access_flags );
        void Close();
        BOOL Terminal();
        BOOL ReadMemory( LPCVOID lpAddr, LPVOID lpBuf, DWORD dwReadSize );
        BOOL WriteMemory( LPVOID lpAddr, LPCVOID lpBuf, DWORD dwWriteSize );
        
        DWORD GetPID()const;
        HANDLE GetHandle();
        DWORD GetThreadCount();
        DWORD GetParentPID();
        DWORD GetPriClassBase();

		// ��ȡ��ǰ���̵�����·��
        LPCTSTR GetFullPathName();

		// ��ȡ��ǰ�����ڽ��̹������еĶ�����
		LPCTSTR GetName();
        BOOL GetIntegrityLevel(INTEGRITYLEVEL* pLevel);
    private:
        DWORD m_dwPID;
        HANDLE m_hProcess;
        DWORD m_dwThreadCount;
        DWORD m_dwParentProcessID;
        DWORD m_dwPriClassBase;

		// ����ȫ·��
        TCHAR m_sFullPathName[MAX_PATH];

		// ���̶�����
		TCHAR m_sName[MAX_PATH];
    };
}

