#pragma once

namespace DevToolkit
{
    class CString
    {
    public:
        CString();
        virtual ~CString();
        
        /**
        * \brief Ansiת��ΪUnicode
        * \param szAnsiStr Ҫת����Ansi�ַ���
        * \return ת��֮���Unicode�ַ���
        * \warning �����ֶ��ͷŷ��ص��ַ���,���������ڴ�й¶
        */
        static wchar_t* AnsiToUnicode( const char* szAnsiStr );
    protected:
    private:
    };
}