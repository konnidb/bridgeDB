%{
#include <iostream>
#include "lex.yy.c"
#include "Interpreter.cpp"
using namespace std;
int parse_query(Interpreter *);
int yyerror(char *);
Interpreter* interpreter; 
%}
%token IDENTIFIER 
%token MATCH
%token RETURN
%token CREATE
%token UPDATE
%token COLON 
%token OPEN_C_BRACE
%token CLOSE_C_BRACE 
%token OPEN_PARENTHESIS
%token CLOSE_PARENTHESIS
%token OPEN_BRACE
%token CLOSE_BRACE
%token NOT 
%token WHERE 
%token EQUALS 
%token GREATER_THAN 
%token LOWER_THAN 
%token APOTSTROPHE 
%token QUOTATION_MARK
%token INTEGER
%token DECIMAL
%token DOT
%token ARROW_TO_LEFT 
%token ARROW_TO_RIGHT 
%token HYPHEN 
%token COMA 
%token CONTAINS 
%token STARTS 
%token ENDS
%token WITH
%token PRIME //VIRGUILILLA
%token ASTERISK
%token EOL 
%token STRING 
%token AS
%token TRUE
%token FALSE
%start S
%%
S:  | START S;
START:  MATCH_ST
;
MATCH_ST: MATCH {cout<<"Match simple"<<endl;}
        | MATCH DATA_STRUCT RETURN_ST
        | MATCH DATA_STRUCT WHERE_ST RETURN_ST
;

MATCH_WITH_RETURN: MATCH_ST RETURN_ST
;

CREATE_ST: CREATE DATA_STRUCT
         ;

MATCH_CREATE: MATCH_ST CREATE_ST
;


NODE: OPEN_PARENTHESIS IDENTIFIER COLON OPEN_C_BRACE KEY_VALUE CLOSE_C_BRACE CLOSE_PARENTHESIS
        | OPEN_PARENTHESIS CLOSE_PARENTHESIS
        | OPEN_PARENTHESIS IDENTIFIER COLON IDENTIFIER CLOSE_PARENTHESIS
        | OPEN_PARENTHESIS IDENTIFIER CLOSE_PARENTHESIS
        | OPEN_PARENTHESIS IDENTIFIER OPEN_C_BRACE KEY_VALUE CLOSE_C_BRACE CLOSE_PARENTHESIS
        | OPEN_PARENTHESIS OPEN_C_BRACE KEY_VALUE CLOSE_C_BRACE CLOSE_PARENTHESIS
;
EDGE: OPEN_BRACE IDENTIFIER COLON IDENTIFIER CLOSE_BRACE 
    | OPEN_BRACE COLON IDENTIFIER CLOSE_BRACE
    ;
END_STRUCT: NODE {cout<<$$<<" from parser"<<endl;}
            | EDGE
            ;
CONNECTION_UNDIRECTED: HYPHEN
                    ;
CONNECTION_TO_LEFT: LOWER_THAN HYPHEN
                  | LOWER_THAN HYPHEN HYPHEN
;
CONNECTION_TO_RIGHT: HYPHEN GREATER_THAN
;
CONNECTION: CONNECTION_TO_LEFT
            | CONNECTION_TO_RIGHT
            | HYPHEN HYPHEN
            ;
DATA_STRUCT: END_STRUCT
            | END_STRUCT CONNECTION DATA_STRUCT
            | NODE HYPHEN HYPHEN NODE
            | NODE ARROW_TO_LEFT HYPHEN NODE
            | NODE HYPHEN ARROW_TO_RIGHT NODE
            ;
KEY_VALUE: IDENTIFIER COLON VALUE
           | IDENTIFIER COLON VALUE COMA KEY_VALUE
        ;
WHERE_ST: WHERE CONDITION;
CONDITION: EQUALS_CONDITION
        | GREATER_CONDITION
        | GREATER_EQ_CONDITION
        | LOWER_CONDITION
        | LOWER_EQ_CONDITION
        ;
EQUALS_CONDITION: LITERAL_VALUE EQUALS EQUALS LITERAL_VALUE;
GREATER_CONDITION: LITERAL_VALUE GREATER_THAN LITERAL_VALUE;
LOWER_CONDITION: LITERAL_VALUE LOWER_THAN LITERAL_VALUE;
GREATER_EQ_CONDITION: LITERAL_VALUE GREATER_THAN EQUALS LITERAL_VALUE;
LOWER_EQ_CONDITION: LITERAL_VALUE LOWER_THAN EQUALS LITERAL_VALUE;
RETURN_ST: RETURN ID_RETURN_ST;

ID_RETURN_VALUES: IDENTIFIER
                | IDENTIFIER DOT IDENTIFIER
                ;
ID_RETURN_ST: ID_RETURN_VALUES
            | ID_RETURN_VALUES COMA ID_RETURN_ST
            ;

BOOLEAN: TRUE
        | FALSE;
VALUE:  INTEGER
        | DECIMAL
        | STRING
        | BOOLEAN
        ;
LITERAL_VALUE: VALUE 
            | ID_RETURN_VALUES
            ;
%%

void match_statement()
{
        interpreter->match();
}

int parse_query(Interpreter *intr)
{
	interpreter = intr;
	YY_BUFFER_STATE buffer = yy_scan_string(interpreter->get_query().c_str());
	interpreter->set_parse_result(yyparse());
}

int yyerror(char *string) {
	cout<<string<<endl;
	return 0;
}