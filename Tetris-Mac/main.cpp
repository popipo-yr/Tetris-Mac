//
//  main.m
//  Tetris-Mac
//
//  Created by mac on 14-4-19.
//  Copyright (c) 2014年 mac. All rights reserved.
//

//#import <Cocoa/Cocoa.h>

#include <GLUT/GLUT.h>

#include "air/air.h"
#include <stdio.h>
#include <cstdlib>
#include <math.h>
using namespace air;
CImageFont g_img_font1;
CImageFont g_img_font2;
void init()
{
	//srand(GetTickCount());
	//g_p_tex_mgr->load_from_config("res/tetris/texture.txt");
	//g_p_pen_mgr->create_from_config("res/tetris/pen.txt");
	//g_p_music->load_from_config("res/tetris/music.txt");
	//g_img_font1.create("font1");
	//g_img_font2.create("font2");
	g_p_script->load("res/tetris/logic.lua");
	g_p_script->call("main_init");
}
void frame()
{
	g_p_script->call("main_update");
}
void draw()
{
	//string s = "x:" + tostr(g_p_input->get_mouse_x()) + " y:" + tostr(g_p_input->get_mouse_y());
    //g_p_pen_mgr->print("3", 100.0f, 400.0f, color(0,255,0), s);
	g_p_script->call("main_draw");
	//g_img_font2.print(200, 410, "QQDY");
	//g_img_font1.print(55, 435, "TETRIS");
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void loop(int x){

    
    g_p_system->loop();
    glutTimerFunc(50, loop , 1);
}

void SetupRc()
{
    glClearColor(0.3f,0.0f,0.0f,0.1f);
}


int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	g_p_system = new CSystem(320, 480, "AirGE by qq_d_y --- tetris");
	g_p_system->set_callback(CSystem::INIT, init);
	g_p_system->set_callback(CSystem::DRAW, draw);
	g_p_system->set_callback(CSystem::FRAME, frame);
	g_p_system->run();
    
    glutDisplayFunc(display);
    glutTimerFunc(1, loop , 1);
    
    SetupRc();
    glutMainLoop();
	return 0;
}



//void display()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_POLYGON);
//    glVertex2f(-0.5, -0.5);
//    glVertex2f(-0.5, 0.5);
//    glVertex2f(0.5, 0.5);
//    glVertex2f(0.5, -0.5);
//	glEnd();
//	glFlush();
//}
//
//void TIMER(int x)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_POLYGON);
//    glVertex2f(-0.5, -0.5);
//    glVertex2f(-0.5, 0.5);
//    glVertex2f(0.5, 0.5);
//    glVertex2f(0.5, -0.5);
//	glEnd();
//	glFlush();
//    
//    glutTimerFunc(2*1000, TIMER , 1);
//}
//
//
//int main(int argc, char ** argv)
//{
//	glutInit(&argc, argv);
//	glutCreateWindow("Xcode Glut Demo");
//    
//    glutTimerFunc(6*1000, TIMER , 1);
//    glutDisplayFunc(display);
//    
//    glutMainLoop();
//}

