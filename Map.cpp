//
//  Map.cpp
//  MHA*
//
//  Created by Harsh Sharma on 05/05/19.
//  Copyright © 2019 Harsh Sharma. All rights reserved.
//

#include "Map.hpp"
#include <vector>
#include <iostream>
#include <tuple>
using namespace std;

Map::Map(tuple<int,int,double> robot_start_position,int user_map_width,int user_map_height,int user_connected_grid):
 robot_start_pos(robot_start_position), map_width(user_map_width),map_height(user_map_height),connected_grid(user_connected_grid)
{
    
}
Map::Map(tuple<int,int,double> robot_start_position,int user_map_width,int user_map_height):
Map(robot_start_position,user_map_width,user_map_height,8) {}

Map::Map(tuple<int,int,double> robot_start_position):
Map(robot_start_position,100,100,8) {}

Map::Map():
Map(make_tuple(0,0,0.0),100,100,8) {}

vector<vector<double> > Map::create_map()
{
    vector<vector<double> > map(map_height, vector<double> (map_width,1.0));
    return map;
}
tuple<int,int,double> Map::get_robot_start_pos()
{
    return robot_start_pos;
}
void Map::display_map(vector<vector<double> > map)
{
    for(auto i1 = map.begin(); i1 != map.end(); ++i1) // loops over the "external" vector
        for(auto i2 = i1->begin(); i2 != i1->end(); ++i2) // loops over the "internal" vectors
            cout << *i2;
        cout<<endl;
}
