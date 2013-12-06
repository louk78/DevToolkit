/********************************************************************
�ļ�˵��:	����ͨѶ��CSerial
��ǰ�汾:	1.1
����:		�ƽ��� Copyright (c) 2010
��������:	2010��9��28�� 23ʱ44��25��

��ʷ�汾:
1.1		������ö�ٴ��ڹ��� 2010��10��17��22ʱ46��
1.0		ԭʼ�汾
*********************************************************************/

#pragma once
#include "SerialCom.h"
#include <SetupAPI.h>
#include <process.h>
#include <string>
using namespace std;
#pragma comment(lib,"setupapi.lib")
// #ifdef _USRDLL
// #define EXPORTCLASS __declspec(dllexport)
// #else
// #define EXPORTCLASS __declspec(dllimport)
// #endif

static const GUID SerialGUID =
{ 0x4d36e978, 0xe325, 0x11ce, { 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18 } };

static const GUID USBGUID =
{ 0x36fc9e60, 0xc465, 0x11cf, { 0x80, 0x56, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };

class /*EXPORTCLASS*/ CSerial : public CSerialCom
{
public:
    CSerial( void );
    virtual ~CSerial( void );
    BOOL RegisterHardWare( HWND hwnd );
    BOOL PortIsOpen();
    BOOL OpenPort( LPTSTR portnum, DWORD dwBaudRate = 9600, BYTE byParity = NOPARITY, BYTE byStopBits = ONESTOPBIT, BYTE byByteSize = 8, HWND hWnd=NULL );
    void ClosePort();
    DWORD ReadData( LPVOID pRecvBuf, DWORD ReadLen, DWORD dwWaitTime = 10 );
    DWORD WriteData( LPCVOID pWriteBuf, DWORD WriteLen );
    virtual void OnRecevie();
    virtual void OnSend();
    static UINT ReadThread( LPVOID pParam );
    BOOL StartMonitor();
    void PauseMonitor();
    void RestoreMonitor();
    void StopMonitor();

    int EnumSerial( LPSTR lpszDest, LPCTSTR lpszFind, GUID SerialGUID = SerialGUID );

    typedef int( *ReadFunc )( LPVOID pData, DWORD size, LPVOID pWnd );
    void SetCallBackFunc( LPVOID CallBackFunc, LPVOID pParam );
    static void Lock();
    static void UnLock();
    static BOOL OpenSaveFilePath( LPCTSTR SaveFilePath );
    static void WriteSaveFile( LPVOID pData, DWORD dwWantWrite );
    static void CloseSaveWrite();
    HANDLE GetPortHandle();
private:
    static HANDLE m_hFile;
    BOOL m_bThreadAlive;
    HANDLE m_hPort;
    CWinThread* m_pReadThread;
    OVERLAPPED m_ovWait;
    OVERLAPPED m_ovWrite;
    OVERLAPPED m_ovRead;
    ReadFunc m_CallBackFunc;
    LPVOID m_pWnd;
    static CRITICAL_SECTION m_Cs;
protected:
    CWnd* m_pMainWnd;
};


