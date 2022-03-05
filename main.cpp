/*
* FILE           : main.cpp
* PROJECT        : Assignment 2 : The encodeInput utility
* PROGRAMMER     : Deep Patel and Gaurav Lodha
* FIRST VERSION  : 2022-02-09
* DESCRIPTION    :
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asmAndSREC.h"


// defining constant 
#define one 1
#define two 2
#define three 3
#define four 4



int main(int argc, char* argv[])
{ 
	// if argument is just project name (encodeInput)
	if (argc == two)
	{
		convertAsmStdout();
	}
	// if there are two argument in command line including project name (encodeInput)
	else if (argc == three)
	{
		oneArgument(argv[two]);
	}
	// if there are three argument in command line including project name (encodeInput)
	else if (argc == four)
	{
		twoArguments(argv[two], argv[three]);
		
	}
	// if there are four argument in command line including project name (encodeInput)
	else if (argc == five)
	{
		threeArguments(argv[two], argv[three], argv[four]);
	}
	// if user did not write the command line than it will show usage instruction
	else
	{
		printf("Usage Instructions");
	}

	return 0;

}





