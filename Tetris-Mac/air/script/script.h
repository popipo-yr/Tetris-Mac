/*
	�ű������࣬Luaʵ��
*/
#ifndef script_h_
#define script_h_

#include "lua/lua.hpp"

namespace air
{
	class CLog;
	class CScript
	{
	private:
		lua_State* m_L;
	public:
		CScript();
		~CScript();
		/*
			����ű�
			p_file��	�ű��ļ�
		*/
		void load(const char* p_file);
		/*
			���ýű�����
			p_fun_name��	�ű�������
			arg_num��		��������
		*/
		void call(const char* p_fun_name);
		/*
			���������ýű�����
			p_fun_name��	�ű�������
			p_params��		�ű���������
			����ʵ����	call("fun_name", "ids", 10, 20.0, "abc")
		*/
		void call(const char* p_fun_name, const char* p_params, ...);
		// ���ýű�����
		// p_func���ű�������
		// in_num�������������
		// p_in�������������
		// out_num�������������
		// p_out�������������
		void call(const char* p_func, int in_num, float* p_in, int out_num, float* p_out);
	private:
		void _register_func();
		void _err(const char* p_msg, ...);
		CScript(const CScript&);
		CScript& operator=(const CScript&);
	};
	extern CScript* g_p_script;
}

#endif
