#ifndef system_h_
#define system_h_

#define WIN32_LEAN_AND_MEAN
//#include <windows.h>

#include <string>
using std::string;

namespace air
{
	typedef void (*callback)();
	class CTimer;
	class CSystem
	{
	private:
		HWND m_hwnd;
		HDC m_hdc;
		bool m_paused;
		callback m_p_init_func;
		callback m_p_frame_func;
		callback m_p_draw_func;
		callback m_p_render_func;
		unsigned int m_fixed_delta;
		unsigned int m_win_width, m_win_height;
		string m_title;
	public:
	    // ���촰��
	    // w��h������
	    // t������
		CSystem(unsigned int w, unsigned int h, const char* t);
		~CSystem();
        // ���ûص�����
        // option��	����ѡ��
        // p_func��	�ص�����
		enum Func { INIT, FRAME, DRAW, RENDER };
		void set_callback(Func option, callback p_func);
        // ��ѭ��
		void run();
        // �����׼windows��Ϣ
		LRESULT msg_proc(UINT msg, WPARAM wparam, LPARAM lparam);
        // �õ�DC
		HDC getDC() const;
	public:
	    void _create_window();
	    void _release();
	    void _err();
	    CSystem();
		CSystem(const CSystem&);
		CSystem& operator=(const CSystem&);
	};
	extern CSystem* g_p_system;
}

#endif
