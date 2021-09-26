//
// Created by Zoelle Wong on 9/21/2021.
//
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

class Point {
private:// data members
double x, y;
public:// methods
Point( double in_x, double in_y){
x = in_x;
y = in_y;
};
int GetX(){return x;};
int GetY(){ return y;};

Point () {};// default constructor

Point scale(float f){
float newx = x*f, newy = y*f;
Point new_point(newx, newy);
return new_point;
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
float halfway(Point otherpoint){
float xdistance = 1/2*( otherpoint.x + x);
float ydistance = 1/2*( otherpoint.y + y);

//vector<float> coord_vec = {xdistance, ydistance};
return(xdistance);
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

class Rectangle{
private:
float w, h;
public:
Rectangle(float in_w, float in_h){
w = in_w;
h = in_h;
};

Rectangle() {}; // default constructor
float area(float w, float h){ return w*h;};
float rightedge(Point b1, float w, float h){ return h+ sqrtf(b1.GetX()*b1.GetX());};
float topedge(Point b1, float w, float h){return w + sqrtf(b1.GetY()*b1.GetY());};

};


// object.gett function

int main() {

Point mypoint (2., 2.);
GridPoint mydistance(2.,2.);
Point p(0.,0.);
Point q(0.,0.);

Rectangle myRectangle(2., 4.);
cout << "Area: " << myRectangle.area(2., 4.) << endl;
cout << "Right Edge: " << myRectangle.rightedge(mypoint, 2., 4.) << endl;
cout << "Top Edge: " << myRectangle.topedge(mypoint, 2., 4.) << endl;

/*cout << "Distance to origin: " << mypoint.distance_to_origin() << endl;
cout << "Angle from origin: " << mypoint.angle()<< endl;
cout << "Mahattan distance from origin: " << mydistance.mahattan_distance() << endl;
cout << "Distance from point p to q: " << p.distance(q) << endl;
cout << "Halfway point from p to q: " << p.halfway(q) << endl;
*/
return 0;
}
