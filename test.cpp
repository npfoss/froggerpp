// #include <iostream>
// //#include <stdlib.h>
// #include <GLUT/glut.h>
// #include <string>
// using namespace std;

// unsigned int window_x = 800;
// unsigned int window_y = 600;

// unsigned int window_start_x = 200;
// unsigned int window_start_y = 100;

// string window_name = "My First OpenGL Window";

// int main(int argc,char* argv[]) {
// 	//give glut command line args (such as X window, etc)
//    glutInit(&argc,argv);

//    cout << "help1" << endl;
//    //how should we accept input data
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    cout << "whyyyy" <<endl;

//    //make window initial size
//    glutInitWindowSize(window_x, window_y);
//    cout << "fml" << endl;

//    //top left window screen position
//    glutInitWindowPosition(window_start_x, window_start_y);
//    cout << "curse seg faults" << endl;

//    //when you start drawing, what should the background be
//    // r g b alpha (0 is opaque, 1 is clear)
//    glClearColor(255,255,255,0);
//    cout << "grrr" << endl;

//    //don't worry about this
//    glShadeModel(GL_SMOOTH);

//    //flush_size();
// }
#include <GLUT/glut.h>

int count = 0;
float red = 0;
void idlefunc() {
	count++;
	if (count == 1000) {
		//if (abs(red-1))	
			red = red + .01;
			count = 0;
		glutPostRedisplay();
	}
}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(red, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world :D");
    glutDisplayFunc(displayMe);
    glutIdleFunc(idlefunc);
    glutMainLoop();
    return 0;
}