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
		//HWND m_hwnd;
		//HDC m_hdc;
		bool m_paused;
		callback m_p_init_func;
		callback m_p_frame_func;
		callback m_p_draw_func;
		callback m_p_render_func;
		unsigned int m_fixed_delta;
		unsigned int m_win_width, m_win_height;
		string m_title;
	public:
	    // 閺嬪嫰