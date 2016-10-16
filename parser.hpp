//
//  parser.hpp
//  klisp
//
//  Created by Filip Peterek on 11/10/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <unordered_map>

#include "token.hpp"
#include "print.hpp"
#include "exception.hpp"


class KobericeLisp {
    
    static const std::unordered_map<char, std::string> escape;  //  " \n \t \\ \" \' \r \v \b ";
    static bool isWhiteSpace(char param);
    
    /* Non-static members */
    
    std::vector<token> _tokens;
    std::string _filename;
    std::string outputFile();
    
public:
    
    void tokenize(const std::string & filename);
    void checkBeginning();
    void checkEnd();
    void traverse();
    void convert();
    
    
    void test();
    
};



#endif /* parser_hpp */
