//
//  Map.hpp
//  MHA*
//
//  Created by Harsh Sharma on 05/05/19.
//  Copyright © 2019 Harsh Sharma. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <vector>
#include <tuple>
#include "state.hpp"
#include <iostream>
#include <cfloat>
#include <cmath>


using namespace std;

class Map
{
    
private:
    tuple<int,int,double> robot_start_pos;
    tuple<int,int,double> robot_goal_pos;
    const int map_width;
    const int map_height;
    const int connected_grid;
    
public:
    Map(tuple<int,int,double> robot_start_position,tuple<int,int,double> robot_goal_position,int user_map_width,int user_map_height,int user_connected_grid);
    Map(tuple<int,int,double> robot_start_position,tuple<int,int,double> robot_goal_position,int user_map_width,int user_map_height);
    Map(tuple<int,int,double> robot_start_position,tuple<int,int,double> robot_goal_position);
    Map();
    
    vector<vector<State> > create_map();
    tuple<int,int,double> get_robot_start_pos();
    tuple<int,int,double> get_robot_goal_pos();
    int get_map_heigth();
    int get_map_width();
    void display_map(vector<vector<State> > map); //Display map of fcosts
    double map_heuristic(const int x,const int y,const int x_g,const int y_g); 
    friend class State;
    
};

#endif /* Map_hpp */
