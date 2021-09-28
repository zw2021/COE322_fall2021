//
// Created by Zoelle Wong on 9/23/2021.
//

#include <iostream>
#include <vector>
using namespace std;

class Point{
private:
    float x, y;
public:
    Point(float xx, float yy )
    : x(xx), y(yy) {};
    float xcoord(){ return x; }
    float ycoord(){ return y; }
};

class Rectangle{
private:
    Point bottomleft; float width, height;
public:
    Rectangle(Point bbl, float ww, float hh)
    : bottomleft(bbl), width(ww), height(hh) {};
    // how to use : notations for
    // colon member-name ( init - data )
    // optionally: comma and more of those and then end with {};
    float right_edge_x(){ return bottomleft.xcoord() + width;}
    float area(){return width*height;}

    Rectangle(Point bbl, Point ttr)
        // you can put expressions in the initializer!
        : bottomleft(bbl),
        width(ttr.xcoord() - bbl.xcoord()),
        height(ttr.ycoord() - bbl.ycoord()) {};
        float area_from_coord(){ return width*height;}
};

class Square : public Rectangle {
    private:
    public:

        Square(Point bbl, float sidelength) : Rectangle(bbl,sidelength,sidelength) {}
        
class Square : public Rectangle{ // derived class
public:
    Square(Point bottomleft,float w, float h): Rectangle(bottomleft, w,h) {
        if (h!=h){cout << "This isn't a square!!!" << endl;};
    };
};

// class General{ // base class
// public:
//     General( double x, double y) {};
// };
// class Special : public General {
//     // calls the base class ...
// };

/*
 * Set Theory: If an object is in A and in B, then A is a subset of C
 * Derived classes inherit data from the class it's in
 * "Base Class" >> "Sub/ Derived Class"
 *      Base class - protected: "private to the outside world, but public to the derived classes"
 * Derived Method can have a method that's not in the base class
 * "inheritance is the evil from all base case" lol
 *
 * HOMEWORK
 *      exercise 10
 * */
int main() {
    Point oneone(1.,1.);
    Point twothree(2,3);
    Rectangle portrait(oneone,2.5,4.);
    cout << "portrait has area " << portrait.area() << endl;
    return 0;
}