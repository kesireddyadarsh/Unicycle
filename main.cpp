//
//  main.cpp
//  rover_domain
//
//  Created by ak on 10/11/18.
//  Copyright © 2018 ak. All rights reserved.
//

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
    
    return 0;
}


