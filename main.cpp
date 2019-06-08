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
#include <stack>
#include "Map.hpp"
#include "state.hpp"

//==============================================================================================================================================================
bool check_if_coordinate_is_valid(double map_width,double map_height,double row,double column)
{
    if(row>=0 && row<map_height && column>=0 && column<map_width)
    {
       return true;
    }
    else
    {
        return false;
    }  
}
//==============================================================================================================================================================
void add_relevant_states_to_open_list(const set<State> &closed_list,set<State> &open_list,vector<vector<State> > &my_map,State state_expanding, const tuple<int,int,double> &goal_state_tuple)
{
    const auto map_width = my_map[0].size();
    const auto map_height = my_map.size();
    for (int newX = -1; newX <= 1; newX++) 
    {
        for (int newY = -1; newY <= 1; newY++)
        {   
            if(check_if_coordinate_is_valid(map_width,map_width,get<0>(state_expanding.state) + newX,get<1>(state_expanding.state) + newY))
            {
                auto *successor_of_expanded_state = &my_map.at(get<0>(state_expanding.state) + newX)[get<1>(state_expanding.state) + newY];
                if(!closed_list.count(*(successor_of_expanded_state)))
                {
                    float gNew, hNew, fNew;
                    gNew = state_expanding.gcost + 1.0;
                    hNew = successor_of_expanded_state->get_heuristic(goal_state_tuple);
                    fNew = gNew + hNew;
                    if(successor_of_expanded_state->get_fcost()>fNew)
                    {
                        successor_of_expanded_state->gcost = gNew;
                        successor_of_expanded_state->hcost = hNew;
                        successor_of_expanded_state->fcost = fNew;
                        successor_of_expanded_state->parent_state = &state_expanding;
                        open_list.insert(*successor_of_expanded_state);
                    }

                    //Add the same from the blog. The cost of path from one state to the other has been assumed 1
                }
            }
        }
    }
}

stack<tuple<int,int> > get_path_from_start_to_goal(State &current_traversing_state, const vector<vector<State> > &my_map, State start_state)
{
    stack<tuple<int,int> > path;
    auto current_x = get<0>(current_traversing_state.state);
    auto current_y = get<1>(current_traversing_state.state);
    auto start_x = get<0>(start_state.state);
    auto start_y = get<1>(start_state.state);
    //while(current_x != start_x && current_y != start_y)
    while(!(current_traversing_state==start_state))
    {
        path.push(make_tuple(get<0>(current_traversing_state.state),get<0>(current_traversing_state.state)));
        current_traversing_state = *(current_traversing_state.parent_state);
    }

    path.push(make_tuple(get<0>(start_state.state),get<1>(start_state.state)));
    return path;
}
//==============================================================================================================================================
void display_result(Map &init_map, stack<tuple<int,int> > &path,const tuple<int,int> &start_position,const tuple<int,int> &goal_position)
{   vector<vector<string> > result_map(init_map.get_map_heigth(), vector<string>(init_map.get_map_width(),"."));

    while (!path.empty()) {
        tuple<int,int> top = path.top();
        result_map[get<0>(top)][get<1>(top)] = "*";
        path.pop();
    }

    result_map[get<0>(start_position)][get<1>(start_position)] = "S";
    result_map[get<0>(goal_position)][get<1>(goal_position)] = "G";

    for(size_t i=0;i<init_map.get_map_heigth();i++)
    {
        for(size_t j=0;i<init_map.get_map_width();j++)
        {
            cout<<result_map[i][j]<<"  ";
        }
        cout<<endl;
    }
}
//======================================================================================================================================
void print_set(const set<State> seto)
{
    for(auto x: seto)
    cout<<x<<endl;
}
//======================================================================================================================================
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
    // I don't think this (hcost and fcost) has to be zero as long as it has a finite value. it will have minimum fcost
    // start_state->parent_x = get<0>(start_state->state);
    // start_state->parent_y = get<1>(start_state->state);
    // start_state->parent_x = -2;
    // start_state->parent_y = -2;
    cout<<"++++++++++++++++++++++++++++++++++++++++++"<<endl;

    init_map.display_map(my_map);

    // my_map.at(get<0>(robot_start))[get<1>(robot_start)].parent_x = get<0>(robot_start);
    // my_map.at(get<0>(robot_start))[get<1>(robot_start)].parent_y = get<1>(robot_start);

    set<State> open_list;
    set<State> closed_list;
    open_list.insert(my_map.at(get<0>(robot_start))[get<1>(robot_start)]);

    bool destination_found = false;
    while(!open_list.empty() && !closed_list.count(*goal_state))
    {
        auto next_state_to_expand = open_list.begin();
        if(next_state_to_expand->state == goal_state->state)
        {
            destination_found = true;
        }
        closed_list.insert(*next_state_to_expand);
        add_relevant_states_to_open_list(closed_list,open_list,my_map,*next_state_to_expand,goal_state->state);
        // print_set(open_list);
        open_list.erase(next_state_to_expand);
    }

    if(!destination_found)
    {
        cout<<"Path to destination not found"<<endl;
    }
    else
    {
        cout<<"Destination found"<<endl;
        // State current_traversing_state = *goal_state;
        // stack<tuple<int,int> > path = get_path_from_start_to_goal(current_traversing_state, my_map, *start_state);
        // const auto goal_position = make_tuple(get<0>(goal_state->state),get<1>(goal_state->state));
        // const auto start_position = make_tuple(get<0>(start_state->state),get<1>(start_state->state));
        // display_result(init_map,path,start_position,goal_position);  
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