#pragma once
#include <Windows.h>
#include "DTKKernel.h"

namespace DevToolkit
{
    enum INTEGRITYLEVEL
    {
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
        BOOL Open( DWORD dwID );
        
        // ��SE_DEBUGȨ�޴򿪽���
        BOOL OpenWithPrivileged( DWORD dwID );
        
        // ��ָ����Ȩ�޴򿪽���
        BOOL OpenWithAccess( DWORD dwID, DWORD access_flags );
        
        // �ͷ���Դ
        void Close();
        
        // ��������
        BOOL Terminal();
        
        // �ӽ��̶�ȡ�ڴ�
        BOOL ReadMemory( LPCVOID lpAddr, LPVOID lpBuf, DWORD dwReadSize );
        
        // �����д������
        BOOL WriteMemory( LPVOID lpAddr, LPCVOID lpBuf, DWORD dwWriteSize );
        
        // ���ؽ���PID
        DWORD GetPID()const;
        
        // ���ؽ��̾��
        HANDLE GetHandle();
        
        
        DWORD GetThreadCount();
        
        // ��ȡ������PID
        DWORD GetParentPID();
        
        // ��ȡ����PEB��ַ
        DWORD GetPEBBase();
        
        // ��ȡ��ǰ���̵�����·��
        LPCTSTR GetFullPathName();
        
        // ��ȡ��ǰ�����ڽ��̹������еĶ�����
        LPCTSTR GetName();
        
        // ��ȡ���������Լ���
        BOOL GetIntegrityLevel( INTEGRITYLEVEL* pLevel );
        
    protected:
        // ��ȡ���̻�����Ϣ
        BOOL GetBaseInformation( LPPROCESS_BASIC_INFORMATION lpBaseInfo );
    private:
        // ����PID
        DWORD m_dwPID;
        
        // ���̾��
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

