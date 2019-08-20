#ifndef CLASS_LEXER
#define CLASS_LEXER
#include <iostream>
#include <string.h>
#include "lex.yy.c"

using namespace std;

class lexer
{
private:
    string query_str;
public:
    lexer(string);
    int* getTokensFromInput();
    ~lexer();
};

#endif