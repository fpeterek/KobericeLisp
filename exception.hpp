//
//  exception.hpp
//  klisp
//
//  Created by Filip Peterek on 11/10/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef exception_hpp
#define exception_hpp

#include <stdio.h>
#include <iostream>

/* There's a better way of doing it but this is ok for what I need it to do */

class missing_function_call : public std::exception {
    
    std::string _position;
    
public:
    missing_function_call(std::string & position);
    missing_function_call(const char * position);
    
    const char * what();
    
};

class terpri_function_call : public std::exception {
    
public:
    
    const char * what();
    
};

class file_not_opened : public std::exception {
    
    std::string _filename;
    
public:
    
    file_not_opened(std::string & filename);
    file_not_opened(const char * filename);
    const char * what();
    
};

class unexpected_function_def : public std::exception {
    
    std::string _functionName;
    
public:
    
    unexpected_function_def(const char * funName);
    unexpected_function_def(std::string & funName);
    
    const char * what();
    
};

#endif /* exception_hpp */
