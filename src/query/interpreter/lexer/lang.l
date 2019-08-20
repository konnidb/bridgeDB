%{
#include "parser.tab.h"
%}
string	    \"[^\n"]+\"
integer     [+-]?[0-9]+
decimal     [+-]?[0-9]+\.[0-9]+
id          [_a-zA-Z][_a-zA-Z0-9]*
%%
"("         return OPEN_PARENTHESIS;
")"         return CLOSE_PARENTHESIS;
"{"         return OPEN_C_BRACE;
"}"         return CLOSE_C_BRACE;
"["         return OPEN_BRACE;
"]"         return CLOSE_BRACE;
"-"         return HYPHEN;
"."         return DOT;
"AS"        return AS;
"MATCH"     {std::cout<<"Simple cout from match"<<std::endl;return MATCH;}
"RETURN"    return RETURN;
":"         return COLON;
"NOT"       return NOT;
"WHERE"     return WHERE;
"="         return EQUALS;
">"         return GREATER_THAN;
"<"         return LOWER_THAN;
"'"         return APOTSTROPHE;
"\""        return QUOTATION_MARK;
"<-"        return ARROW_TO_LEFT;
"->"        return ARROW_TO_RIGHT;
","         return COMA;
"CONTAINS"  return CONTAINS;
"STARTS"    return STARTS;
"ENDS"      return ENDS;
"WITH"      return WITH;
"~"         return PRIME;
"*"         return ASTERISK;
{integer}   return INTEGER;
{decimal}   return DECIMAL;
{string}	return STRING;
{id}        return IDENTIFIER;
\n          return EOL;

%%

int yywrap(void) {
    return 1;
}