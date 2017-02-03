#include <GLUT/glut.h>
#include <GLUT/glut.h>
#include <vector>
using namespace std;

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 400
#define DELAY 100000;

class Rect
{
public:
  int x;
  int y;
  int dx;
  float r, g, b;
  int width;
  int height;

  Rect(){}

  Rect(int xLocation, int yLocation, int dx, float r, float g, float b, int width, int height)
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

  bool collidesWith(Rect rect){

    return false;
  }
};

//Globals
vector <Rect> cars;
vector <Rect> logs;
Rect frog;
int count = 0;
float red = 0;
float w = 1.0/SCREEN_WIDTH;
float h = 1.0/SCREEN_HEIGHT;
float c = 1.0/<p></p>255;


void init()
{
   Rect Car0=Rect(SCREEN_WIDTH/4,SCREEN_HEIGHT/4,5,244*c,208*c,63*c,4,4);
   Rect Car1=Rect(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,8,155*c,89*c,182*c,4,4);

   cars.push_back(Car0);
   cars.push_back(Car1);

   Rect Log0=Rect(SCREEN_WIDTH/2,SCREEN_HEIGHT/4,5,255*c,248*c,220*c,10,3);
   Rect Log1=Rect(SCREEN_WIDTH*3/4,SCREEN_HEIGHT/4,5,255*c,248*c,220*c,10,3);
   Rect Log2=Rect(SCREEN_WIDTH/2,SCREEN_HEIGHT*3/4,5,255*c,248*c,220*c,10,3);

   Rect LogGoal0=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,0,255*c,255*c,255*c,4,4);
   Rect LogGoal1=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,0,255*c,255*c,255*c,4,4);
   Rect LogGoal2=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,0,255*c,255*c,255*c,4,4);

   logs.push_back(Log0);
   logs.push_back(Log1);
   logs.push_back(Log2);

   frog=Rect(SCREEN_WIDTH/2,SCREEN_HEIGHT - 50,0,0*c,255*c,0*c,3,3);
}

void idlefunc() {
  count++;
  if (count == DELAY) {
    count = 0;
    red = red + .01;

    for(auto car : cars){
      car.x += car.dx;
    }

    for(auto car : logs){
      car.x += car.dx;
    }



    glutPostRedisplay();
  }
}

void fillBackground(){
  glClear(GL_COLOR_BUFFER_BIT);
  // eventually have a road texture, water texture, etc
}
void displayMe(void)
{
   fillBackground();
   glColor3f(red, 0.0, 0.0);
   for (auto car:cars) {
      glBegin(GL_POLYGON);
         glVertex2f(car.x*w, car.y*h);
         glVertex2f(car.x*w+car.width*w, car.y*h);
         glVertex2f(car.x*w+car.width*w, car.y*h+car.height*h);
         glVertex2f(car.x*w, car.y*h+car.height*h);
      glEnd();
   }

   // always last
   glutSwapBuffers();
}

int main(int argc, char** argv)
{
    init();
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