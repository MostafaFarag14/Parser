
/////////////////////////////////////////////////////////////////
/*
scanner_output.txt must be created in the directory (empty or not)
before running the code (actuallu before running parsing phase)
to make the parser wok properly ,I tried to fix that but i could not 

Parser alone works fine if the scanner_output.txt is already exists  
*/
////////////////////////////////////////////////////////

#include"parser.h"
#include"scanner.h"
void main()
{
	scan();
	parse();
}