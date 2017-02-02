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