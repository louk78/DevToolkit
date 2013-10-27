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
    };
}