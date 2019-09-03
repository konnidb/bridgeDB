%{
#include <iostream>
#include "lex.yy.c"
#include <string.h>
#include <unordered_map>
#include "Interpreter.cpp"
using namespace std;
int parse_query(Interpreter *);
int yyerror(char *);
void register_node(char*);
interpreter_node* generate_node(char* node_id, char* schema_name, unordered_map<string, void*>* value);
interpreter_edge* generate_edge(char* edge_name, char* label, char* schema_name);
Interpreter* interpreter;
%}
%union {
        int intValue;
        double doubleValue;
        float floatValue;
        char* strValue;
        bool boolValue;
        interpreter_node* nodeValue;
        interpreter_edge* edgeValue;
}
%token <strValue> IDENTIFIER
%token <strValue> MATCH
%token <strValue> RETURN
%token <strValue> CREATE
%token <strValue> UPDATE
%token COLON
%token OPEN_C_BRACE
%token <strValue> CLOSE_C_BRACE 
%token OPEN_PARENTHESIS
%token CLOSE_PARENTHESIS
%token <strValue> OPEN_BRACE
%token <strValue> CLOSE_BRACE
%token <strValue> NOT 
%token <strValue> WHERE 
%token <strValue> EQUALS 
%token <strValue> GREATER_THAN 
%token <strValue> LOWER_THAN  
%token <strValue> APOTSTROPHE 
%token <strValue> QUOTATION_MARK
%token <strValue> INTEGER
%token <doubleValue> DECIMAL
%token <strValue> DOT
%token <strValue> ARROW_TO_LEFT 
%token <strValue> ARROW_TO_RIGHT 
%token <strValue> HYPHEN 
%token <strValue> COMA 
%token <strValue> CONTAINS 
%token <strValue> STARTS 
%token <strValue> ENDS
%token <strValue> WITH
%token <strValue> PRIME //VIRGUILILLA
%token <strValue> ASTERISK
%token <strValue> EOL 
%token <strValue> STRING 
%token <strValue> AS
%token <strValue> TRUE
%token <strValue> FALSE
%type <nodeValue> NODE
%type <strValue> END_STRUCT
%type <strValue> EDGE
%start S
%%
S:  | START S;
START:  MATCH_ST
;
MATCH_ST: MATCH {cout<<"Match simple"<<endl;}
        | MATCH DATA_STRUCT RETURN_ST {cout<<"Match DATA RET"<<endl;}
        | MATCH DATA_STRUCT WHERE_ST RETURN_ST {cout<<"Match DATA WHERE RET"<<endl;}
;

MATCH_WITH_RETURN: MATCH_ST RETURN_ST
;

CREATE_ST: CREATE DATA_STRUCT
         ;

MATCH_CREATE: MATCH_ST CREATE_ST
;

END_STRUCT: NODE {$$ = "";}
            | EDGE
            ;

NODE: OPEN_PARENTHESIS IDENTIFIER COLON IDENTIFIER OPEN_C_BRACE KEY_VALUE CLOSE_C_BRACE CLOSE_PARENTHESIS {
                $$ = generate_node($2, $4,NULL);
        }
        | OPEN_PARENTHESIS CLOSE_PARENTHESIS {$$ = generate_node("", "", NULL);}
        | OPEN_PARENTHESIS IDENTIFIER COLON IDENTIFIER CLOSE_PARENTHESIS {$$ = generate_node($2, $4, NULL);}
        | OPEN_PARENTHESIS IDENTIFIER CLOSE_PARENTHESIS {$$ = generate_node($2, "", NULL);}
        | OPEN_PARENTHESIS IDENTIFIER OPEN_C_BRACE KEY_VALUE CLOSE_C_BRACE CLOSE_PARENTHESIS {$$ = generate_node($2, "", NULL);}
        | OPEN_PARENTHESIS OPEN_C_BRACE KEY_VALUE CLOSE_C_BRACE CLOSE_PARENTHESIS {$$ = NULL;}
;
EDGE: OPEN_BRACE IDENTIFIER COLON IDENTIFIER CLOSE_BRACE {$$ = $2;}
    | OPEN_BRACE COLON IDENTIFIER CLOSE_BRACE
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
DATA_STRUCT: END_STRUCT {cout << "END_STRUCT" << endl;}
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
        yyparse();
	// interpreter->set_parse_result(yyparse());
}

int yyerror(char *string) {
	cout<<string<<endl;
	return 0;
}

interpreter_edge* generate_edge(char* edge_name, char* label, char* schema_name)
{
	interpreter_edge edge;
	edge.name = edge_name;
	edge.label = label;
	edge.schema_name = schema_name;
	return &edge;
}

interpreter_node* generate_node(char* node_id, char* schema_name, unordered_map<string, void*>* value)
{
	interpreter_node node;	
	node.name = node_id;
	node.schema_name = schema_name;
	node.values = value;
	return &node;
}

void register_node(char* nodeID)
{
        cout << "HERE MTFCK!" << endl;
        interpreter->create_node_id(nodeID);
}