#include "StdAfx.h"
#include <Dbt.h>
#include "Communication.h"
const DWORD dwInQueue = 4096;
const DWORD dwOutQueue = 4096;
const DWORD EvtMask = EV_RXCHAR;
HANDLE CSerial::m_hFile = NULL;
CRITICAL_SECTION CSerial::m_Cs;


//Ĭ�Ϲ��캯��
CSerial::CSerial( void )
{
    m_hPort = INVALID_HANDLE_VALUE;
    m_pMainWnd = NULL;
    m_WantRead = 0;
    //	m_bOpened=FALSE;
    m_pReadThread = NULL;

    m_ovWait.hEvent = NULL;
    m_ovRead.hEvent = NULL;
    m_ovWrite.hEvent = NULL;

    ZeroMemory( &m_ovWait, sizeof( m_ovWait ) );
    ZeroMemory( &m_ovRead, sizeof( m_ovRead ) );
    ZeroMemory( &m_ovWrite, sizeof( m_ovWrite ) );
    m_ovRead.hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
    m_ovWrite.hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
    m_ovWait.hEvent = CreateEvent( NULL, TRUE, FALSE, 0 );
    m_bThreadAlive = FALSE;
    ZeroMemory( m_RecvedBuf, 2048 );
    m_CmdID = 0;
}

//Ĭ����������
CSerial::~CSerial( void )
{
    ClosePort();
    DeleteCriticalSection( &m_Cs );
}

//�����Ƿ��Ѿ���
BOOL CSerial::PortIsOpen()
{
    return m_hPort != INVALID_HANDLE_VALUE;
}

//���ûص�����,�����յ������¼�ʱ��CSerial����,֪ͨ�����򴰿ڴ�����Ϣ
void CSerial::SetCallBackFunc( LPVOID CallBackFunc, LPVOID pParam )
{
    //	ThreadParam* param=(ThreadParam*)pParam;
    m_CallBackFunc = ( ReadFunc )CallBackFunc;
    m_pWnd = pParam;
}

HANDLE CSerial::GetPortHandle()
{
    return m_hPort;
}

//�򿪴���
BOOL CSerial::OpenPort( LPTSTR portnum, DWORD dwBaudRate, BYTE byParity, BYTE byStopBits, BYTE byByteSize, HWND hWnd )
{
    m_pMainWnd = pWnd;

    if ( PortIsOpen() )
    {
        ClosePort();
    }

    CString strport;
    strport.Format( _T( "\\\\.\\%s" ), portnum );
    m_hPort = CreateFile( strport, GENERIC_WRITE | GENERIC_READ,
                          0, NULL, OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL );

    if ( INVALID_HANDLE_VALUE == m_hPort )
    {
        TRACE( _T( "CreateFile Failed" ) );
        return FALSE;
    }

    //���ô����������������
    if ( !SetupComm( m_hPort, dwInQueue, dwOutQueue ) )
    {
        TRACE( _T( "SetupComm Failed" ) );
        return FALSE;
    }

    //ȡ�ô�������
    DCB dcb;

    if ( !GetCommState( m_hPort, &dcb ) )
    {
        TRACE( _T( "GetCommState Failed" ) );
        return FALSE;
    }

    //���ô�������
    dcb.BaudRate = dwBaudRate;	//���ò�����

    if ( byParity == 0 )			//������żУ��λ
    {
        dcb.Parity = NOPARITY;
    }
    else if ( byParity == 1 )
    {
        dcb.Parity = ODDPARITY;
    }
    else if ( byParity == 2 )
    {
        dcb.Parity = EVENPARITY;
    }
    else if ( byParity == 3 )
    {
        dcb.Parity = MARKPARITY;
    }
    else if ( byParity == 4 )
    {
        dcb.Parity = SPACEPARITY;
    }
    else
        dcb.Parity = NOPARITY;

    dcb.ByteSize = byByteSize;		//��������λ

    if ( byStopBits == 1 )			//����ֹͣλ
        dcb.StopBits	= ONESTOPBIT;
    else if ( byStopBits == 2 )
        dcb.StopBits	= TWOSTOPBITS;
    else
        dcb.StopBits	= ONE5STOPBITS;

    //����
    // 	dcb.fDsrSensitivity = 0;
    // 	dcb.fDtrControl = DTR_CONTROL_ENABLE;
    // 	dcb.fOutxDsrFlow = 0;
    if ( !SetCommState( m_hPort, &dcb ) )
    {
        TRACE( _T( "SetCommState Failed" ) );
        return FALSE;
    }

    //���ó�ʱ
    COMMTIMEOUTS timeouts;
    //�趨����ʱ
    timeouts.ReadIntervalTimeout = MAXWORD;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.ReadTotalTimeoutConstant = 0;
    //�ڶ�һ�����뻺���������ݺ���������������أ�
    //�������Ƿ������Ҫ����ַ���


    //�趨д��ʱ
    timeouts.WriteTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant = 0;

    if ( !SetCommTimeouts( m_hPort, &timeouts ) )
    {
        TRACE( _T( "SetCommTimeouts Failed" ) );
        return FALSE;
    }

    //���ô����¼�
    if ( !SetCommMask( m_hPort, EvtMask ) )
    {
        TRACE( _T( "SetCommMask Failed" ) );
        return FALSE;
    }

    if ( !PurgeComm( m_hPort, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT ) )
    {
        TRACE( _T( "PurgeComm Failed" ) );
        return FALSE;
    }

    return StartMonitor();
}

