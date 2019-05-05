//
//  main.cpp
//  MHA*
//
//  Created by Harsh Sharma on 01/05/19.
//  Copyright © 2019 Harsh Sharma. All rights reserved.
//

#include <iostream>
#include "Map.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Map my_map;
    my_map.display_map(my_map.create_map());
    return 0;
}


