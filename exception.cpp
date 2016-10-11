//
//  exception.cpp
//  klisp
//
//  Created by Filip Peterek on 11/10/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "exception.hpp"

/* There's a better way of doing it but this is ok for what I need it to do */

missing_function_call::missing_function_call(std::string & position) {
    
    _position = position;
    
}

missing_function_call::missing_function_call(const char * position) {
    
    _position = position;
    
}

const char * missing_function_call::what() {
    
    std::string str = "Missing funtion call to (Kobeřice) at the " + _position + " of file. ";
    return str.c_str();
    
}

const char * terpri_function_call::what() {
    
    return "Unexpected call to (terpri). Use (opli-mas-oplatek) in klisp instead. ";
    
}

file_not_opened::file_not_opened(std::string & filename) {
    
    _filename = filename;
    
}

file_not_opened::file_not_opened(const char * filename) {
    
    _filename = filename;
    
}

const char * file_not_opened::what() {
    
    std::string str = "Unable to open " + _filename;
    return str.c_str();
    
}
