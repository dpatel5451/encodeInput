/*
* FILE           : AdditionalFunctions.cpp
* PROJECT        : Assignment 2 : The encodeInput utility
* PROGRAMMER     : Deep Patel and Gaurav Lodha
* FIRST VERSION  : 2022-02-09
* DESCRIPTION    : 
*/



#include "asmAndSREC.h"



/*
* Function   :  oneArgument()
* Parameter  :  char argument[max_characters]
* return     :  none
* Description:  this function will be called when user write one argument in command line
* 
*/
void oneArgument(char argument[max_characters])
{
	// if argument is -h 
	if (strcmp(argument, usage) == 0)
	{
		printInstructions();
	}
	// if argument is -srec
	else if (strcmp(argument, sRecord) == 0)
	{
		stdinoutSREC();
	}
	// if argument starts from -i or -o 
	else
	{
		int checkValue = 0;
		checkValue = checkFileType(argument);

		if (checkValue == 1)
		{
			char fileName[max_characters] = "";
			strcpy(fileName, argument);
			strcat(fileName, sRecExt);
			convertAssembly(argument, fileName);
		}
		// getting the extension behind the filename for conversion of standard text
		else if (checkValue == 2)
		{

			char* ptr = NULL;
			const int dot = '.';
			ptr = strrchr(argument, dot);
			if (ptr != NULL)
			{
				if (strcmp(ptr, assemblyExt) == 0)
				{
					//if extension is arm, then it will convet to assembly
					convertAsmStdin(argument);
				}
				else if (strcmp(ptr, sRecExt) == 0)
				{
					// if file extension is srec, then it will convert to srec
					stdinSREC(argument);
				}
				else
				{
					//If output extension is different, then it will convert into assembly.
					convertAsmStdin(argument);
				}
			}
			else
			{
				//If there is no extension, then it will print assembly file.
				char outputFile[max_characters] = "";
				strcpy(outputFile, argument);
				strcat(outputFile, assemblyExt);
				convertAsmStdin(outputFile);
			}

		}
		// if argument doesnot match above given argument
		// it will print error 
		else
		{
			printf("Error, Wrong Command! Type -h for help");
		}
	}
}





/*
* Function   :  twoArguments()
* Parameter  :  char firstArgument[max_characters], char secondArgument[max_characters]
* return     :  none
* Description:  This function will be called when user write two argument in command line
*
*/
void twoArguments(char firstArgument[max_characters], char secondArgument[max_characters])
{

	int checkValue = 0;
	checkValue = checkFileType(firstArgument);
	int checkValueAgain = 0;
	checkValueAgain = checkFileType(secondArgument);

	// if argument is -srec from both arguments then 
	// it connvert text to srec
	if (strcmp(firstArgument, sRecord) == 0)
	{
		int checkValue = 0;
		checkValue = checkFileType(secondArgument);

		// checking first argument is -i or -o with filename
		if (checkValue == 1)
		{
			char fileName[max_characters] = "";
			strcpy(fileName, secondArgument);
			strcat(fileName, sRecExt);
			convertSREC(secondArgument, fileName);
		}
		//checking second argument is srec 
		else if (checkValue == 2)
		{
			stdinSREC(secondArgument);
		}
		// if user type wrong or different commannd it will show error
		else
		{
			printf("Error, Wrong Command! Type -h for help");
		}
	}
	// if second argument is srec then which is first argument from -i or -o 
	else if (strcmp(secondArgument, sRecord) == 0)
	{
		int checkValue = 0;
		checkValue = checkFileType(firstArgument);

		if (checkValue == 1)
		{
			char fileName[max_characters] = "";
			strcpy(fileName, firstArgument);
			strcat(fileName, sRecExt);
			convertSREC(firstArgument, fileName);
		}
		else if (checkValue == 2)
		{
			stdinSREC(firstArgument);
		}
		else
		{
			printf("Error, Wrong Command! Type -h for help");
		}
	}
	// Check if first argument is -i and second argument is -o
	else if (checkValue == 1 && checkValueAgain == 2)
	{
		char outputFileName[max_characters] = "";
		strcpy(outputFileName, secondArgument);
		char* ptr = NULL;
		const int dot = '.';
		ptr = strrchr(outputFileName, dot);
		if (ptr != NULL)
		{
			if (strcmp(ptr, assemblyExt) == 0)
			{
				//if extension is arm, then it will convet to assembly
				convertAssembly(firstArgument, outputFileName);
			}
			else if (strcmp(ptr, sRecExt) == 0)
			{
				// if file extension is srec, then it will convert to srec
				convertSREC(firstArgument, outputFileName);
			}
			else
			{
				//If output extension is different, then it will convert into assembly.
				convertAssembly(firstArgument, outputFileName);
			}
		}
		else
		{
			//If there is no extension, then it will print assembly file.
			char outputFile[max_characters] = "";
			strcpy(outputFile, secondArgument);
			strcat(outputFile, assemblyExt);
			convertSREC(firstArgument, outputFile);
		}

	}
	// Check if first argument is -o and second argument is -i
	else if (checkValue == 2 && checkValueAgain == 1)
	{
		char outputFileName[max_characters] = "";
		strcpy(outputFileName, firstArgument);
		char* ptr = NULL;
		const int dot = '.';
		ptr = strrchr(outputFileName, dot);
		if (ptr != NULL)
		{
			if (strcmp(ptr, assemblyExt) == 0)
			{
				//if extension is arm, then it will convet to assembly
				convertAssembly(secondArgument, outputFileName);
			}
			else if (strcmp(ptr, sRecExt) == 0)
			{
				// if file extension is srec, then it will convert to srec
				convertSREC(secondArgument, outputFileName);
			}
			else
			{
				//If output extension is different, then it will convert into assembly.
				convertAssembly(secondArgument, outputFileName);
			}
		}
		else
		{
			//If there is no extension, then it will print assembly file.
			char outputFile[max_characters] = "";
			strcpy(outputFile, secondArgument);
			strcat(outputFile, assemblyExt);
			convertSREC(secondArgument, outputFile);
		}
	}
	else
	{
		printf("Error, Wrong Command! Type -h for help");
	}
}





