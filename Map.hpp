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


using namespace std;

class Map
{
    
private:
    tuple<int,int,double> robot_start_pos;
    const int map_width;
    const int map_height;
    const int connected_grid;
    
public:
    Map(tuple<int,int,double> robot_start_position,int user_map_width,int user_map_height,int user_connected_grid);
    Map(tuple<int,int,double> robot_start_position,int user_map_width,int user_map_height);
    Map(tuple<int,int,double> robot_start_position);
    Map();
    
    vector<vector<double> > create_map();
    tuple<int,int,double> get_robot_start_pos();
    void display_map(vector<vector<double> > map);
    
};

#endif /* Map_hpp */
