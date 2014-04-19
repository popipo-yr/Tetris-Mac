#ifndef surface_h_
#define surface_h_

#include "openGL.h"

namespace air
{
	class COpenGL
	{
	public:
		// 2D ģʽ�� ��Ļ����ϵΪ�ѿ�������ϵ�ڶ����ޣ����½�Ϊԭ��
		// 3D ģʽ�� ��������ϵ
		enum Mode	{ _2D, _3D };
	private:
		HGLRC m_hrc;
		int	  m_width, m_height;
		Mode  m_mode;
		void _init();
	public:
		/*
			���� OpenGL ��Ⱦϵͳ
			hdc��			�豸������
			width��height��	���ڳߴ�
		*/
		COpenGL(HDC hdc, int width, int height);
		~COpenGL();
		/*
			���ڳߴ�ı�
			new_width��new_height��	�µĴ��ڳߴ�
		*/
		void resize(int new_width, int new_height);
		/*
			ÿ֡���ã������ʹ�����
		*/
		void frame() const;
		/*
			������Ⱦģʽ
		*/
		void twoD();
		void threeD();
		/*
			��������
			hdc��		���н������豸������
		*/
		void swap_buff(HDC hdc) const;
		/*
			������Ⱦģʽ
		*/
		Mode get_mode() const;
		/*
			�õ��ӿڸ�
		*/
		int get_height() const;
	private:
		COpenGL();
		COpenGL(const COpenGL&);
		COpenGL& operator =(const COpenGL&);
	};
	extern COpenGL* g_p_openGL;

	//////////////////////////////////////////////////////////////////////////
	class CSurface
	{
	public:
		CSurface();
		~CSurface();
		/*
			�����߶�
			start_x��start_y��	�߶����
			end_x��end_y��		�߶��յ�
			color��				��ɫ
			size��				�߶δ�ϸ
		*/
		bool draw_line(float start_x, float start_y, float end_x, float end_y, color c, float size = 1.0f);
		/*
			���ƾ���
			x��y��			�������½�����
			width��height��	���ο�͸�
			color��			��ɫ
			fill��			�Ƿ����
		*/
		bool draw_rect(float x, float y, float width, float height, color c, bool fill = true);
		/*
			����Բ
			x��y��		Բ������
			radius��	�뾶
			color��		��ɫ
			fill��		�Ƿ����
		*/
		bool draw_circle(float x, float y, float radius, color c, bool fill = true);
		/*
			��������
			p_name��				����������
			x��y��					��Ļ����
			sub_x��sub_y��			�����������
			sub_width��sub_height��	����ߴ�
		*/
		bool draw_texture(const char* p_name, float x, float y, float sub_x = 0.0f, float sub_y  = 0.0f, float sub_width = 0.0f, float sub_height = 0.0f);
		/*
			�����ӻ��棬���� alpha ����
			p_name��				����������
			x��y��					��Ⱦ��Ļλ��
			sub_x��sub_y��			�����������
			sub_width��sub_height��	����ߴ�
		*/
		bool draw_sprite(const char* p_name, float x, float y, float sub_x = 0.0f, float sub_y = 0.0f, float sub_width = 0.0f, float sub_height = 0.0f);
	private:
		CSurface(const CSurface&);
		CSurface& operator=(const CSurface&);
	};
	extern CSurface* g_p_surface;
}

#endif