/*
* Function   :  threeArguments()
* Parameter  :  char firstArgument[max_characters], char secondArgument[max_characters], char thirdArgument[max_characters]
* return     :  none
* Description:  this function will be called when user write three argument in command line
*
*/
void threeArguments(char firstArgument[max_characters], char secondArgument[max_characters], char thirdArgument[max_characters])
{
	// From three arguemnet it is fixed one will be -srec
	// if -srec is first argument than other two will be -i or -o 
	if (strcmp(firstArgument, sRecord) == 0)
	{
		int checkValue = 0;
		checkValue = checkFileType(secondArgument);
		int checkValueAgain = 0;
		checkValueAgain = checkFileType(thirdArgument);

		// checking which one -i or -o 
		if (checkValue == 1 && checkValueAgain == 2)
		{
			char outputFileName[max_characters] = "";
			strcpy(outputFileName, thirdArgument);
			int checkValue = 0;
			checkValue = checkFileType(thirdArgument); 
			if (checkValue == 2)
			{
				convertSREC(secondArgument, outputFileName);
			}
			else
			{
				printf("Error, Wrong Command! Type -h for help");
			}
		}
		else if (checkValue == 2 && checkValueAgain == 1)
		{
			char outputFileName[max_characters] = "";
			strcpy(outputFileName, secondArgument);
			int checkValue = 0;
			checkValue = checkFileType(secondArgument); 
			if (checkValue == 2)
			{
				convertSREC(thirdArgument, outputFileName);
			}
			else
			{
				printf("Error, Wrong Command! Type -h for help");
			}
		}
		else
		{
			printf("Error, Wrong Command! Type -h for help");
		}
	}
	else if (strcmp(secondArgument, sRecord) == 0)
	{
		int checkValue = 0;
		checkValue = checkFileType(firstArgument);
		int checkValueAgain = 0;
		checkValueAgain = checkFileType(thirdArgument);
		if (checkValue == 1 && checkValueAgain == 2)
		{
			char ofilename[max_characters] = "";
			strcpy(ofilename, thirdArgument);
			int checkValue = 0;
			checkValue = checkFileType(thirdArgument); 
			if (checkValue == 2)
			{
				convertSREC(firstArgument, ofilename);
			}
			else
			{
				printf("Error, Wrong Command! Type -h for help");
			}
		}
		else if (checkValue == 2 && checkValueAgain == 1)
		{
			char ofilename[max_characters] = "";
			strcpy(ofilename, firstArgument);
			int checkValue = 0;
			checkValue = checkFileType(firstArgument); 
			if (checkValue == 2)
			{
				convertSREC(thirdArgument, ofilename);
			}
			else
			{
				printf("Error, Wrong Command! Type -h for help");
			}
		}
		else
		{
			printf("Error, Wrong Command! Type -h for help");
		}
	}
	else if (strcmp(thirdArgument, sRecord) == 0)
	{
		int checkValue = 0;
		checkValue = checkFileType(firstArgument);
		int checkValueAgain = 0;
		checkValueAgain = checkFileType(secondArgument);
		if (checkValue == 1 && checkValueAgain == 2)
		{
			char ofilename[max_characters] = "";
			strcpy(ofilename, secondArgument);
			int checkValue = 0;
			checkValue = checkFileType(secondArgument); 
			if (checkValue == 2)
			{
				convertSREC(firstArgument, ofilename);
			}
			else
			{
				printf("Error, Wrong Command! Type -h for help");
			}
		}
		else if (checkValue == 2 && checkValueAgain == 1)
		{
			char ofilename[max_characters] = "";
			strcpy(ofilename, firstArgument);
			int checkValue = 0;
			checkValue = checkFileType(firstArgument); 
			if (checkValue == 2)
			{
				convertSREC(secondArgument, ofilename);
			}
			else
			{
				printf("Error, Wrong Command! Type -h for help");
			}
		}
		else
		{
			printf("Error, Wrong Command! Type -h for help");
		}


	}
	else
	{
		printf("Error, Wrong Command! Type -h for help");
	}

}




/*
* Function   :  checkFileType()
* Parameter  :  char* argument
* return     :  fileType 
* Description:  this function will check the file is input(-i) or output(-o)
*/
int checkFileType(char* argument)
{
	char fileType[four] = "";
	strncpy(fileType, argument, 2);
	// checking the argument is for input file 
	// if file is -i then it will return 1 
	if (strcmp(fileType, fileInput) == 0)
	{
		return 1;
	}
	// checking the argument is for output file
	// if file is -o then it will return 2 
	else if (strcmp(fileType, fileOutput) == 0)
	{
		return 2;
	}
	// if argument is not start with -i or -o 
	// then it will return 0
	else
	{
		return 0;
	}
}


/*
* Function   :  printInstructions()
* Parameter  :  void
* return     :  none
* Description:  this function will show usage instructions to user
*/
void printInstructions(void)
{
	printf("encodeInput has 4 optional switches which are ");
	printf("\n i) -iINPUTFILENAME ii) -oOUTPUTFILENAME iii) -srec iv) -h ");
}



