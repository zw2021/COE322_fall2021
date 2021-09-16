#include<iostream>
#include<cmath>
using namespace std;

class Point {
  private:// data members
    double x, y;
  public:// methods
    Point( double in_x, double in_y){
      x = in_x; 
      y = in_y;
    };
  double distance_to_origin(){
      return sqrt(x*x + y*y);
  };
  double angle(){
      return atan2(y,x)*(180/M_PI);
  };
  float distance(Point otherpoint){
      int xdistance = otherpoint.x - x;
      int ydistance = otherpoint.y - y;

      return sqrt((xdistance*xdistance) + (ydistance*ydistance));
  };
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
int main() {

  Point mypoint (2., 2.);
  GridPoint mydistance(2.,2.);
  Point p(3.,4.);
  Point q(0.,0);

  cout << "Distance to origin: " << mypoint.distance_to_origin() << endl;
  cout << "Angle from origin: " << mypoint.angle()<< endl;
  cout << "Mahattan distance from origin: " << mydistance.mahattan_distance() << endl;
  cout << "Distance from point p to q: " << p.distance(q) << endl;
  return 0;
}
