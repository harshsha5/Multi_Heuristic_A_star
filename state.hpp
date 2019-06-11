//
//  Map.hpp
//  MHA*
//
//  Created by Harsh Sharma on 05/05/19.
//  Copyright © 2019 Harsh Sharma. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <cmath>

using namespace std;

enum heuristic { 
    EUCLIDIAN,                              //signifies closed list
    BRAY_CURTIS,
    MANHATTAN, 
    Count
    };


class State
{
    //Can be modelled as a struct
    public:                                 //Should ideally be private================
    tuple<int,int,double> state;
    float fcost;
    float gcost;
    float hcost;
    State *parent_state;
    //tuple<int,int,double> parent_state;   //===========================

    public:
    float get_fcost();
    double get_heuristic(const tuple<int,int,double> goal_state_tuple) const;
    void calculate_heuristic(const heuristic heuristic,const tuple<int,int,double> goal_state_tuple);
    void calculate_fcost();
    bool operator < (const State& lhs) const;
    bool operator == (const State& lhs);
    //~State();
    friend ostream &operator<<( ostream &output, const State &S )
    { 
    const auto x = get<0>(S.state);
    const auto y = get<1>(S.state);
    output << "(" << x << "," << y << ")";
    return output;            
    }

//     State::State();

//     State::State(tuple<int,int,double> state, float fcost, float gcost, float hcost, State *parent_state);

//     // Copy constructor
//     State::State(const State& source)
//     {
//         // because m_length is not a pointer, we can shallow copy it
//         state = source.state;
//         fcost = source.fcost;
//         gcost = source.gcost;
//         hcost = source.hcost;

//         // m_data is a pointer, so we need to deep copy it if it is non-null
//         if (source.parent_state)
//         {
//             // allocate memory for our copy
//             parent_state = new State[*source.parent_state];
//         }
//         else
//             parent_state = nullptr;
//     }

//     // Assignment operator
//     State& State::operator=(const State & source)
//     {
//         // check for self-assignment
//         if (this == &source)
//             return *this;
    
//         // first we need to deallocate any value that this string is holding!
//         delete[] parent_state;
    
//         // because m_length is not a pointer, we can shallow copy it
//         state = source.state;
//         fcost = source.fcost;
//         gcost = source.gcost;
//         hcost = source.hcost;
    
//         // m_data is a pointer, so we need to deep copy it if it is non-null
//         if (source.parent_state)
//         {
//             // allocate memory for our copy
//             parent_state = new State[*source.parent_state];
//         }
//         else
//             parent_state = nullptr;
    
    
//         return *this;
//         }

};

inline bool State::operator < (const State& lhs) const 
{//We need to overload "<" to put our struct into a set
    return fcost < lhs.fcost;
}

inline bool State::operator == (const State& lhs)
{//We need to overload "==" to see if configuration matches goal configuration
    return state == lhs.state;
}

// State::State():State(make_tuple(0,0,0.),-1,-1,-1,nullptr) {};

// State::State(tuple<int,int,double> state, float fcost, float gcost, float hcost, State *parent_state):
// state(state),fcost(fcost),gcost(gcost),hcost(hcost),
// {

// }

// State::~State()
// {
//     delete []parent_state;
// }

#endif /* State_hpp */
