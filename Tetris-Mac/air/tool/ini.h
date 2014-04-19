/*
	ini �ļ�������
*/
#ifndef ini_h_
#define ini_h_

#include <map>
#include <string>
using std::map;
using std::string;

namespace air
{
	class CIni
	{
	private:
		typedef map<string, string>		IniSection;
		typedef map<string, IniSection>	IniAllSections;
		IniAllSections m_all_sections;
	public:
		CIni();
		~CIni();
		/*
			���벢���������ļ�
			p_ini��		�����ļ�·��
			����ֵ��	�ɹ� / ʧ��
		*/
		bool load(const char* p_ini);
		/*
			�������ļ��ж�ȡ��Ϣ
			section��	����
			name��		������
			value��		��ȡ����ֵ
			����ֵ��	�ɹ� / ʧ��
		*/
		bool read_int(const string& section, const string& name, int& value);
		bool read_float(const string& section, const string& name, float& value);
		bool read_string(const string& section, const string& name, string& value);
		bool read_3ub(string section, string name, unsigned char& x, unsigned char& y, unsigned char& z);
		/*
			�ͷ��ڴ�
		*/
		void free();

	private:
		CIni(const CIni&);
		CIni& operator = (const CIni&);
	};
}

#endif
