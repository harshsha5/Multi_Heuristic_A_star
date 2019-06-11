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
///======================================================================================================================================
void expand(State &s,
            const size_t &i,
            const int &n,vector<vector<State> > &my_map,
            vector<vector<State> > &my_map_anchor,
            vector< set<State> > &open_list,
            set<State> &open_anchor_list,
            set<State> &closed_list,
            set<State> &closed_anchor_list,
            const tuple<int,int,double> &robot_goal 
            )
{
    for(auto x:open_list)
    {
        if(x.find(s) != x.end())
            x.erase(s);
    }

    const auto map_width = my_map[0].size();
    const auto map_height = my_map.size();
    for (int newX = -1; newX <= 1; newX++) 
    {
        for (int newY = -1; newY <= 1; newY++)
        {   
            if(check_if_coordinate_is_valid(map_width,map_width,get<0>(s.state) + newX,get<1>(s.state) + newY))
            {
                auto *successor_of_expanded_state = &my_map.at(get<0>(s.state) + newX)[get<1>(s.state) + newY];
                auto *successor_of_expanded_state_in_anchor_map = &my_map_anchor.at(get<0>(s.state) + newX)[get<1>(s.state) + newY];
                float gNew;
                gNew = s.gcost + 1.0;
                if(successor_of_expanded_state->gcost>gNew)
                    {
                        successor_of_expanded_state->gcost = gNew;
                        successor_of_expanded_state->parent_state = &s;
                        if(closed_list.find(s) == closed_list.end())
                        {
                            successor_of_expanded_state_in_anchor_map->calculate_heuristic(static_cast<heuristic>(0),robot_goal);
                            successor_of_expanded_state_in_anchor_map->gcost = gNew;
                            successor_of_expanded_state_in_anchor_map->calculate_fcost();

                            //-------- Complete line 12 onwards--------
                        }
                    }

                    //Add the same from the blog. The cost of path from one state to the other has been assumed 1
            }
        }
    }
}
///======================================================================================================================================
///MAIN STARTS
int main(int argc, const char * argv[]) {

    Map init_map(make_tuple(0,0,0),make_tuple(5,9,0),10,10,8); //Handle exception of goal state being within map margin
    vector<vector<State> > my_map = init_map.create_map();
    auto my_map_anchor = my_map;
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

    ///WEIGHTS
    const auto w1 = 1;
    const auto w2 = 1;

    ///MHA* IMPLEMENTATION
    const auto n = (int)heuristic::Count;       //Number of heuristics
    vector< set<State> > open_list (n);
    set<State> open_anchor_list;
    set<State> closed_list;
    set<State> closed_anchor_list;

    ///Insert the start posiiton in all open lists
    for(auto x: open_list)
    {
        x.insert(my_map.at(get<0>(robot_start))[get<1>(robot_start)]);
    }
    queue<State> q;
    bool destination_found = false;

    while(!open_anchor_list.empty())
    {
        for(size_t i = 1;i<n;i++)
        {
            if(open_list[i].begin()->fcost<=w2*(open_anchor_list.begin())->fcost)
            {
                if(goal_state->gcost<=open_list[i].begin()->fcost)
                   {
                       destination_found = true ;
                       break;                       //Handle back pointer here probably
                   }

                auto next_state_to_expand = *(open_list[i].begin());
                expand(next_state_to_expand,i,n,my_map,my_map_anchor,open_list,open_anchor_list,closed_list,closed_anchor_list,robot_goal);
            }

            else
            {
                if(goal_state->gcost<=open_anchor_list.begin()->fcost)
                   {
                       destination_found = true ;
                       break;                       //Handle back pointer here probably
                   }

                auto next_state_to_expand = open_anchor_list.begin();
                expand(next_state_to_expand);
            }
        }
    }   
    return 0;
}


//To do
// - See how to handle raw pointers in class. Issues relating to copying and assigning. Learn overloading for self pointers of a class
// - Implement Independent MHA*
// - Implement Shared MHA* 

//Questions
//How to handle continious angles?
//How to handle 16 connected grid