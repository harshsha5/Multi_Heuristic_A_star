//
//  Map.hpp
//  MHA*
//
//  Created by Harsh Sharma on 05/05/19.
//  Copyright © 2019 Harsh Sharma. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <stdio.h>
#include <vector>
#include <tuple>

using namespace std;


class State
{
    //Can be modelled as a struct
    public:                                 //Should ideally be private
    tuple<int,int,double> state;
    float fcost;
    float gcost;
    float hcost;
    int parent_x;
    int parent_y;
    tuple<int,int,double> parent_state;   

    public:
    bool operator < (const State& lhs);
    bool operator == (const State& lhs);

    //bool check_if_state_valid(const Map &my_map) const;
    bool check_if_state_valid(const Map &my_map) const;

};

inline bool State::operator < (const State& lhs)
{//We need to overload "<" to put our struct into a set
    return fcost < lhs.fcost;
}

inline bool State::operator == (const State& lhs)
{//We need to overload "==" to see if configuration matches goal configuration
    return state == lhs.state;
}

#endif /* State_hpp */
