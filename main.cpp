//
//  main.cpp
//  KobeřiceLisp
//
//  Created by Filip Peterek on 11/10/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include <iostream>

#include "parser.hpp"
#include "print.hpp"


int main(int argc, const char * argv[]) {
    
    KobericeLisp klisp;
    klisp.tokenize("test.klisp");
    // klisp.test();
    
    try {
        
        klisp.traverse();
        klisp.convert();
        
    }
    catch (file_not_opened e) {
        
        print(e.what());
        return -1;
        
    }
    catch (terpri_function_call e ) {
        
        print(e.what());
        return -1;
        
    }
    catch (missing_function_call e) {
        
        print(e.what());
        return -1;
        
    }
    catch (std::exception e) {
        
        print("Unexpected error");
        print(e.what());
        return -1;
        
    }
    
    print("File successfully compiled");
    
    return 0;
    
}
