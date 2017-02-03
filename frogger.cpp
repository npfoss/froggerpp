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
//#include <iostream>
#include <GLUT/glut.h>
#include <GLUT/glut.h>
#include <vector>
using namespace std;

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 400
#define LANE_HEIGHT 40
#define RECT_HEIGHT 30
//#define DELAY_CNT 100000;
#define JUMP_DIST 40

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
char key_press;
int ascii_value;
bool up_pressed, down_pressed, left_pressed, right_pressed = false;

void resetFrog(){
  // TODO: start frog at the bottom in the middle
  frog.y = SCREEN_HEIGHT - 5 - RECT_HEIGHT;
  frog.x = SCREEN_HEIGHT / 2 - RECT_HEIGHT / 2;
}

void init()
{
  // for row r of cars/logs
    // x = various
    // y = r * LANE_HEIGHT + (LANE_HEIGHT - RECT_HEIGHT) / 2



  Rect Car0=Rect(SCREEN_WIDTH-30,SCREEN_HEIGHT*8/10,-5,244*c,208*c,63*c,RECT_HEIGHT,RECT_HEIGHT);
  Rect Car1=Rect(0,SCREEN_HEIGHT*7/10,6,155*c,89*c,182*c,RECT_HEIGHT,RECT_HEIGHT);
  Rect Car2=Rect(SCREEN_WIDTH-30,SCREEN_HEIGHT*6/20,-9,155*c,89*c,182*c,RECT_HEIGHT,RECT_HEIGHT);

  cars.push_back(Car0);
  cars.push_back(Car1);
  cars.push_back(Car2);

  Rect Log0=Rect(SCREEN_WIDTH-30,SCREEN_HEIGHT*1/10,5,255*c,248*c,220*c,3*RECT_HEIGHT,RECT_HEIGHT);
  Rect Log1=Rect(0,SCREEN_HEIGHT*2/10,5,255*c,248*c,220*c,LANE_HEIGHT,2*RECT_HEIGHT);
  Rect Log2=Rect(SCREEN_WIDTH-30,SCREEN_HEIGHT*3/10,5,255*c,248*c,220*c,4*RECT_HEIGHT,RECT_HEIGHT);
  Rect Log3=Rect(0,SCREEN_HEIGHT*4/10,5,255*c,248*c,220*c,LANE_HEIGHT,3*RECT_HEIGHT);

  Rect LogGoal4=Rect(SCREEN_WIDTH*3/10,0,0,255*c,255*c,255*c,1.5*RECT_HEIGHT,RECT_HEIGHT);
  Rect LogGoal5=Rect(SCREEN_WIDTH/2,0,0,255*c,255*c,255*c,1.5*RECT_HEIGHT,RECT_HEIGHT);
  Rect LogGoal6=Rect(SCREEN_WIDTH*7/10,0,0,255*c,255*c,255*c,1.5*RECT_HEIGHT,RECT_HEIGHT);

  logs.push_back(Log0);
  logs.push_back(Log1);
  logs.push_back(Log2);
  logs.push_back(Log3);
  logs.push_back(LogGoal4);
  logs.push_back(LogGoal5);
  logs.push_back(LogGoal6);

  frog = Rect(0, 0, 0, 0, 255, 0, RECT_HEIGHT, RECT_HEIGHT);

  resetFrog();
}

void keyfunc(unsigned char key,int xscr,int yscr) {
   switch(key){
      case 'w':
         up_pressed =  true;
         break;
      case 's':
         down_pressed =  true;
         break;
      case 'a':
        left_pressed = true;
        break;
      case 'd':
        right_pressed = true;
        break;
   }
}

void keyupfunc(unsigned char key,int xscr,int yscr) {
   switch(key){
      case 'w':
         up_pressed =  false;
         break;
      case 's':
         down_pressed = false;
         break;
      case 'a':
        left_pressed = false;
        break;
      case 'd':
        right_pressed = false;
        break;
   }
}

bool frogOnLogs(){
  for(auto car : logs){
    if(frog.collidesWith(car)){
      return true;
    }
  }
  return false;
}

void idlefunc() {
  cnt++;
  if (cnt == 10000) {
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

    if (frog.y<LANE_HEIGHT)
    { 
      for (int n=0;n<logs.size();n++)
    {
      if (frog.collidesWith(logs[n]))
     {
        logs[n].r=0;
        logs[n].g=255;
        logs[n].b=0;
        resetFrog();
     }
    }
    }



    // check if frog dies
    if(frog.x > 5*LANE_HEIGHT){
      // watch out for cars
      for(auto car : cars){
        if(frog.collidesWith(car)){
          // ded
          resetFrog();
        }
      }
    } else {
      // make sure on logs
      if(!frogOnLogs()){
        // ded
        resetFrog();
      }
    }
    for (int n=0;n<cars.size();n++)
    {
      if (cars[n].dx<0&&cars[n].x<-cars[n].width)
      {
        cars[n].x=SCREEN_WIDTH;
      }
      else if (cars[n].dx>0&&cars[n].x>=SCREEN_WIDTH)
      {
        cars[n].x=-cars[n].width;
      }
    }


    glutPostRedisplay();
  }
}

void fillBackground(){
  glClear(GL_COLOR_BUFFER_BIT);
  // eventually have a road texture, water texture, etc
   // grass on top
   glColor3f(0.0, 153*c, 0.0);
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

   //middle grass
   glColor3f(0.0, 153*c, 0.0);
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
   glColor3f(0.0, 153*c, 0.0);
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
         glVertex2f(car.x*w-1, 1-car.y*h);
         glVertex2f(car.x*w-1+car.width*w, 1-car.y*h);
         glVertex2f(car.x*w-1+car.width*w, 1-car.y*h+car.height*h);
         glVertex2f(car.x*w-1, 1-car.y*h+car.height*h);
      glEnd();
   }

   for (auto alog:logs) {
      glColor3f(alog.r, alog.g, alog.b);
      glBegin(GL_POLYGON);
         glVertex2f(alog.x*w-1, 1-alog.y*h);
         glVertex2f(alog.x*w-1+alog.width*w, 1-alog.y*h);
         glVertex2f(alog.x*w-1+alog.width*w, 1-alog.y*h+alog.height*h);
         glVertex2f(alog.x*w-1, 1-alog.y*h+alog.height*h);
      glEnd();
   }

   glColor3f(frog.r, frog.g, frog.b);
   glBegin(GL_POLYGON);
      glVertex2f(frog.x*w-1, 1-frog.y*h);
      glVertex2f(frog.x*w-1+frog.width*w, 1-frog.y*h);
      glVertex2f(frog.x*w-1+frog.width*w, 1-frog.y*h+frog.height*h);
      glVertex2f(frog.x*w-1, 1-frog.y*h+frog.height*h);
   glEnd();   

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
    glutKeyboardFunc(keyfunc);
    glutKeyboardUpFunc(keyupfunc);
    glutMainLoop();
    return 0;
}