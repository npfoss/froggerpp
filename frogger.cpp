#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 400

class Rect
{
public:
  int xLocation;
  int yLocation;
  int dx;
  int r, g, b;
  int width;
  int height;

  Rect(xLocation,yLocation,dx,r,g,b,width,height)
  {
    this->xLocation=xLocation;
    this->yLocation=yLocation;
    this->dx=dx;
    this->r=r;
    this->g=g;
    this->b=b;
    this->width=width;
    this->height=height;
  }

};

void init(vector <Rect> Cars, vector <Rect> Logs,vector <Rect> Frogs)
{
    Rect Car0=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,5,244,208,63,4,4);
    Rect Car1=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,8,155,89,182,4,4);

    Cars.push_back(Car0);
    Cars.push_back(Car1);

    Rect Log0=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,5,255,248,220,10,3);
    Rect Log1=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,5,255,248,220,10,3);
    Rect Log2=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,5,255,248,220,10,3);

    Rect LogGoal0=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,0,255,255,255,4,4);
    Rect LogGoal1=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,0,255,255,255,4,4);
    Rect LogGoal2=Rect(SCREEN_WIDTH,SCREEN_HEIGHT,0,255,255,255,4,4);

    Logs.push_back(Log0);
    Logs.push_back(Log1);
    Logs.push_back(Log2);

    Rect Frog=Rect(SCREEN_WIDTH,/*lower portion of screen height*/,0,0,255,0,3,3);

    Frogs.push_back(Frog);

}

int main()
{
 return 0;
}