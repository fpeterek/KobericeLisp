//
//  print.hpp
//  klisp
//
//  Created by Filip Peterek on 11/10/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef print_h
#define print_h

#include <iostream>

template <class T>
void print(T param) {
    std::cout << param << std::endl;
}

#endif /* print_h */
