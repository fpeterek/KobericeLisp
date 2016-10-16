//
//  token.hpp
//  KobeřiceLisp
//
//  Created by Filip Peterek on 11/10/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef token_hpp
#define token_hpp

#include <stdio.h>
#include <iostream>


enum class tokType {
    
    openingPar,     //  Opening parenthesis '('
    closingPar,     //  Closing parenthesis ')'
    strLit,         //  String literal, eg. "Kobeřice"
    anythingElse,   //  Anything else
    none
    
};


struct token {
    
    tokType type;
    std::string value;
    
    token(tokType t, std::string val);
    token();
    
};


#endif /* token_hpp */
