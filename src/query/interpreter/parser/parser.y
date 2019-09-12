%{
#include <iostream>
#include "lex.yy.c"
#include <unordered_map>
#include "Interpreter.cpp"
#include "query_graph.hpp"
// #include "query_graph.hpp"
using namespace std;
struct interpreter_struct;
struct interpreter_node;
struct interpreter_edge;
int parse_query(Interpreter *);
int yyerror(char *);
void register_node(char*);
// query_graph generate_query_graph();
interpreter_node create_node(char* name, char* schema_name);
interpreter_edge create_edge(char* name, char* schema_name);
Interpreter* interpreter;
%}
%union {
	int intValue;
	double doubleValue;
	float floatValue;
	char* strValue;
	bool boolValue;
	struct interpreter_node nodeValue;
	struct interpreter_edge edgeValue;
	struct interpreter_struct* structValue;
	void* voidPtrValue;
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
%type <edgeValue> EDGE
%start S
%%
S: MATCH_CLAUSE
;
MATCH_CLAUSE: MATCH GRAPH_REPR RETURN_CLAUSE
;
GRAPH_REPR:
NODE {
	struct interpreter_node* node = &$1;
	cout << ">>"  << (char*)(node->name) << endl;
	interpreter->set_node_id_value(node->name, node);
}
| EDGE {
	// interpreter->set_edge_id_value()
	;
}
| NODE CONNECTOR GRAPH_REPR
| EDGE CONNECTOR GRAPH_REPR
;
NODE:
OPEN_PARENTHESIS CLOSE_PARENTHESIS {
	$$ = create_node("", "");
}
| OPEN_PARENTHESIS IDENTIFIER CLOSE_PARENTHESIS {
	$$ = create_node($2, "");
}
| OPEN_PARENTHESIS IDENTIFIER COLON IDENTIFIER CLOSE_PARENTHESIS {
	$$ = create_node($2, $4);
}
| OPEN_PARENTHESIS COLON IDENTIFIER CLOSE_PARENTHESIS {
	$$ = create_node("", $3);
}
;
EDGE:
OPEN_BRACE CLOSE_BRACE {
	$$ = create_edge("", "");
}
| OPEN_BRACE IDENTIFIER CLOSE_BRACE {
	$$ = create_edge($2, "");
}
| OPEN_BRACE IDENTIFIER COLON IDENTIFIER CLOSE_BRACE {
	$$ = create_edge($2, $4);
}
| OPEN_BRACE COLON IDENTIFIER CLOSE_BRACE {
	$$ = create_edge("", $3);
}
;

CONNECTOR:
ARROW_TO_LEFT
| ARROW_TO_RIGHT
| HYPHEN HYPHEN
| HYPHEN
;

WHERE_CLAUSE:
WHERE
| ;

RETURN_CLAUSE:
RETURN RETURN_REPR
|
;
RETURN_REPR:
IDENTIFIER DOT IDENTIFIER
| IDENTIFIER DOT IDENTIFIER COMA RETURN_REPR
;
%%

interpreter_node create_node(char* name, char* schema_name)
{
	struct interpreter_node node;
	node.name = name;
	node.schema_name = schema_name;
	node.values = NULL;
	node.edges = NULL;
	node.connections = NULL;
	return node;
}

interpreter_edge create_edge(char* name, char* schema_name)
{
	struct interpreter_edge edge;
	edge.name = name;
	edge.schema_name = schema_name;
	edge.values = NULL;
	// edge.edges = NULL;
	return edge;
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
