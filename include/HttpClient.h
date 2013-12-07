#pragma once
#include <winhttp.h>

namespace DevToolkit
{
    class EXPORTS_CLASS CHttpClient
    {
        typedef void ( *CallBackDataRecv )( BYTE* pData, DWORD dwDataSize );
    public:
        CHttpClient( LPCTSTR lpszURL, CallBackDataRecv callBack = NULL );
        virtual ~CHttpClient( void );
        
        BOOL SendHttpRequest();
        LPCTSTR GetHttpHeader();
        LPCTSTR GetHttpResponse();
        BOOL SaveResponseToFile( LPCTSTR lpszFileName );
    private:
        TCHAR* m_lpszURL;			//	������URL
        TCHAR* m_lpszHttpHeader;	//	Httpͷ
        BYTE* m_lpszHttpResponse;	//	Http��Ӧ��Ϣ
        TCHAR* m_lpszHostName;		//	������
        TCHAR* m_lpszUrlPath;		//	Url���·��
        INTERNET_PORT m_wPort;		//	�˿ں�
        DWORD m_dwResponseLength;	//	��Ӧ��Ϣ����
    private:
        CallBackDataRecv m_callBackDataRecv;
    };
}

