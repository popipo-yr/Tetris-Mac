#include "system.h"
#include "../graphics/surface.h"
#include "../graphics/texture.h"
#include "../graphics/pen.h"
#include "../input/input.h"
#include "../script/script.h"
#include "../music/music.h"
#include <mmsystem.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
namespace air
{
	CSystem* g_p_system = NULL;
	CSystem::CSystem(unsigned int w, unsigned int h, const char* t)
	{
		m_hwnd = NULL;
		m_hdc = NULL;
		m_paused = false;
		m_p_init_func = m_p_frame_func = m_p_draw_func = m_p_render_func = NULL;
		m_fixed_delta = 1000 / 60;
		m_win_width = w;
        m_win_height = h;
        m_title = string(t);
        _create_window();
	}
	CSystem::~CSystem()
	{
		_release();
	}
	void CSystem::set_callback(Func option, callback p_func)
	{
		switch (option)
		{
		case INIT:
			m_p_init_func = p_func;
			break;
		case FRAME:
			m_p_frame_func = p_func;
			break;
		case DRAW:
			m_p_draw_func = p_func;
		    break;
		case RENDER:
			m_p_render_func = p_func;
			break;
		default:
		    break;
		}
	}
	void CSystem::run()
	{
	    //_create_window();
		if (m_p_init_func != NULL)
			m_p_init_func();
		g_p_openGL->frame();

		// 娑撹