//
//  parser.cpp
//  klisp
//
//  Created by Filip Peterek on 11/10/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "parser.hpp"

const std::unordered_map<char, std::string> KobericeLisp::escape = {
    { 'n'  , "\n"  },
    { 't'  , "\t"  },
    { '\\' , "\\"  },
    { '"'  , "\""  },
    { '\'' , "'"   },
    { 'r'  , "\r"  },
    { 'v'  , "\v"  },
    { 'b'  , "\b"  }
};

bool KobericeLisp::isWhiteSpace(char param) {
    
    return isspace(param);
    
}

void KobericeLisp::tokenize(const std::string & filename) {
    
    _filename = filename;
    
    std::ifstream input(filename);
    
    if (not input) {
        
        throw file_not_opened(_filename);
        
    }
    
    std::string line;
    
    size_t lineLen;
    
    while (std::getline(input, line)) {
        
        print(line);
        
        lineLen = line.length();
        
        for (int i = 0; i < lineLen; /* Don't increment here, iter is incremented inside loop */) {
            
            /* Check for single line comment, if found, break out of loop */
            /* The content of a comment is none of the compilers bussines */
            
            if ( line[i] == ';' ) {
                
                break;
                
            }
            
            else if ( KobericeLisp::isWhiteSpace(line[i]) ) {
                
                ++i; /* Do nothing on whitespace, it's not important anymore, just increment iterator */
                
            }
            
            /* Check for parenthesis */
            
            else if ( line[i] == '(' ) {
                
                _tokens.emplace_back( tokType::openingPar, std::string("(") );
                ++i;
                
            }
            else if ( line[i] == ')' ) {
                
                _tokens.emplace_back(tokType::closingPar, std::string(")") );
                ++i;
                
            } /* parenthesis */
            
            /* Check for string literal. String literals keep whitespaces. Copied from different project, not everything might make */
            /* sense, but whatever, so long as it works. Might rewrite in the future.                                               */
            
            else if ( line[i] == '"' ) {
                
                std::string str;
                
                ++i;
                
                while ( line[i] != '"' ) {
                    
                    if ( line[i] == '\\' and i > lineLen - 2) {
                        
                        try {
                            
                            str += KobericeLisp::escape.at( line[i + 1] );
                            
                        } catch (std::out_of_range) {
                            
                            str += ( "\\" + std::string(1, line[i]) );
                            
                        }
                        
                        i += 2;
                        
                    }
                    else {
                        
                        str += std::string(1, line[i]); /* std::string constructor(repeat: int, character: char) */
                        ++i;
                        
                    }
                    
                    if (i >= lineLen) { throw missing_token('"'); }
                    
                }
                
                ++i; /* " character */
                _tokens.emplace_back(tokType::strLit, str);
                
            } /* str literal */
            
            /* Check for an identifier */
            
            else {
                
                std::string str(1, line[i]); /* std::string constructor(repeat: int, character: char) */
                ++i;
                
                while ( not KobericeLisp::isWhiteSpace(line[i])
                        and ( line[i] != ')' and line[i] != '(' and line[i] != '"')
                        and i < lineLen ) {
                    
                    str += std::string(1, line[i]); /* std::string constructor(repeat: int, character: char) */
                    ++i;
                    
                }
                
                _tokens.emplace_back(tokType::anythingElse, str);
                
            } /* identifier */
            
        } /* for */
        
    } /* while */
    
} /* tokenize () */


void KobericeLisp::checkBeginning() {
    
    /* At least three tokens are needed for a function call to (Kobeřice) */
    
    if (_tokens.size() < 3) { throw missing_function_call("beginning"); }
    
    std::string tok = _tokens[1].value;
    std::transform(tok.begin(), tok.end(), tok.begin(), ::tolower); /* Doesn't convert Ř to ř */
    
    if (_tokens[0].type == tokType::openingPar and (tok == "kobeřice" or tok == "kobeŘice") ) {
        
        return; /* Everything is correct, go on */
        
    }
    else { /* Oops, error */
        
        throw missing_function_call("beginning"); /* There's a better way of doing it but this is ok for what I need it to do */
        
    }
    
}

