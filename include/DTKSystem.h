/**
 * ϵͳ��غ���ʵ��
 */
#pragma once

namespace DevToolkit
{
    /**
    * \brief ��⵱ǰ�û��Ƿ����ϵͳȨ��
    * \return ��ǰ�û�����ϵͳȨ��,����TRUE,���򷵻�FALSE
    */
    EXPORTS_FUNC BOOL IsAdmin();
    
    /**
    * \brief ��GetLastError�������ص�ID��ʽ��Ϊ�ַ���
    * \return ��ʽ������ַ���
    * \warning �����ֶ��ͷŷ��ص��ַ���
    */
    EXPORTS_FUNC BOOL GetLastErrMsg( LPTSTR lpBuf, DWORD dwBufSize );
    
    /**
    * \brief ��ϵͳ����Ĵ���ID��ʽ��Ϊ�ַ���
    * \param dwErrID ϵͳ����Ĵ���ID
    * \return ��ʽ������ַ���
    * \warning �����ֶ��ͷŷ��ص��ַ���
    */
    EXPORTS_FUNC BOOL FormatErrMsg( const DWORD dwErrID, LPTSTR lpBuf, DWORD dwBufSize );
    
    /**
    * \brief �Թ���ԱȨ�����г���
    * \param lpExeFile Ҫ���еĳ���·��
    * \return �ɹ�����TRUE,ʧ�ܷ���FALSE
    */
    EXPORTS_FUNC BOOL RunAsAdmin( LPCTSTR lpExeFile );
    
    /**
    * \brief ��ǰϵͳ�汾�Ƿ���Vista֮��İ汾
    * \return ��Vista֮��汾����TRUE,���򷵻�FALSE
    */
    EXPORTS_FUNC BOOL IsVistaOrLater();
    
    
    /**
    * \brief ��һ��URL
    * \param szURL URL��ַ
    * \param bPriorityIE �Ƿ�����ʹ��IE��
    * \return HINSTANCE
    */
    EXPORTS_FUNC BOOL OpenURL( const LPCTSTR szURL, BOOL bPriorityIE=FALSE );
    
    /**
    * \brief ��ǰϵͳ�Ƿ���64λ�ܹ�
    * \return ��64λ�ܹ�����TRUE,���򷵻�FALSE
    */
    EXPORTS_FUNC BOOL IsIA64();
    
    /**
    * \brief ��Explorer�ж�λ��ѡ���ļ�
    * \param lpszFile Ҫ��λ���ļ�·��
    * \return HINSTANCE
    */
    EXPORTS_FUNC BOOL OpenFileInExplorer( const LPCTSTR lpszFile );
    
    /**
    * \brief ���ݴ��ھ����ȡģ��·��
    * \param hWnd Ҫ��ȡ·���Ĵ��ھ��
    * \param lpszBuf ·��������
    * \param dwBufSize ��������С
    * \return ģ��·��
    */
    EXPORTS_FUNC LPCTSTR GetModulePathByHwnd( const HWND hWnd, LPTSTR lpszBuf, DWORD dwBufSize );
    
    EXPORTS_FUNC BOOL ParseURLs( LPCTSTR pwszURL, LPTSTR pwszHostName, LPTSTR pwszPath, WORD& wPort );
    
    EXPORTS_FUNC BOOL EncodeURL( LPCTSTR pwszURL, int iLen, LPTSTR pwszRetURL, int& iRetLen ) ;
    
    EXPORTS_FUNC HRESULT OpenUrlWithDefaultBrowser( LPCTSTR lpUrl );
    
    EXPORTS_FUNC BOOL IsHasNetConnect();
    
    EXPORTS_FUNC BOOL OpenUrlWithIE( LPCTSTR lpszURL );
    
    EXPORTS_FUNC BOOL IsWin7();
    
    EXPORTS_FUNC BOOL IsXP();
    
    EXPORTS_FUNC BOOL IsVista();
    
    EXPORTS_FUNC BOOL IsWin8();
    
    EXPORTS_FUNC BOOL IsWin2000();
    
    EXPORTS_FUNC BOOL IsWinNT();
    
    EXPORTS_FUNC BOOL SetProcessAppUserModelID( LPCWSTR lpwsProcessUserModelID );
    
    /**
    * \brief ����ϵͳ���ļ��򿪡��Ի���
    * \param hWnd
    * \param lpszTitle �Ի������
    * \param lpszFilter �Ի�������ַ������ַ���
    * \param lpFileName �����򿪡���ť��ѡ����ļ�·��
    * \return �򿪳ɹ�����TRUE��ʧ�ܷ���FALSE
    */
    BOOL OpenFileDlg( HWND hWnd, LPCTSTR lpszTitle, LPCTSTR lpszFilter, LPTSTR lpFileName );
    
    /**
    * \brief ����ϵͳ��Ŀ¼ѡ�񡱶Ի���
    * \param hWnd
    * \param lpszTitle �Ի������
    * \param sDirectory ����ȷ������ť��ѡ����ļ���·��
    * \return �򿪳ɹ�����TRUE��ʧ�ܷ���FALSE
    */
    BOOL SelectDirDlg( HWND hWnd, LPCTSTR lpszTitle, LPTSTR sDirectory );
    
    DWORD GetThreadIDByProcssID( DWORD dwProcessID );
    
    HWND GetWindowHandleByPID( DWORD dwProcessID );
    
    /**
    * \brief ����һ������
    * \param lpszAppName Ҫ�����Ľ��̵�·��
    * \param lpszCmdLine ���ݸ����̵�������
    * \param bShow �Ƿ���ʾ����
    * \return �����ɹ�����TRUE��ʧ�ܷ���FALSE
    */
    BOOL LanuchProcess( LPCTSTR lpszAppName, LPTSTR lpszCmdLine = NULL, BOOL bShow = TRUE );
    
}