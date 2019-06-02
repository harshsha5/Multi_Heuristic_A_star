//
//  main.cpp
//  MHA*
//
//  Created by Harsh Sharma on 01/05/19.
//  Copyright © 2019 Harsh Sharma. All rights reserved.
//

#include <iostream>
#include <tuple>
#include "Map.hpp"
#include "state.hpp"

int main(int argc, const char * argv[]) {
    Map init_map(make_tuple(0,0,0),make_tuple(9,9,0),10,10,8);
    vector<vector<State> > my_map = init_map.create_map();
    init_map.display_map(my_map);
    
    tuple<int,int,double> robot_start = init_map.get_robot_start_pos();
    my_map.at(get<0>(robot_start))[get<1>(robot_start)].gcost = 0 ;

    //Initialze the start position's gcost,fcost,hcost to zero
    //Define a function is_valid to check if a state is valid or not 
    //Check which state to expand from the open list. Add it to closed list after expanding
    //Check all its nearby neighbours depending on the grid-connectedness 
    //See if the new_fcost is lower than the existing. If yes, update the costs and parents. Add state to open set/list
    
    return 0;
}


//Questions
//How to handle continious angles?
//How to handle 16 connected grid