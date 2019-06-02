//
//  Map.cpp
//  MHA*
//
//  Created by Harsh Sharma on 05/05/19.
//  Copyright © 2019 Harsh Sharma. All rights reserved.
//

#include "Map.hpp"
using namespace std;

#define THRESHOLD 10

Map::Map(tuple<int,int,double> robot_start_position,tuple<int,int,double> robot_goal_position,int user_map_width,int user_map_height,int user_connected_grid):
 robot_start_pos(robot_start_position), robot_goal_pos(robot_goal_position),map_width(user_map_width),map_height(user_map_height),connected_grid(user_connected_grid)
{
    
}
Map::Map(tuple<int,int,double> robot_start_position,tuple<int,int,double> robot_goal_position,int user_map_width,int user_map_height):
Map(robot_start_position,robot_goal_position,user_map_width,user_map_height,8) {}

Map::Map(tuple<int,int,double> robot_start_position,tuple<int,int,double> robot_goal_position):
Map(robot_start_position,robot_goal_position,100,100,8) {}

Map::Map():
Map(make_tuple(0,0,0.0),make_tuple(1,1,0.0),100,100,8) {}

vector<vector<State> > Map::create_map()
{
    vector< std::vector< State > > map( map_height, std::vector< State >( map_width) );
    int count_x {0};
    int count_y {0};
    for(auto i1 = map.begin(); i1 != map.end(); ++i1) // loops over the "external" vector
        {   count_y = 0;
            for(auto i2 = i1->begin(); i2 != i1->end(); ++i2) // loops over the "internal" vectors
                {   count_y ++;
                    i2->fcost = DBL_MAX;
                    i2->gcost = DBL_MAX;
                    i2->hcost = map_heuristic(count_x,count_y,get<0>(robot_goal_pos),get<1>(robot_goal_pos));
                    i2->state = make_tuple(count_x,count_y,0);
                    i2->parent_x = -1;
                    i2->parent_y = -1;
                }
        count_x++;
        }
    return map;
}


tuple<int,int,double> Map::get_robot_start_pos()
{
    return robot_start_pos;
}

tuple<int,int,double> Map::get_robot_goal_pos()
{
    return robot_goal_pos;
}


void Map::display_map(vector<vector<State> > map)
{
    for(auto i1 = map.begin(); i1 != map.end(); ++i1) // loops over the "external" vector
        {
          for(auto i2 = i1->begin(); i2 != i1->end(); ++i2) // loops over the "internal" vectors
        	{
                cout<<i2->fcost<<"\t";

        	}
          cout<<endl; 
        }
}

double Map::map_heuristic(const int x,const int y,const int x_g,const int y_g)   //Should be removed later.
{
    //Assumed Euclidian distance as of now
    return double(sqrt(pow((x-x_g),2) + pow((y-y_g),2)));
}
