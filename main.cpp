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
#include <queue>
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
//====================================================================================================================================================
stack<tuple<int,int> > get_path_from_start_to_goal(State *current_traversing_state_pointer, const vector<vector<State> > &my_map,const State start_state)
{
    stack<tuple<int,int> > path;

    while(!(*current_traversing_state_pointer==start_state))
    {
        cout<<"Current Traversing state is "<<*current_traversing_state_pointer<<endl;
        // cout<<*(current_traversing_state.parent_state)<<endl;
        path.push(make_tuple(get<0>(current_traversing_state_pointer->state),get<1>(current_traversing_state_pointer->state)));
        current_traversing_state_pointer = current_traversing_state_pointer->parent_state;
    }

    path.push(make_tuple(get<0>(start_state.state),get<1>(start_state.state)));
    return path;
}
//==============================================================================================================================================
void display_result(Map &init_map, queue<State> &path,const tuple<int,int> &start_position,const tuple<int,int> &goal_position)
{   vector<vector<string> > result_map(init_map.get_map_heigth(), vector<string>(init_map.get_map_width(),"."));

    while (!path.empty()) {
        auto present_state = path.front();
        //cout<<present_state<<endl;
        result_map[get<0>(present_state.state)][get<1>(present_state.state)] = "*";
        path.pop();
    }

    result_map[get<0>(start_position)][get<1>(start_position)] = "S";
    result_map[get<0>(goal_position)][get<1>(goal_position)] = "G";

    for(size_t i=0;i<init_map.get_map_heigth();i++)
    {
        for(size_t j=0;j<init_map.get_map_width();j++)
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
    Map init_map(make_tuple(0,0,0),make_tuple(5,9,0),10,10,8); //Handle exception of goal state being within map margin
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
    start_state->parent_state = nullptr;
    cout<<"++++++++++++++++++++++++++++++++++++++++++"<<endl;

    //init_map.display_map(my_map);

    set<State> open_list;
    set<State> closed_list;
    open_list.insert(my_map.at(get<0>(robot_start))[get<1>(robot_start)]);

    queue<State> q;

    bool destination_found = false;
    while(!open_list.empty())
    {
        auto next_state_to_expand = open_list.begin();

        q.push(*next_state_to_expand); //This is not the correct way to find the path. The correct way is by backtracking from the goal

        ///Print statements to validate parent and next state is getting assigned correctly
        // cout<<"Next state to expand is "<<*next_state_to_expand<<"\n";
        // if(next_state_to_expand->parent_state!=nullptr)
        //     { 
        //         cout<<"It's parent is "<<*next_state_to_expand->parent_state<<endl; 
        //         }
        
        if(next_state_to_expand->state == goal_state->state)
        {
            destination_found = true;
            break;
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
        // while (!q.empty())
        // {
        //     std::cout << ' ' << q.front();
        //     q.pop();
        // }
        cout<<endl;
        auto current_traversing_state_pointer = goal_state;
        // cout<<*current_traversing_state_pointer<<*(current_traversing_state_pointer->parent_state)<<endl;
        // stack<tuple<int,int> > path = get_path_from_start_to_goal(current_traversing_state_pointer, my_map, *start_state);
        const auto goal_position = make_tuple(get<0>(goal_state->state),get<1>(goal_state->state));
        const auto start_position = make_tuple(get<0>(start_state->state),get<1>(start_state->state));
        display_result(init_map,q,start_position,goal_position);  
        //init_map.display_map(my_map);
    }   
    return 0;
}


//Questions
//How to handle continious angles?
//How to handle 16 connected grid