#include <iostream>
#include "parser.tab.c"
#include <string.h>
#include "Interpreter.hpp"
// #include "parser.tab.c"
using namespace std;
bool greater_than(void *parameter, void *control);
template <typename T>
bool typed_gt(void*, void*);

// int parse_query(Interpreter *);
int main()
{
	Interpreter intr("MATCH (n:Person) RETURN n.property");
	cout<<"Hello world";
	parse_query(&intr);
	// YY_BUFFER_STATE buffer = yy_scan_string("MATCH (n:Person) RETURN n.property");
	// int result = yyparse();
	// cout << result << endl;
	// yy_delete_buffer(buffer);
	int a = 12;
	int b = 20;
	cout<<greater_than(&a,&b)<<" >>>>"<<endl;
	cout << typed_gt<float>(&a, &b) << " >>>>" << endl;
	
	return intr.get_parse_result();
}

bool greater_than(void* parameter, void* control)
{	
	return *static_cast<int*>(parameter) > *static_cast<int*>(control);
}

template <typename T>
bool typed_gt(void* arg1, void* arg2)
{
	T a = *static_cast<T*>(arg1);
	T b = *static_cast<T*>(arg2);
	T c = a + b;
	return *static_cast<T*>(arg1) > *static_cast<T*>(arg2);
}
