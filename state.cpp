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

bool State::check_if_state_valid(const Map &my_map) const
{
    if(get<0>(state)>0 && get<1>(state)>0 && get<0>(state)<my_map.map_width && get<1>(state)<my_map.map_height)
    {
        return true;
    }
    
    return false; 
}


// bool State::operator < (const State& lhs)
// {//We need to overload "<" to put our struct into a set
//     return fcost < lhs.fcost;
// }