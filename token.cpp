//
//  token.cpp
//  KobeřiceLisp
//
//  Created by Filip Peterek on 11/10/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "token.hpp"


token::token(tokType t, std::string val) {
    
    type = t; value = val;
    
}

token::token() {
    
    type = tokType::none; value = "";
    
}

