#include<iostream>
#include<cmath>
using namespace std;

class Point {
  private:// data members
    double x, y;
  public:// methods
    Point() {
      x = 0;
      y = 0;
    }
    Point( double in_x, double in_y){
      x = in_x; 
      y = in_y;
    };
  double distance_to_origin(){
      return sqrt(x*x + y*y);
  };
  double angle(){
      return atan2(y,x)*(180/3.14);
  };
  float distance(Point otherpoint){
      int xdistance = otherpoint.x - x;
      int ydistance = otherpoint.y - y;

      return sqrt((xdistance*xdistance) + (ydistance*ydistance));
  };
  Point halfway(Point q) {
    double xp = (x+q.x)/2;
    double yp = (y+q.y)/2;
    return Point(xp,yp);
  }
  double getX() {
    return x;
  }
  double getY() {
    return y;
  }
};

class GridPoint {
  private:
    double x, y;
  public:
      GridPoint( double in_x, double in_y){
       x = in_x; 
       y = in_y;
      };
   double  mahattan_distance(){
      return (sqrt(x*x) + sqrt(y*y));
  };

};
// int main() {

//   Point mypoint (2., 2.);
//   GridPoint mydistance(2.,2.);
//   Point p(3.,4.);
//   Point q(0.,0);

//   //cout << "Distance to origin: " << mypoint.distance_to_origin() << endl;
//   //cout << "Angle from origin: " << mypoint.angle()<< endl;
//   //cout << "Mahattan distance from origin: " << mydistance.mahattan_distance() << endl;
//   //cout << "Distance from point p to q: " << p.distance(q) << endl;
//   Point h = p.halfway(q);
//   cout << "X = " << h.getX() << ", Y = " << h.getY() << endl;
//   return 0;
// }
