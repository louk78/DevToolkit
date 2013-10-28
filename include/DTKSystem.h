/**
 * ϵͳ��غ���ʵ��
 */
#pragma once

namespace DevToolkit
{
    class CSystem
    {
    public:
    
        /**
        * \brief ��⵱ǰ�û��Ƿ����ϵͳȨ��
        * \return ��ǰ�û�����ϵͳȨ��,����TRUE,���򷵻�FALSE
        */
        static BOOL IsAdmin();
        
        /**
        * \brief ��GetLastError�������ص�ID��ʽ��Ϊ�ַ���
        * \return ��ʽ������ַ���
        * \warning �����ֶ��ͷŷ��ص��ַ���
        */
        static LPCTSTR GetLastErrMsg();
        
        /**
        * \brief ��ϵͳ����Ĵ���ID��ʽ��Ϊ�ַ���
        * \param dwErrID ϵͳ����Ĵ���ID
        * \return ��ʽ������ַ���
        * \warning �����ֶ��ͷŷ��ص��ַ���
        */
        static LPCTSTR FormatErrMsg( const DWORD dwErrID );
        
        /**
        * \brief �Թ���ԱȨ�����г���
        * \param lpExeFile Ҫ���еĳ���·��
        * \return �ɹ�����TRUE,ʧ�ܷ���FALSE
        */
        static BOOL runAsAdmin( LPCTSTR lpExeFile );
        
        /**
        * \brief ��ǰϵͳ�汾�Ƿ���Vista֮��İ汾
        * \return ��Vista֮��汾����TRUE,���򷵻�FALSE
        */
        static BOOL IsVistaOrLater();
        
        /**
        * \brief ����Ӧ�ó���Ȩ��ΪDEBUGȨ��
        * \param PrivilegeName Ҫ������Ȩ������ ��SE_DEBUG
        * \return �ɹ�����ΪDEBUGȨ�޷���TRUE,���򷵻�FALSE
        */
        static BOOL EnablePrivilege( LPCTSTR PrivilegeName );
        
        /**
        * \brief ��һ��URL
        * \param szURL URL��ַ
        * \param bPriorityIE �Ƿ�����ʹ��IE��
        * \return HINSTANCE
        */
        static HINSTANCE OpenURL( const LPCTSTR szURL, BOOL bPriorityIE );
        
        /**
        * \brief ��ǰϵͳ�Ƿ���64λ�ܹ�
        * \return ��64λ�ܹ�����TRUE,���򷵻�FALSE
        */
        static BOOL IsIA64();
        
        /**
        * \brief ��Explorer�ж�λ��ѡ���ļ�
        * \param lpszFile Ҫ��λ���ļ�·��
        * \return HINSTANCE
        */
        static HINSTANCE OpenFileInExplorer( const LPCTSTR lpszFile );
        
        /**
        * \brief ���ݴ��ھ����ȡģ��·��
        * \param hWnd Ҫ��ȡ·���Ĵ��ھ��
        * \param lpszBuf ·��������
        * \param dwBufSize ��������С
        * \return ģ��·��
        */
        static LPCTSTR GetModulePathByHwnd( const HWND hWnd, LPTSTR lpszBuf, DWORD dwBufSize );
    };
}