//���������߳�
BOOL CSerial::StartMonitor()
{
    if ( NULL == m_pReadThread )
        m_pReadThread = AfxBeginThread( AFX_THREADPROC( ReadThread ), this, THREAD_PRIORITY_NORMAL, 0, 0, 0 );

    if ( NULL == m_pReadThread )
    {
        return FALSE;
    }
    else
        return TRUE;
}


//��������߳�
void CSerial::PauseMonitor()
{
    if ( NULL != m_pReadThread )
    {
        m_pReadThread->SuspendThread();
    }
}

//�ָ������߳�
void CSerial::RestoreMonitor()
{
    if ( NULL != m_pReadThread )
    {
        m_pReadThread->ResumeThread();
    }
}

//ֹͣ�����߳�
void CSerial::StopMonitor()
{
    if ( NULL != m_pReadThread )
    {
        SetCommMask( m_hPort, 0 );
        SetEvent( m_ovWrite.hEvent );
        SetEvent( m_ovRead.hEvent );
        SetEvent( m_ovWait.hEvent );
        m_bThreadAlive = FALSE;

        if ( WaitForSingleObject( m_pReadThread->m_hThread, 5000 ) != WAIT_OBJECT_0 )
            TerminateThread( m_pReadThread, 0 );

        m_pReadThread = NULL;
    }
}

//�����¼��̺߳���
UINT CSerial::ReadThread( LPVOID pParam )
{
    CSerial* pThis = ( CSerial* )pParam;
    DWORD dwErrors = 0;
    DWORD dwEvtMask = 0;
    DWORD Transferred = 0;
    DWORD Readed = 0;
    COMSTAT ComStat;
    BYTE pBuff[4096] = {0};
    pThis->m_bThreadAlive = TRUE;

    if ( NULL == pThis->m_ovWait.hEvent )
    {
        MessageBox( NULL, _T( "�����ȴ��¼�ʧ��" ), _T( "����" ), 0 );
        return -1;
    }

    while ( pThis->m_bThreadAlive )
    {
        if ( !WaitCommEvent( pThis->m_hPort, &dwEvtMask, &pThis->m_ovWait ) )
        {
            if ( ERROR_IO_PENDING == GetLastError() )
            {
                WaitForSingleObject( pThis->m_ovWait.hEvent, INFINITE );

                if ( !GetOverlappedResult( pThis->m_hPort, &pThis->m_ovWait, &Transferred, FALSE ) )
                {
                    if ( ERROR_IO_INCOMPLETE != GetLastError() )
                    {
                        //						AfxMessageBox(_T("GetOverlappedResult Failed"));
                        SetEvent( pThis->m_ovWait.hEvent );
                        //						return -1;
                    }
                }
            }
        }

        switch ( dwEvtMask )
        {
        case EV_RXCHAR:
        {
            if ( !ClearCommError( pThis->m_hPort, &dwErrors, &ComStat ) )
            {
                PurgeComm( pThis->m_hPort, PURGE_RXABORT | PURGE_RXCLEAR );
                //					return -1;
            }

            // 				if (ComStat.cbInQue)
            // 					pThis->OnRecevie();
            if ( ComStat.cbInQue )
            {
                Readed = pThis->ReadData( pBuff, pThis->m_WantRead );
                pThis->m_CallBackFunc( pBuff, Readed, pThis->m_pWnd );
                TRACE( _T( "%dEV_RXCHAR\r\n" ), Readed );
            }
        }
        break;

        case EV_TXEMPTY:
            pThis->OnSend();
            break;

        case EV_BREAK:
            TRACE( _T( "EV_BREAK\r\n" ) );
            break;

        default:
            break;
        }

        ResetEvent( pThis->m_ovWait.hEvent );
    }

    TRACE( _T( "�߳��˳�\r\n" ) );

    if ( NULL != pThis->m_ovWait.hEvent )
    {
        CloseHandle( pThis->m_ovWait.hEvent );
        pThis->m_ovWait.hEvent = NULL;
    }

    return 0;
}

