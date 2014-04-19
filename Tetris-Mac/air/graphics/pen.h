#ifndef pen_h_
#define pen_h_

#include "openGL.h"
#include <map>
#include <string>
using std::map;
using std::string;

namespace air
{
	class CPenManager
	{
	private:
		struct Pen
		{
			unsigned int list_id;
			HFONT		 hfont;
		};
		typedef map<string, Pen>	PenMap;
		PenMap m_pens;
		void _free();	// �ͷ��ڴ�
		void _draw(unsigned int id, float x, float y, unsigned char r, unsigned char g, unsigned char b, string msg);	// �����ı�
	public:
		CPenManager();
		~CPenManager();
		/*
			����һ������
			name��	����������
			size��	����ߴ�
			style��	����������
			space��	����ƽ�����
			weight�������ϸ
		*/
		bool create(string name, int size, string style, int space = 0, int weight = FW_BOLD);
		/*
			�������д�������
			config��	�����ļ�
		*/
		bool create_from_config(string config);
		/*
			�����ı�
			name��	����������
			x��y��	λ��
			c��	    ��ɫ
			msg��	����
		*/
		bool print(string name, float x, float y, color c, string msg);
		/*
			ɾ������
			name��	����������
		*/
		void destroy(string name);
		/*
			��ȡ������Ϣ
			name��	����������
		*/
		unsigned int get_char_height(string name);
		// �õ�ָ���ַ������
		// name������������
		// msg��ָ���ַ���
		unsigned int get_str_width(string name, string msg);
	private:
		CPenManager(const CPenManager&);
		CPenManager& operator=(const CPenManager&);
	};
	extern CPenManager* g_p_pen_mgr;
}

#endif
