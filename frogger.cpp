#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 400
#include <GLUT/glut.h>

//Globals
vector <Rect> Cars;
vector <Rect> Logs;
Rect Frog;
int count = 0;
float red = 0;

class Rect
{
public:
  int x;
  int y;
  int dx;
  int r, g, b;
  int width;
  int height;

  Rect(xLocation,yLocation,dx,r,g,b,width,height)
  {
    this->x=xLocation;
    this->y=yLocation;
    this->dx=dx;
    this->r=r;
    this->g=g;
    this->b=b;
    this->width=width;
    this->height=height;
  }

};

void init()
{
   Rect Car0=Rect(SCREEN_WIDTH/4,SCREEN_HEIGHT/4,5,244,208,63,4,4);
   Rect Car1=Rect(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,8,155,89,182,4,4);

   Cars.push_back(Car0);
   Cars.push_back(Car1);

   Rect Log0=Rect(SCREEN_WIDTH/2,SCREEN_HEIGHT/4,5,255,248,220,10,3);
   Rect Log1=Rect(SCREEN_WIDTH*3/4,SCREEN_HEIGHT/4,5,255,248,220,10,3);
   Rect Log2=Rect(SCREEN_WIDTH/2,SCREEN_HEIGHT*3/4,5,255,248,220,10,3);

   Rect LogGoal0=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,0,255,255,255,4,4);
   Rect LogGoal1=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,0,255,255,255,4,4);
   Rect LogGoal2=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,0,255,255,255,4,4);

   Logs.push_back(Log0);
   Logs.push_back(Log1);
   Logs.push_back(Log2);

   Frog=Rect(SCREEN_WIDTH/2,SCREEN_HEIGHT - 50,0,0,255,0,3,3);
}


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
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Frogger :D");
    glutDisplayFunc(displayMe);
    glutIdleFunc(idlefunc);
    glutMainLoop();
    return 0;
}