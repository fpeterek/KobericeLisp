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

#define __DEBUG

bool isKLisp(std::string & filename) {
    
    if (filename.rfind(".klisp") == filename.length() - 6) {
        
        return true;
        
    }
    
    return false;
    
}


int main(int argc, const char * argv[]) {
    
    KobericeLisp klisp;
    std::string filename;
    
    print(isspace('\n'));
    
#ifndef __DEBUG
    
    if (argc > 1) {
        
        filename = argv[1];
        
    }
    else {
    
        print("No file to compile");
        return 0;
    
    }
    
    if (not isKLisp(filename)) {
        
        print("File is not a KobeřiceLisp file. (Extension .klisp)");
        return -1;
    
    }
    
#else
    filename = "test.klisp";
#endif
    
    klisp.tokenize(filename);
    
#ifdef __DEBUG
    print("\nTokens: \n");
    klisp.test();
#endif
    
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
    catch (unexpected_function_def e) {
        
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
