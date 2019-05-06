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

int main(int argc, const char * argv[]) {
    // insert code here...
    Map my_map(make_tuple(0,0,0),make_tuple(9,9,0),10,10,8);
    my_map.display_map(my_map.create_map());
    return 0;
}


