//
//  main.cpp
//  rover_domain
//
//  Created by ak on 10/11/18.
//  Copyright © 2018 ak. All rights reserved.
// https://www.desmos.com/calculator

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <cmath>
#include <math.h>
#include <random>
#include <assert.h>
#include <vector>
#include <cassert>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <map>


using namespace std;

struct Point {
   double x, y;
};

struct line {
   Point p1, p2;
};

bool onLine(line l1, Point p) {        //check whether p is on the line or not
   if(p.x <= max(l1.p1.x, l1.p2.x) && p.x <= min(l1.p1.x, l1.p2.x) &&
      (p.y <= max(l1.p1.y, l1.p2.y) && p.y <= min(l1.p1.y, l1.p2.y)))
         return true;

   return false;
}

int direction(Point a, Point b, Point c) {
   int val = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y);
   if (val == 0)
      return 0;           //colinear
   else if(val < 0)
      return 2;          //anti-clockwise direction
      return 1;          //clockwise direction
}

bool isIntersect(line l1, line l2) {
   //four direction for two lines and points of other line
   int dir1 = direction(l1.p1, l1.p2, l2.p1);
   int dir2 = direction(l1.p1, l1.p2, l2.p2);
   int dir3 = direction(l2.p1, l2.p2, l1.p1);
   int dir4 = direction(l2.p1, l2.p2, l1.p2);

   if(dir1 != dir2 && dir3 != dir4)
      return true;           //they are intersecting
   if(dir1==0 && onLine(l1, l2.p1))        //when p2 of line2 are on the line1
      return true;
   if(dir2==0 && onLine(l1, l2.p2))         //when p1 of line2 are on the line1
      return true;
   if(dir3==0 && onLine(l2, l1.p1))       //when p2 of line1 are on the line2
      return true;
   if(dir4==0 && onLine(l2, l1.p2)) //when p1 of line1 are on the line2
      return true;
   return false;
}

bool checkInside(Point poly[], int n, Point p) {
   if(n < 3)
      return false;                  //when polygon has less than 3 edge, it is not polygon
   line exline = {p, {9999, p.y}};   //create a point at infinity, y is same as point p
   int count = 0;
   int i = 0;
   do {
      line side = {poly[i], poly[(i+1)%n]};     //forming a line from two consecutive points of poly
      if(isIntersect(side, exline)) {          //if side is intersects exline
         if(direction(side.p1, p, side.p2) == 0)
            return onLine(side, p);
         count++;
      }
      i = (i+1)%n;
   } while(i != 0);
      return count&1;             //when count is odd
}

int main() {
   // line polygon = {{{0,0},{10,0}},{{10,0},{10,10}},{{10,10},{0,10}},{{0,10},{0,0}}};
   
   int n = 4;
   Point polygon[]= {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
   Point p = {5, 3};
      
   if(checkInside(polygon, n, p))
      cout << "Point is inside.";
   else
      cout << "Point is outside.";
    cout<<p.x<<endl;
}
/*

int main(int argc, const char * argv[]) {
    srand ( time(NULL) );
    //cout<<"Lets test it"<<endl;
    //run_simulation_function();
    double center_x = 30.0;
    double center_y = 30.0;
    double radius = 5.0;
    vector<double> x_coordinates;
    vector<double> y_coordinates;

    //First point 
    cout<<"Test"<<endl;
    double angle =0.0;
    x_coordinates.push_back(center_x + radius * sin(angle));
    y_coordinates.push_back(center_y + radius * cos(angle));
    
    angle = 60.0;
    x_coordinates.push_back(center_x + radius * sin(angle));
    y_coordinates.push_back(center_y + radius * cos(angle));

    angle = 185.0;
    x_coordinates.push_back(center_x + radius * sin(angle));
    y_coordinates.push_back(center_y + radius * cos(angle));
    cout<<cos(0)<<endl;
    for (int i = 0; i < x_coordinates.size(); i++)
    {
        cout<<x_coordinates.at(i)<<"\t"<<y_coordinates.at(i)<<endl;
    }
    
    if (90%10 == 0)
    {
        cout<<"Correct condition"<<endl;
    }else
    {
        cout<<"wrong condition"<<endl;
    }
    
    return 0;
}


*/