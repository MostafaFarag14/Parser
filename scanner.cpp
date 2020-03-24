#include<stdio.h>
#include<iostream>
#include <fstream>
#include <string>
#include"scanner.h"
using namespace std ;


typedef enum
{
	START,INCOMMENT,INNUM,INID,INASSIGN,DONE
}state;

char c;
string x="",buff="";
	string temp;

bool Is_digit(char in)
{
	char d0_9[10]={'0','1','2','3','4','5','6','7','8','9'};
	for(int i=0;i<10;i++) 
	{
		if(in==d0_9[i]) return 1;
	}
	return 0;
}

bool Is_symbol(char in)
{
	char sym[9]={'+','-','*','/','=','<','(',')',';'};
	for(int i=0;i<9;i++) 
	{
		if(in==sym[i]) return 1;
	}
	return 0;
}
bool Is_res_word(string in)
{
	string words[8]={"if","then","else","end","repeat","until","read","write"};
	for(int i=0;i<8;i++) 
	{
		if(in==words[i]) return 1;
	}
	return 0;
}
void add_to_x()
{
	temp=c;
	x.append(temp);
}

void add_to_buff()
{
	temp=c;
	buff=buff.append(temp);
}
	
bool Is_alpha(char in)
{
	if((in>64 && in<91) | (in>96 && in<123))
	{return 1;}
	return 0;
}
void scan()
{	
	state state,prev_state=START;
	state=prev_state;
	ofstream myfile;
	myfile.open ("scanner_output.txt");
fstream fin("tiny_sample_code.txt", fstream::in);
while (fin >> noskipws >> c) {
    
	
	pass:
	switch(state)
	{
		case START :
			{
				if(c=='{') state=INCOMMENT;
				else if(Is_digit(c))
					{
						add_to_x();
						state=INNUM;
					}
				else if(Is_symbol(c))
				{
					add_to_x();
					prev_state=state;
					state=DONE;
				}
				else if(c==':') 
				{
					add_to_x();
					state=INASSIGN;
				}
				else if(isalpha(c))
				{
					add_to_x();
					state=INID;
				}
				break;
			}
		case INCOMMENT  :
			{
				if(c!='}') state=INCOMMENT ;
				else state=START;
				break;
			}
		case INNUM :
			{
				if(Is_digit(c))
					{
						add_to_x();
						state=INNUM;
					}
				else{
					add_to_buff();
						prev_state=state;
						state=DONE;
					}
				break;
			}
		case INID :
			{
				if(isalpha(c))
				{
					add_to_x();
					state=INID;
				}
				else
				{
					add_to_buff();
					prev_state=state;
					state=DONE;
				}
			}
			break;
		case INASSIGN :
			{
					if(c=='=') 
					{
						add_to_x();
						prev_state=state;
						state=DONE;
					}
					else 
					{
						x="";
						add_to_buff();
						prev_state=state;
						state=DONE;
					}
			}
			break;
		case DONE :
			{
				switch (prev_state)
				{
					
				case INNUM: 
					{
						myfile<<x<<" : Number\n";
						break;
					}
				case START :
					{
						myfile<<x<<" : Special_Symbol\n";
						break;
					}
				case INASSIGN :
					{
						if(x.empty()!=1)
						myfile<<x<<" : Special_Symbol\n";
						break;
					}
				case INID :
					{
						if(Is_res_word(x))
							myfile<<x<<" : Reserved_Word\n";
						else myfile<<x<<" : Identifier\n";
						break;
					}
				}
				x="";
				state=START;
			}
			break;					
	}

	if(state==DONE)
		 goto pass;

	if (buff.empty()!=1 && state==START)
		 {
			c=buff[0];
			buff.erase(0,1);
			goto pass;
		 }
}
	   myfile.close();
}