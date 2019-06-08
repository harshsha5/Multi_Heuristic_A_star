//
//  state.cpp
//  MHA*
//
//  Created by Harsh Sharma on 05/05/19.
//  Copyright © 2019 Harsh Sharma. All rights reserved.
//

#include "state.hpp"

using namespace std;

/// Check if the state is within the map boundary
///@input Takes the map as the input
///@return True if the state is valid else false

// bool State::check_if_state_valid(const int map_width,const int map_height) const
// {
//     if(get<0>(state)>=0 && get<1>(state)>=0 && get<0>(state)<map_width && get<1>(state)<map_height)
//     {
//         return true;
//     }
    
//     return false; 
// }

float State::get_fcost()
{
    fcost = gcost + hcost;
    return fcost;
}

double State::get_heuristic(tuple<int,int,double> goal_state_tuple) const
{
    //Assumed Euclidian distance as of now
    float x_g = get<0>(goal_state_tuple);
    float y_g = get<1>(goal_state_tuple);

    return double(sqrt(pow((get<0>(state)-x_g),2) + pow((get<1>(state)-y_g),2)));
}


// bool State::operator < (const State& lhs)
// {//We need to overload "<" to put our struct into a set
//     return fcost < lhs.fcost;
// }