//�رմ���
void CSerial::ClosePort()
{
    if ( !PortIsOpen() )
        return ;


    if ( NULL != m_pReadThread || m_bThreadAlive )
    {
        StopMonitor();
    }

    if ( m_ovRead.hEvent != NULL )
    {
        CloseHandle( m_ovRead.hEvent );
        m_ovRead.hEvent = NULL;
    }

    if ( m_ovWrite.hEvent != NULL )
    {
        CloseHandle( m_ovWrite.hEvent );
        m_ovWrite.hEvent = NULL;
    }

    if ( m_hPort != INVALID_HANDLE_VALUE )
    {
        CloseHandle( m_hPort );
        m_hPort = INVALID_HANDLE_VALUE;
    }
}

//��ȡ����
DWORD CSerial::ReadData( LPVOID pRecvBuf, DWORD WantReadLen, DWORD dwWaitTime/* =10 */ )
{
    DWORD Readed = 0;
    DWORD dwErrorFlags = 0;
    COMSTAT ComStat;
    DWORD ret = 0;

    if ( !ClearCommError( m_hPort, &dwErrorFlags, &ComStat ) && dwErrorFlags > 0 )
    {
        PurgeComm( m_hPort, PURGE_RXABORT | PURGE_RXCLEAR );
        AfxMessageBox( _T( "ClearCommError Failed" ) );
        return 0;
    }

    WantReadLen = WantReadLen > ComStat.cbInQue ? ComStat.cbInQue : WantReadLen;

    if ( !ReadFile( m_hPort, pRecvBuf, WantReadLen, &Readed, &m_ovRead ) )
    {
        if ( ERROR_IO_PENDING == GetLastError() )
        {
            if ( WAIT_OBJECT_0 != WaitForSingleObject( m_ovRead.hEvent, dwWaitTime ) )
            {
                if ( !GetOverlappedResult( m_hPort, &m_ovRead, &Readed, TRUE ) )
                {
                    AfxMessageBox( _T( "��ȡʧ��" ) );
                    return 0;
                }
            }
        }
    }

    //	ResetEvent(m_ovRead.hEvent);
    return Readed;
}

//д������
DWORD CSerial::WriteData( LPCVOID pWriteBuf, DWORD WriteLen )
{
    DWORD Written = 0;
    DWORD dwErrorFlags = 0;
    COMSTAT ComStat;
    DWORD ret = 0;

    if ( !ClearCommError( m_hPort, &dwErrorFlags, &ComStat ) && dwErrorFlags > 0 )
    {
        PurgeComm( m_hPort, PURGE_TXABORT | PURGE_TXCLEAR );
        AfxMessageBox( _T( "ClearCommError Failed" ) );
        return -1;
    }

    if ( !WriteFile( m_hPort, pWriteBuf, WriteLen, &Written, &m_ovWrite ) )
    {
        if ( GetLastError() == ERROR_IO_PENDING )
        {
            ret = WaitForSingleObject( m_ovWrite.hEvent, 1000 );

            switch ( ret )
            {
            case WAIT_OBJECT_0:
                if ( !GetOverlappedResult( m_hPort, &m_ovWrite, &Written, TRUE ) )
                {
//					AfxMessageBox(_T("���ͳɹ�"));
                    SetEvent( m_ovWrite.hEvent );
                    Written = 0;
                }

                break;

            case WAIT_TIMEOUT:
            {
                AfxMessageBox( _T( "���ͳ�ʱ" ) );
                SetEvent( m_ovWrite.hEvent );
                break;
            }

            case WAIT_FAILED:
            {
                AfxMessageBox( _T( "����ʧ��" ) );
                return 0;
                break;
            }

            default:
            {
                Written = 0;
                break;
            }
            }
        }

    }

    //	ResetEvent(m_ovWrite.hEvent);
    return Written;
}

//����
void CSerial::Lock()
{
    EnterCriticalSection( &m_Cs );
}

//����
void CSerial::UnLock()
{
    LeaveCriticalSection( &m_Cs );
}

void CSerial::OnRecevie()
{

}

void CSerial::OnSend()
{

}

