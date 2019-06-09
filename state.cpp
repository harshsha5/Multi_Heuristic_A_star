//
//  state.cpp
//  MHA*
//
//  Created by Harsh Sharma on 05/05/19.
//  Copyright © 2019 Harsh Sharma. All rights reserved.
//

#include "state.hpp"

using namespace std;

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

