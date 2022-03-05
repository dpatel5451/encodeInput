/*
* FILE           : asmAndSREC.h
* PROJECT        : Assignment 2 : The encodeInput utility
* PROGRAMMER     : Deep Patel and Gaurav Lodha
* FIRST VERSION  : 2022-02-09
* DESCRIPTION    :
*/



#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Defining constant 
#define firstLine 1
#define afterFirstLine 2
#define usage "-h"
#define sRecord "-srec"
#define zero 0
#define one 1
#define two 2
#define three 3
#define four 4
#define five 5
#define six 6
#define fileInput "-i"
#define fileOutput "-o"
#define max_characters 100
#define assemblyExt ".asm"
#define sRecExt ".srec"
#define lineSize 120
#define maxBytes 16
#define initialLocation 0000

#pragma warning(disable:4996)



// Function prototypes for checking which function to call
void oneArgument(char argument[max_characters]);
void twoArguments(char firstArgument[max_characters], char secondArgument[max_characters]);
void threeArguments(char firstArgument[max_characters], char secondArgument[max_characters], char thirdArgument[max_characters]);

// Function prototypes which will check if argument is input/output file type.
int checkFileType(char* argument);

// Function prototypes which will print instructions to user.
void printInstructions(void);

// Functions prototypes which will convert code to Assembly.
void convertAsmStdout(void);
void convertAsmStdin(char* outputFileName);
void convertAssembly(char* inputFileName, char* outputFileName);

// Functions prototypes which will convert code to SREC.
void stdinoutSREC(void);
void stdinSREC(char* outputFileName);
void convertSREC(char* inputFileName, char* outputFileName);


// Function prototypes which will count characters and counts Location.
void printCC(FILE* outputFile, int srecWords);
void printAAAA(FILE* outputFile, int srecWords);