//���ñ��������ļ�·��
BOOL CSerial::OpenSaveFilePath( LPCTSTR SaveFilePath )
{
    InitializeCriticalSection( &m_Cs );

    if ( NULL == m_hFile )
    {
        m_hFile = CreateFile( SaveFilePath, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
    }

    if ( INVALID_HANDLE_VALUE != m_hFile )
    {
        return TRUE;
    }
    else
        return FALSE;
}

//�ļ���������
void CSerial::WriteSaveFile( LPVOID pData, DWORD dwWantWrite )
{
    DWORD dwWrited = 0;
    Lock();
    WriteFile( m_hFile, pData, dwWantWrite, &dwWrited, NULL );
    UnLock();
}

//�ر������ļ�
void CSerial::CloseSaveWrite()
{
    if ( INVALID_HANDLE_VALUE != m_hFile || NULL != m_hFile )
    {
        CloseHandle( m_hFile );
        m_hFile = NULL;
    }

    DeleteCriticalSection( &m_Cs );
}

BOOL CSerial::RegisterHardWare( HWND hwnd )
{
    DEV_BROADCAST_HANDLE  NotificationFilter;
    ZeroMemory( &NotificationFilter, sizeof( NotificationFilter ) );
    NotificationFilter.dbch_size = sizeof( DEV_BROADCAST_HANDLE );
    NotificationFilter.dbch_devicetype = DBT_DEVTYP_HANDLE;
    NotificationFilter.dbch_handle = m_hPort;
    HDEVNOTIFY  hDevNotify = RegisterDeviceNotification( hwnd, &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE );

    if ( NULL == hDevNotify )
    {
        TRACE( _T( "ע��Ӳ��֪ͨ�¼�ʧ��" ) );
        return FALSE;
    }

    return TRUE;
}

int CSerial::EnumSerial( LPSTR lpszDest, LPCTSTR lpszFind, GUID SerialGUID )
{
    int iFindCount = 0;
    BOOL bFind = FALSE;
    HDEVINFO hDevinfo = SetupDiGetClassDevs( NULL, NULL, NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES );
    //	DWORD i=0;

    SP_DEVINFO_DATA DevInfo_Data;
    DevInfo_Data.cbSize = sizeof( SP_DEVINFO_DATA );

    //	SetLastError(NO_ERROR);
    for ( DWORD i = 0; SetupDiEnumDeviceInfo( hDevinfo, i, &DevInfo_Data ) && ( GetLastError() != ERROR_NO_MORE_ITEMS ); i++ )
    {
        SP_DEVICE_INTERFACE_DATA Device_Interface_Data;
        Device_Interface_Data.cbSize = sizeof( SP_DEVICE_INTERFACE_DATA );
        DWORD j = 0;
        //		for (DWORD j=0;SetupDiEnumDeviceInterfaces(hDevinfo,&DevInfo_Data,NULL,j,&Device_Interface_Data) && (ERROR_NO_MORE_ITEMS!=GetLastError());j++)
        {
            //			PSP_DEVICE_INTERFACE_DETAIL_DATA Dev_Interface_Detail;
            DWORD RequiredSize = 0;
            // 			SetupDiGetDeviceInterfaceDetail(hDevinfo,&Device_Interface_Data,NULL,0,&RequiredSize,NULL);
            // 			Dev_Interface_Detail=(PSP_DEVICE_INTERFACE_DETAIL_DATA)new TCHAR[sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA)+RequiredSize];
            // 			Dev_Interface_Detail->cbSize=sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
            // 			SetupDiGetDeviceInterfaceDetail(hDevinfo,&Device_Interface_Data,Dev_Interface_Detail,RequiredSize,&RequiredSize,NULL);
            SetupDiGetDeviceRegistryProperty( hDevinfo, &DevInfo_Data, SPDRP_FRIENDLYNAME, NULL, NULL, 0, &RequiredSize );
            TCHAR *name = new TCHAR[RequiredSize + 10];
            SetupDiGetDeviceRegistryProperty( hDevinfo, &DevInfo_Data, SPDRP_FRIENDLYNAME, NULL, ( PBYTE )name, RequiredSize, &RequiredSize );
            int len = _tcslen( lpszFind ) * sizeof( TCHAR ) > _tcslen( name ) * sizeof( TCHAR ) ? _tcslen( name ) * sizeof( TCHAR ) : _tcslen( lpszFind ) * sizeof( TCHAR );
            bFind = TRUE;

            for ( int k = 0; k < len; k++ )
            {
                if ( lpszFind[k] != name[k] )
                {
                    bFind = FALSE;
                    break;
                }
            }

            // 			delete[] Dev_Interface_Detail;
            // 			Dev_Interface_Detail=NULL;
            if ( bFind )
            {
                TCHAR *posstart = NULL;
                posstart = strchr( name, 40 );
                TCHAR *posend = NULL;
                posend = strchr( name, 41 );

                if ( NULL == posstart || NULL == posend )
                {
                    //					AfxMessageBox(_T("���豸��ƥ��"));
                    continue;
                }

                int s = posstart - name + 1;
                int e = posend - name;
                memcpy_s( lpszDest, e - s, &name[s], e - s );
                iFindCount++;
            }

            delete name;
            name = NULL;
        }
    }

    SetupDiDestroyDeviceInfoList( hDevinfo );
    return iFindCount;
}

