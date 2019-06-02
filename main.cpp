//
//  main.cpp
//  MHA*
//
//  Created by Harsh Sharma on 01/05/19.
//  Copyright © 2019 Harsh Sharma. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <set>
#include "Map.hpp"
#include "state.hpp"

void add_relevant_states_to_open_list(set<State> &closed_list,set<State> &open_list,vector<vector<State> > &my_map,const State state_expanding, const tuple<int,int,double> &goal_state_tuple)
{
    for (int newX = -1; newX <= 1; newX++) 
    {
        for (int newY = -1; newY <= 1; newY++)
        {
            State *successor_of_expanded_state = &(my_map.at(get<0>(state_expanding.state) + newX)[get<1>(state_expanding.state) + newY]);
            if(successor_of_expanded_state->check_if_state_valid(my_map) && !closed_list.count(*(successor_of_expanded_state)))
            {
                float gNew, hNew, fNew;
                gNew = successor_of_expanded_state->gcost + 1.0;
                hNew = successor_of_expanded_state->get_heuristic(goal_state_tuple);
                fNew = gNew + hNew;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    Map init_map(make_tuple(0,0,0),make_tuple(9,9,0),10,10,8);
    vector<vector<State> > my_map = init_map.create_map();
    init_map.display_map(my_map);
    
    tuple<int,int,double> robot_start = init_map.get_robot_start_pos();
    tuple<int,int,double> robot_goal = init_map.get_robot_goal_pos();
    //Initialize the start state with appropriate costs and parents

    State *start_state = &my_map.at(get<0>(robot_start))[get<1>(robot_start)];
    State *goal_state = &my_map.at(get<0>(robot_goal))[get<1>(robot_goal)];
    start_state->gcost = 0;
    start_state->hcost = 0;
    start_state->fcost = 0;
    // I don't think this has to be zero as long as it has a finite value. it will have minimum fcost
    start_state->parent_x = get<0>(start_state->state);
    start_state->parent_y = get<1>(start_state->state);
    cout<<"========================================================================================="<<endl;

    init_map.display_map(my_map);

    my_map.at(get<0>(robot_start))[get<1>(robot_start)].parent_x = get<0>(robot_start);
    my_map.at(get<0>(robot_start))[get<1>(robot_start)].parent_y = get<1>(robot_start);

    set<State> open_list;
    set<State> closed_list;
    open_list.insert(my_map.at(get<0>(robot_start))[get<1>(robot_start)]);


    while(!open_list.empty() && !closed_list.count(*goal_state))
    {
        auto next_state_to_expand = open_list.begin();
        closed_list.insert(*next_state_to_expand);
        add_relevant_states_to_open_list(closed_list,open_list,my_map,*next_state_to_expand,goal_state->state);
        open_list.erase(next_state_to_expand);

    }




    //Initialze the start position's gcost,fcost,hcost to zero (Done)
    //Define a function is_valid to check if a state is valid or not (Done)
    //Check which state to expand from the open list. Add it to closed list after expanding
    //Check all its nearby neighbours depending on the grid-connectedness 
    //See if the new_fcost is lower than the existing. If yes, update the costs and parents. Add state to open set/list
    
    return 0;
}


//Questions
//How to handle continious angles?
//How to handle 16 connected grid