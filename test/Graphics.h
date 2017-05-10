#pragma once


#include "GL/glut.h"
#include <cmath>
#include "Point/point.h"
#include <Vector>


#define LL 0           //640*480
#define LO 1           //800*600
#define LHD 2          //HD
#define LFHD 3         //FullHD
#define LFK 4          //4K
#define FULL_SCREEN 1
#define NO_FULL_SCREEN 0


void display();                                      //funct to render image
void changeSize(int, int);                           //funct to set projection matrix (when user changed size of the window)
void processNormalKeys(unsigned char, int, int);     //processing of clicks x3
void pressSpecialKey(int , int, int);
void releaseSpecialKey(int , int, int);
void InitializationGLUT(int *, char **, int, int, std::vector <Point*> *);        //fnc to init window and draw
/*1st is pointer to argc, 2nd - char** argv (param to main)
3d is window size in pixels and the last one is flag full_screen

/*кодеры, после InitializationGLUT прога ввы=аливается в бесконечный цикл =>
=> это дерьмо нужно делать либо в отдельном процессе, либо в нити*/