void KobericeLisp::checkEnd() {
    
    /* At least six tokens are needed for two function calls to (Kobeřice) */
    
    if (_tokens.size() < 6) { throw missing_function_call("end"); }
    
    size_t lastTok = _tokens.size() - 1;
    
    std::string tok = _tokens[lastTok - 1].value;
    std::transform(tok.begin(), tok.end(), tok.begin(), ::tolower); /* Doesn't convert Ř to ř, GG */
    
    if (_tokens[lastTok].type == tokType::closingPar and (tok == "kobeřice" or tok == "kobeŘice") ) {
        
        return; /* Everything is correct, go on */
        
    }
    else {
        
        throw missing_function_call("end"); /* There's a better way of doing it but this is ok for what I need it to do */
        
    }
    
}

void KobericeLisp::traverse() {
    
    bool isFunCall = false;
    bool isDefun = false; /* Check for function definitions, if defun is found, this var is set to true and function name is checked */
    
    checkBeginning();
    checkEnd();
    
    for (auto & i : _tokens) {
        
        
        std::transform(i.value.begin(), i.value.end(), i.value.begin(), ::tolower); /* Doesn't convert Ř to ř, GG */
        
        if (i.type == tokType::openingPar) { isFunCall = true; }
        
        if (isDefun and (i.value == "kobeřice" or i.value == "kobeŘice") ) { throw unexpected_function_def("Kobeřice"); }
        else if (isDefun and i.value == "terpri") { throw unexpected_function_def("terpri"); }
        else { isDefun = false; }
        
        if (isFunCall and i.value == "terpri") { throw terpri_function_call(); }
        else if (isFunCall and i.value == "defun") { isDefun = true; }
        // else if (isFunCall and i.value == "opli-mas-oplatek") i.value = "terpri";
        
        
    }
    
}

std::string KobericeLisp::outputFile() {
    
    std::string file = _filename.substr(0, _filename.find("."));
    file.append(".lisp");
    return file;
    
}

void KobericeLisp::convert() {
    
    std::string file = outputFile();
    
    std::stringstream ss;
    std::ofstream output(file);
    
    if (not output) { throw file_not_opened(file); }
    
    print(ss, "(defun Kobeřice ()"                                                                          );
    print(ss, "    (terpri)"                                                                                );
    print(ss, "    (format t \"------------------------------------------------------------------~%\")"     );
    print(ss, "    (format t \"-                                                                -~%\")"     );
    print(ss, "    (format t \"-                       Opli, máš oplatek?                       -~%\")"     );
    print(ss, "    (format t \"-                                                                -~%\")"     );
    print(ss, "    (format t \"------------------------------------------------------------------~%\")"     );
    print(ss, "    (terpri))\n"                                                                             );
    
    print(ss, "(defun opli-mas-oplatek ( &optional (stream *standard-output*) )"                            );
    print(ss, "    (terpri stream))"                                                                        );
    
    int c = 0;
    
    for (auto & i : _tokens) {
        
        if (i.value == "(") {
            
            std::endl(ss); /* Insert newline in front of ( */
            for (int iter = c; iter > 0; --iter) { ss << "    "; }
            ss << "( ";
            ++c;
            
        }
        else if (i.value == ")") { --c; ss << ") ";}
        else if (i.type == tokType::strLit) { ss << "\"" << i.value << "\""; }
        else { ss << i.value << " "; }
        
        if (not c) { std::endl(ss); }
        
    }
    
    output << ss.str();
    
}

void KobericeLisp::test() {
    
    int c = 0;
    
    for (auto & i : _tokens) {
        
        print("Token { " + i.value + " }");
        
        if (i.value == "(") ++c;
        if (i.value == ")") --c;
        
        if (not c) { std::endl(std::cout); }
        
    }
    
}
