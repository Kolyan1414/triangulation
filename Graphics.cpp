#include "Graphics.h"


#define RAD_GRAD 57.32484076433121

double X=0, Y=0, Z=0;                                           //zero point
double dforward=0, dsideways=0;
double Anglefi=0, Angleksy=0;                                   //spherical coordinates (where the camera is looking)45
double dAnglefi=0, dAngleksy=0;
double zoom=1;

double Xo=0, Yo=0, Zo=0;

std::vector <Point*> *main_pointer;



void InitializationGLUT(int* argc, char** argv, int param, int flag, std::vector <Point*> *pointer){

    main_pointer=pointer;

    glutInit(argc, argv);

    switch (param){
        case LL:
            glutInitWindowSize(640, 480);                       //window size
            glutInitWindowPosition(300, 100);           //window position
            break;

        case LO:
            glutInitWindowSize(800, 600);                       //window size
            glutInitWindowPosition(300, 100);           //window position
            break;

        case LHD:
            glutInitWindowSize(1024, 720);                       //window size
            glutInitWindowPosition(0, 0);           //window position
            break;

        case LFHD:
            glutInitWindowSize(1920, 1080);
            glutInitWindowPosition(0, 0);
            break;

        case LFK:
            glutInitWindowSize(4096, 3072);
            glutInitWindowPosition(0, 0);
            break;

        default:
            glutInitWindowSize(640, 480);
            glutInitWindowPosition(300, 100);
            break;
    }

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_ACCUM);
    glutCreateWindow("TRIANGULATOR");               //title


    glEnable(GL_DEPTH_TEST);                        //DEPTH TEST
    glDepthFunc(GL_LEQUAL);                         //Set the type of depth-test
    glShadeModel(GL_SMOOTH);                        // Enable smooth shading

    glClearColor(0.53, 0.81, 0.98, 1);              //background color - sky blue

    glutDisplayFunc(display);                       //set rendering function
    glutReshapeFunc(changeSize);                    //set function to change size

    glutIdleFunc(display);

    glutKeyboardFunc(processNormalKeys);            //set fnc to press key x3
    glutSpecialFunc(pressSpecialKey);
	glutSpecialUpFunc(releaseSpecialKey);
    glutIgnoreKeyRepeat(1);                         //for smooth movement


    if(flag==FULL_SCREEN){
        glutFullScreen();
    }

    glutMainLoop();                                 //GLUT main loop
};

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                       //clr matrix

    Anglefi+=dAnglefi;
    Angleksy+=dAngleksy;

    glTranslated(0, 0, -10);
    glRotated(Anglefi, 0, 0, 1);
    glRotated(Angleksy, cos(Anglefi/RAD_GRAD), -sin(Anglefi/RAD_GRAD), 0);



    /*glBegin(GL_TRIANGLES);
        glColor3d(1, 0, 0);
        glVertex3d(-3, 2, 1);
        glColor3d(0, 1, 0);
        glVertex3d(-2, -1, 0);
        glColor3d(0, 1, 1);
        glVertex3d(-1, 0, -0.5);

        glColor3d(1, 0, 0);
        glVertex3d(-3, 2, 1);
        glColor3d(0, 1, 1);
        glVertex3d(-1, 0, -0.5);
        glColor3d(0, 0, 1);
        glVertex3d(1, 1, -1);

        glColor3d(0, 1, 1);
        glVertex3d(-1, 0, -0.5);
        glColor3d(0, 0, 1);
        glVertex3d(1, 1, -1);
        glColor3d(0, 1, 1);
        glVertex3d(2, -3, -0.5);


        glColor3d(0, 1, 1);
        glVertex3d(-1, 0, -0.5);
        glColor3d(1, 1, 0);
        glVertex3d(-1, -3, 0.5);
        glColor3d(0, 1, 0);
        glVertex3d(-2, -1, 0);

        glColor3d(0, 1, 1);
        glVertex3d(2, -3, -0.5);
        glColor3d(0, 1, 1);
        glVertex3d(-1, 0, -0.5);
        glColor3d(1, 1, 0);
        glVertex3d(-1, -3, 0.5);

        glColor3d(0, 0, 1);
        glVertex3d(1, 1, -1);
        glColor3d(0, 1, 1);
        glVertex3d(2, -3, -0.5);
        glColor3d(0, 1, 1);
        glVertex3d(4, 3, -0.5);

        glColor3d(0, 0, 1);
        glVertex3d(1, 1, -1);
        glColor3d(0, 1, 1);
        glVertex3d(4, 3, -0.5);
        glColor3d(1, 0, 0);
        glVertex3d(-3, 2, 1);
    glEnd(); */

    glColor3f(0,0,0);

    int max_vector_size=0, counter=0;
    max_vector_size=(*main_pointer).size();

    std::cout << max_vector_size;

    glPointSize(500);

    glBegin(GL_POINTS);
        for(counter=0;counter< 5;counter++)
            glVertex3d((*main_pointer)[counter]->x,
                        (*main_pointer)[counter]->y,
                        (*main_pointer)[counter]->z);
    glEnd();

	glFlush();
	glutSwapBuffers();
};

void changeSize(int w, int h){
	if (h==0 || w==0){
		h=1;
		w=1;
    }

	float ratio =  w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0, ratio, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
};

void processNormalKeys(unsigned char key, int x, int y) {

    switch (key) {
    case 27:
        exit(0);
        break;
    case 'w':
    case 'W':
    case '�':
    case '�':
        dforward=0.001;
        break;
    case 's':
    case 'S':
    case '�':
    case '�':
        dforward=-0.001;
        break;
    case '�':
    case '�':
    case 'd':
    case 'D':
        dsideways=0.001;
        break;
    case 'a':
    case 'A':
    case '�':
    case '�':
        dsideways=-0.001;
        break;

    case ' ':
        if(Anglefi==0 && Angleksy==0){
            Angleksy=-60;
            Anglefi=0;
        }else{
            Anglefi=0;
            Angleksy=0;
        }
        break;
    }
};

void pressSpecialKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT:
            dAnglefi=0.1;
            break;
		case GLUT_KEY_RIGHT:
            dAnglefi=-0.1;
            break;
		case GLUT_KEY_UP:
            dAngleksy=0.1;
            break;
		case GLUT_KEY_DOWN:
            dAngleksy=-0.1;
            break;
	}
};

void releaseSpecialKey(int key, int x, int y) {

	switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            dAnglefi=0.0;
            break;

        case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
			dAngleksy=0.0;
			break;
	}
};
