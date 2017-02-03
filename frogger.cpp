/* Game map by row:
0----grass and finish----
1--------logs------------
2--------logs------------
3--------logs------------
4--------logs------------
5--------grass-----------
6--------cars------------
7--------cars------------
8--------cars------------
9--------grass-----------
*/
#include <iostream>
#include <GLUT/glut.h>
#include <GLUT/glut.h>
#include <vector>
using namespace std;

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 400
#define LANE_HEIGHT 40
#define RECT_HEIGHT 30
#define JUMP_DIST 5
//#define DELAY_CNT 100000;

class Rect
{
public:
  // x, y of top left corner
  int x;
  int y;
  // for movement, not sizing
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
    return (this->x + this->width < rect.x || this->y + this->height < rect.y || rect.x + rect.width < this->x || rect.y + rect.height < this->y);
  }
};

//Globals
vector <Rect> cars;
vector <Rect> logs;
Rect frog;
int cnt = 0;
float w = 2.0/SCREEN_WIDTH;
float h = 2.0/SCREEN_HEIGHT;
float c = 1.0/255;
bool up_pressed, down_pressed, left_pressed, right_pressed = false;


void resetFrog(){
  // TODO: start frog at the bottom in the middle
  frog=Rect(SCREEN_WIDTH/2,SCREEN_HEIGHT - 50,0,0*c,255*c,0*c,3,3);
}


void init()
{
  // for row r of cars/logs
    // x = various
    // y = r * LANE_HEIGHT + (LANE_HEIGHT - RECT_HEIGHT) / 2



  Rect Car0=Rect(SCREEN_WIDTH/4,SCREEN_HEIGHT/4,5,244*c,208*c,63*c,4,RECT_HEIGHT);




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

  resetFrog();
}

void idlefunc() {
  cnt++;
  if (cnt == 1000) {
    cnt = 0;

    // move everything
    for(auto car : cars){
      car.x += car.dx;
    }

    for(auto car : logs){
      car.x += car.dx;
    }

    if (up_pressed){
      frog.y -= JUMP_DIST;
    }
    if (down_pressed){
      frog.y += JUMP_DIST;
    }
    if (left_pressed){
      frog.x -= JUMP_DIST;
    }
    if (right_pressed){
      frog.x += JUMP_DIST;
    }

    // TODO: check if frog made it across


    // check for collisions
    for(auto car : cars){
      if(frog.collidesWith(car)){
        // ded
        resetFrog();
      }
    }

    for(auto car : logs){
      if(frog.collidesWith(car)){
        // ded
        resetFrog();
      }
    }

    glutPostRedisplay();
  }
}

void fillBackground(){
  glClear(GL_COLOR_BUFFER_BIT);
  // eventually have a road texture, water texture, etc
   // grass on top
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
     glVertex3f(-1.0, 1.0, 0.0);
     glVertex3f(-1.0, 1-LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0,1-LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0, 1.0, 0.0);
   glEnd();

   //water
   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_POLYGON);
     glVertex3f(-1.0, 1-LANE_HEIGHT*h, 0.0);
     glVertex3f(-1.0, 1-5*LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0,1-5*LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0, 1-LANE_HEIGHT*h, 0.0);
   glEnd();

   //middle water
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
     glVertex3f(-1.0, 1-5*LANE_HEIGHT*h, 0.0);
     glVertex3f(-1.0, 1-6*LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0,1-6*LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0, 1-5*LANE_HEIGHT*h, 0.0);
   glEnd();

   //road lines
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
     glVertex3f(-1.0, 1.005-7*LANE_HEIGHT*h, 0.0);
     glVertex3f(-1.0, 0.995-7*LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0, 0.995-7*LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0, 1.005-7*LANE_HEIGHT*h, 0.0);
   glEnd();
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
     glVertex3f(-1.0, 1.005-8*LANE_HEIGHT*h, 0.0);
     glVertex3f(-1.0, 0.995-8*LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0, 0.995-8*LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0, 1.005-8*LANE_HEIGHT*h, 0.0);
   glEnd();
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
     glVertex3f(-1.0, 1.005-8*LANE_HEIGHT*h, 0.0);
     glVertex3f(-1.0, 0.995-8*LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0, 0.995-8*LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0, 1.005-8*LANE_HEIGHT*h, 0.0);
   glEnd();

   //grass on bottom
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
     glVertex3f(-1.0, -1.0, 0.0);
     glVertex3f(-1.0, -1+LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0,-1+LANE_HEIGHT*h, 0.0);
     glVertex3f(1.0, -1.0, 0.0);
   glEnd();   
}

void displayMe(void)
{
   fillBackground();
   
   for (auto car:cars) {
      glColor3f(car.r, car.g, car.b);
      glBegin(GL_POLYGON);
         glVertex2f(car.x*w, car.y*h);
         glVertex2f(car.x*w+car.width*w, car.y*h);
         glVertex2f(car.x*w+car.width*w, car.y*h+car.height*h);
         glVertex2f(car.x*w, car.y*h+car.height*h);
      glEnd();
   }

   for (auto alog:logs) {
      glColor3f(alog.r, alog.g, alog.b);
      glBegin(GL_POLYGON);
         glVertex2f(alog.x*w, alog.y*h);
         glVertex2f(alog.x*w+alog.width*w, alog.y*h);
         glVertex2f(alog.x*w+alog.width*w, alog.y*h+alog.height*h);
         glVertex2f(alog.x*w, alog.y*h+alog.height*h);
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