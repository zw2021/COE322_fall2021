#include<iostream>
#include<cmath>
#include "point.cpp"
using namespace std;

class Rectangle {
    private:

    Point bottom_left;
    float width;
    float height;

    public:

    Rectangle(Point bl, float w, float h) {
        bottom_left = bl;
        width = w;
        height = h;
    }
    Rectangle(Point bl, Point tr) {
        bottom_left = bl;
        width = tr.getX() - bl.getX();
        height = tr.getY() - bl.getY();
    }
    float area() {
        return abs(width)*abs(height);
    }
    float rightedge() {
        return height;
    }
    float topedge() {
        return width;
    }

};

int main() {
    Point bl(2,2);
    float w = 3;
    float h = 4;
    Rectangle R(bl,w,h);
    cout << R.area() << endl;
}