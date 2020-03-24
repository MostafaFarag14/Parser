
#include"parser.h"
#include <iostream>
#include <string>
#include <fstream>
#include"scanner.h"
using namespace std ;


fstream fin("scanner_output.txt", fstream::in);
void exp();
void stmt_seq();
string token , t1,t2 ; 
ofstream parse_file;
void parse_line()
{
	fin>>t1;
	fin>>t2;
	fin>>t2;
	if(t2 == "Reserved_Word" || t2 == "Special_Symbol" ) token=t1;
	else if (t2 =="Number" || t2 =="Identifier" ) token=t2;
}

void WF(string x)
{
	parse_file<<x<<"\n";
}
void advance()
{
	parse_line();
}
void match(string x)
{
	if(token == x)
		advance();
}
void factor()
{
	if(token == "(")
	{
		match("(");
		exp();
		match(")");
		return;
	}
	if(token == "Number" || token == "Identifier" )
	match(token);
	WF("Factor Found");
}

void mulop()
{
	match(token);
	WF("Mul_Operator Found");
}

void term()
{
	factor();
	while (token == "*" || token == "/")
	{
		mulop();
		factor();
	}
	WF("Term Found");
}
void addop()
{
	match(token);
	WF("Add_Operator Found");
}
void simple_exp()
{
	term();
	while (token == "+" || token == "-")
	{
		addop();
		term();
	}
	WF("Simple_Expression Found");
}
void comp_op()
{
	match(token);
	WF("Comparator_Operator Found");
}
void exp()
{
	simple_exp();
	if(token == "<" || token == "=")
	{
		comp_op();
		simple_exp();
	}
	WF("Expression Found");
}
void read_stmt()
{
	match("read");
	match("Identifier");
	WF("Read_Statement Found");
}
void repeat_stmt()
{
	match("repeat");
	stmt_seq();
	match("until");
	exp();
	WF("Repeat_Statement Found");
}
void write_stmt()
{
	match("write");
	exp();
	WF("Write_Statement Found");
}
void if_stmt()
{
	match("if");
	exp();
	match("then");
	stmt_seq();
	if(token == "else")
	{
		match(token);
		stmt_seq();
	}
	match("end");
	
	WF("IF_Statement Found");
}
void assign_stmt ()
{
	match("Identifier");
	match(":=");
	exp();
	WF("Assignment_Statement Found");
}
void stmt()
{
	if(token == "read") read_stmt();
	else if (token == "repeat") repeat_stmt();
	else if (token == "write") write_stmt();
	else if (token == "if") if_stmt();
	else assign_stmt ();
	WF("Statement Found");
}
void stmt_seq()
{
	do	{
		match(";");
		stmt();
		}
	while (token == ";");
WF("Statement_Sequence Found");
}

void program()
{
	parse_line();
	stmt_seq();
	WF("Program Found");
}

void parse()
{

	parse_file.open("parser_output.txt");
	program() ; 
	cout<<"Done\n";
	parse_file.close();
}
