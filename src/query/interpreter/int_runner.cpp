#include <iostream>
#include "parser.tab.c"
#include <string.h>
#include "Interpreter.hpp"
#include <assert.h>
#include <unordered_map>
// #include "parser.tab.c"
using namespace std;
bool greater_than(void *parameter, void *control);
template <typename T>
bool typed_gt(void*, void*);

// int parse_query(Interpreter *);
int main()
{
	Interpreter intr("MATCH ( n : Person ) RETURN n.property");
	cout<<"Hello world";
	parse_query(&intr);
	unordered_map<string, void*> map = intr.get_nodes_map();
	string* tmp_str = static_cast<string*>(map["n"]);
	cout << tmp_str << endl;
	// int a = 12;
	// int b = 20;
	// cout<<greater_than(&a,&b)<<" >>>>"<<endl;
	// cout << typed_gt<float>(&a, &b) << " >>>>" << endl;
	
	return intr.get_parse_result();
}

bool greater_than(void* parameter, void* control)
{	
	return *static_cast<int*>(parameter) > *static_cast<int*>(control);
}

template <typename T>
bool typed_gt(void* arg1, void* arg2)
{
	return *static_cast<T*>(arg1) > *static_cast<T*>(arg2);
}

// YY_BUFFER_STATE buffer = yy_scan_string("MATCH (n:Person) RETURN n.property");
	// int result = yyparse();
	// cout << result << endl;
	// yy_delete_buffer(buffer);