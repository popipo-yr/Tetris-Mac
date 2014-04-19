#ifndef texture_h_
#define texture_h_

#include <string>
#include <map>
using std::string;
using std::map;

namespace air
{
	class CTextureManager
	{
	public:
		struct Texture					// ����ṹ��	
		{
			unsigned int id;			// ��������
			unsigned int width, height;	// ����ߴ�
		};

	private:
		typedef map<string, Texture>	TexMap;
		TexMap m_texs;

		void _free();

	public:
		CTextureManager();
		~CTextureManager();

		/*
			����ָ��͸��ɫ�� BMP �ļ���Ϊ����
			p_file��	ͼ���ļ�·��
			p_name��	����������
			r��g��b��	͸��ɫ��Ĭ��Ϊ��ɫ RGB(128,0,128)
		*/
		bool load_bmp(const char* p_file, const char* p_name, unsigned char r = 128, unsigned char g = 0, unsigned char b = 128);

		/*
			���� TGA �ļ���Ϊ����
			p_file��	ͼ���ļ�·��
			p_name��	����������
		*/
		bool load_tga(const char* p_file, const char* p_name);

		/*
			�������ļ�����������
			p_config��	�����ļ���
		*/
		bool load_from_config(const char* p_config);

		/*
			�õ��������Ϣ
			p_name��	����������
		*/
		unsigned int get_id(const char* p_name) const;
		unsigned int get_width(const char* p_name) const;
		unsigned int get_height(const char* p_name) const;
		const Texture* get_texture(const char* p_name) const;

		/*
			��դ�������ֲ�����ԭ��Ϊ�������ģ�����������Ϊ������ת��
			p_name��				������
			sub_x��sub_y��			�������
			sub_width��sub_height��	�ߴ�
		*/
		bool raster_origin_center(const char* p_name, float sub_x = 0.0f, float sub_y  = 0.0f, float sub_width = 0.0f, float sub_height = 0.0f) const;

		/*
			��դ�������ֲ�����ԭ��Ϊ�������½�
			p_name��				������
			sub_x��sub_y��			�������
			sub_width��sub_height��	�ߴ�
		*/
		bool raster_origin_leftbottom(const char* p_name, float sub_x = 0.0f, float sub_y  = 0.0f, float sub_width = 0.0f, float sub_height = 0.0f) const;

	private:
		CTextureManager(const CTextureManager&);
		CTextureManager& operator =(const CTextureManager&);
	};
	extern CTextureManager* g_p_tex_mgr;

	//////////////////////////////////////////////////////////////////////////
	// ͼ������
	class CImageFont
	{
	private:
		struct Font
		{
			unsigned int id;		// ��ʾ�б�ID
			unsigned int width;		// �ַ���
			unsigned int height;	// �ַ���
			unsigned int tex_id;	// ����ID
		};
		Font m_font;
		unsigned int m_ascii_to_list[128];

		void _init_char_to_list(unsigned int start);
		void _print(char c);
		void _free();

	public:
		CImageFont();
		~CImageFont();

		/*
			����һ��ͼ�����壬�������ⲿλͼ���д�������
			p_tex_name��������
		*/
		bool create(const char* p_tex_name);

		/*
			��ʾ��Ϣ
			x��y��	λ��
			msg��	��Ϣ
		*/
		void print(float x, float y, string msg);

	private:
		CImageFont(const CImageFont&);
		CImageFont& operator=(const CImageFont&);
	};
}

#endif