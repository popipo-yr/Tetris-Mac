#include "system.h"
#include "../graphics/surface.h"
#include "../graphics/texture.h"
#include "../graphics/pen.h"
#include "../input/input.h"
#include "../script/script.h"
#include "../music/music.h"
#include <unistd.h>
#include <GLFW/glfw3.h>
//#include <mmsystem.h>



//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
namespace air
{
	CSystem* g_p_system = NULL;
	CSystem::CSystem(unsigned int w, unsigned int h, const char* t)
	{
		//m_hwnd = NULL;
		//m_hdc = NULL;
		m_paused = false;
		m_p_init_func = m_p_frame_func = m_p_draw_func = m_p_render_func = NULL;
		m_fixed_delta = 1000 / 60;
		m_win_width = w;
        m_win_height = h;
        m_title = std::string(t);
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

        
		// 主循环
		//MSG msg;
		//unsigned long last = timeGetTime();
        unsigned long last = 0;
        
        gettimeofday(&m_lastTime,NULL);
        

            
            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(_p_window))
            {
                /* Render here */
                

                
                
               // if (!m_paused)
               // {
                struct timeval tpend;
                gettimeofday(&tpend, NULL);
                unsigned long dt = tpend.tv_usec - m_lastTime.tv_usec;
                if (dt >= m_fixed_delta)
                {
                    gettimeofday(&m_lastTime, NULL);
                    
                        last = time(0);
                        // 更新子系统
                        //g_p_music->update();
                        g_p_input->update();
                        // 游戏逻辑
                        if (m_p_frame_func != NULL)
                            m_p_frame_func();
                        // 渲染逻辑
                        g_p_openGL->frame();
                        g_p_openGL->twoD();
                        if (m_p_draw_func != NULL)
                            m_p_draw_func();
                        g_p_openGL->threeD();
                        if (m_p_render_func != NULL)
                            m_p_render_func();
                        g_p_openGL->swap_buff(m_hdc);
                        
                        //g_p_input->update();
                        
                        
                        /* Swap front and back buffers */
                        glfwSwapBuffers(_p_window);
                        
                        /* Poll for and process events */
                        glfwPollEvents();
                        
                    
                    } else {
                                   //if (dt + 5 < m_fixed_delta) ;
                   
                                sleep(1);
                        }
                }
            //}


	}

//	void CSystem::run()
//	{
//	    //_create_window();
//		if (m_p_init_func != NULL)
//			m_p_init_func();
//		g_p_openGL->frame();
//        
//        return;
//        
//		// 主循环
//		//MSG msg;
//		//unsigned long last = timeGetTime();
//        unsigned long last = 0;
//        
//        gettimeofday(&m_lastTime,NULL);
//        
//		for (;;)
//		{
////			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
////			{
////			    if (msg.message == WM_QUIT)
////                    break;
////				TranslateMessage(&msg);
////				DispatchMessage(&msg);
////			}
//			//else
//			{
//			    if (!m_paused)
//                {
//                    unsigned int dt = time(0) - last;
//                    if (dt > m_fixed_delta)
//                    {
//                        last = time(0);
//                        // 更新子系统
//                        //g_p_music->update();
//                        g_p_input->update();
//                        // 游戏逻辑
//                        if (m_p_frame_func != NULL)
//                            m_p_frame_func();
//                        // 渲染逻辑
//                        g_p_openGL->frame();
//                        g_p_openGL->twoD();
//                        if (m_p_draw_func != NULL)
//                            m_p_draw_func();
//                        g_p_openGL->threeD();
//                        if (m_p_render_func != NULL)
//                            m_p_render_func();
//                        g_p_openGL->swap_buff(m_hdc);
//                        
//                        //g_p_input->update();
//                    }
////                    else
////                    {
////                        if (dt + 5 < m_fixed_delta) ;
////                        
////                        sleep(1);
////                        //Sleep(1);
////                    }
//                }
//                else
//                {
//                    //Sleep(1);
//                }
//			}
//		}
//	}
    
    void CSystem::loop(){
        
        
        if (!m_paused)
        {
            struct timeval tpend;
            unsigned long dt = tpend.tv_usec - m_lastTime.tv_usec;
            if (dt >= m_fixed_delta)
            {
                gettimeofday(&m_lastTime, NULL);
                
                // 更新子系统
                //g_p_music->update();
                //g_p_input->update();
                
                // 游戏逻辑
                if (m_p_frame_func != NULL)
                    m_p_frame_func();
                // 渲染逻辑
                g_p_openGL->frame();
                g_p_openGL->twoD();
                if (m_p_draw_func != NULL)
                    m_p_draw_func();
                g_p_openGL->threeD();
                if (m_p_render_func != NULL)
                    m_p_render_func();
                g_p_openGL->swap_buff(m_hdc);
            
                g_p_input->update();
            }
//            else
//            {
//                if (dt + 5 < m_fixed_delta)
//                    sleep(1);
//            }
        }
        else
        {
            sleep(1);
        }
    
    }
//	LRESULT CSystem::msg_proc(UINT msg, WPARAM wparam, LPARAM lparam)
//	{
//		switch (msg)
//		{
//            case WM_ACTIVATE:
//                if (LOWORD(wparam) == WA_INACTIVE)
//                    m_paused = true;
//                else
//                    m_paused = false;
//                return 0;
//            case WM_SIZE:
//                g_p_openGL->resize(LOWORD(lparam), HIWORD(lparam));
//                return 0;
//            case WM_CLOSE:
//                DestroyWindow(m_hwnd);
//                return 0;
//            case WM_DESTROY:
//                PostQuitMessage(0);
//                return 0;
//		}
//		return DefWindowProc(m_hwnd, msg, wparam, lparam);
//	}
//	HDC CSystem::getDC() const
//	{
//		return m_hdc;
//	}
    
    
    
	void CSystem::_create_window()
	{
        
        /* Create a windowed mode window and its OpenGL context */
        _p_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!_p_window)
        {
            glfwTerminate();
            return;
        }
        
        /* Make the window's context current */
        glfwMakeContextCurrent(_p_window);
        
        
//        glutInitWindowSize(m_win_width, m_win_height);
//        glutCreateWindow(m_title.c_str());
    
		// 构造子系统
		g_p_openGL = new COpenGL(m_hdc, m_win_width, m_win_height);
		g_p_tex_mgr = new CTextureManager();
		g_p_surface = new CSurface();
		g_p_input = new CInput(_p_window);
		g_p_script = new CScript();
		//g_p_pen_mgr = new CPenManager();
		//g_p_music = new CMusic();
	}
	void CSystem::_release()
	{
		//ReleaseDC(m_hwnd, m_hdc);
		delete g_p_openGL;
		delete g_p_tex_mgr;
		delete g_p_surface;
		delete g_p_input;
		delete g_p_script;
		//delete g_p_pen_mgr;
		//delete g_p_music;
	}
	void CSystem::_err()
	{
//        unsigned int e = GetLastError();
//        printf("CSystem error %d\n", e);
//        PostQuitMessage(0);
	}
}

//////////////////////////////////////////////////////////////////////////
//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//	if (air::g_p_system != NULL)
//		return air::g_p_system->msg_proc(msg, wparam, lparam);
//	else
//		return DefWindowProc(hwnd, msg, wparam, lparam);
//}
