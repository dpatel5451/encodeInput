/*
* FILE           : converToASM.cpp
* PROJECT        : Assignment 2 : The encodeInput utility
* PROGRAMMER     : Deep Patel and Gaurav Lodha
* FIRST VERSION  : 2022-02-09
* DESCRIPTION    :
*/


#include "asmAndSREC.h"

/*
* Function   :  convertAsmStdin()
* Parameter  :  char* outputFileName
* return     :  none
* Description:  this function convert standard input into assmebly
*               by taking input from console by displaying output in file of extension .asm
*/
void convertAsmStdin(char* outputFileName)
{
	//variable declaration
	FILE* outputFile = NULL;
	int bytesCount = 0;
	int byte = 0;
	char Value[three] = { 0 };

	char currentLine = firstLine;
	char* fileToPrint = outputFileName + 2;

	//creating a file for output 
	outputFile = fopen(fileToPrint, "wb");

	// if file is empty then it will display the error 
	if (outputFile == NULL)
	{
		//error
		printf("\nFile I/O Error");
	}
	// else it will take input and prints to file
	else
	{
		//userinput 
		printf("Enter your input:\n");

		while ((byte = fgetc(stdin)) != EOF)
		{
			if (bytesCount == 0)
			{
				// displaying dc.b in firstline of file
				if (currentLine == firstLine)
				{
					fprintf(outputFile, "dc.b\t");
					currentLine = afterFirstLine;
				}
				// if it is second line then again display of dc.b 
				else
				{
					fprintf(outputFile, "\ndc.b\t");
				}
				bytesCount = 0;
			}

			// displaying $ symbol in front of every byte 
			if (bytesCount == 0)
			{
				fprintf(outputFile, "$");
			}
			else
			{
				fprintf(outputFile, ", $");
			}

			bytesCount++;

			// storing the byte in variable Value
			sprintf(Value, "%X", byte);

			if (Value[1] == '\0')
			{
				Value[1] = Value[0];
				Value[0] = '0'; // displaying 0 when user press enter 
			}

			// displaying the value (converted text) 
			fprintf(outputFile, "%c", Value[0]);
			fprintf(outputFile, "%c", Value[1]);

			// if byte count become 16 it goes to second line
			if (bytesCount >= maxBytes)
			{
				bytesCount = 0;
			}

		}
		// data is written succesfully in file 
		printf("\n\nData Written Successfully.\n");
		fclose(outputFile);
	}
}


/*
* Function   :  convertAssembly()
* Parameter  :  char* inputFileName, char* outputFileName
* return     :  none
* Description:  this function convert standard input into assmebly
*               by taking input from file and again displaying output in file of extension .asm
*/
void convertAssembly(char* inputFileName, char* outputFileName)
{
	//variable declaration
	FILE* outputFile = NULL;
	FILE* inputFile = NULL;
	int bytesCount = 0;
	unsigned int byte;
	char Value[three] = { 0 };
	char record[lineSize] = "";
	char currentLine = firstLine;
	char* fileToRead = inputFileName + 2;
	char* fileToPrint = outputFileName + 2;
	int counter = 0;

	//creating a file for output 
	outputFile = fopen(fileToPrint, "wb");

	// reading input file 
	inputFile = fopen(fileToRead, "rb");

	// if file is empty then it will display the error
	if (outputFile == NULL && inputFile == NULL)
	{
		//error
		printf("File I/O Error");
	}
	else
	{
		// getting the filesize, length 
		while ((byte = fgetc(inputFile)) != EOF)
		{
			if (bytesCount == 0)
			{
				// displaying dc.b in firstline of file
				if (currentLine == firstLine)
				{
					fprintf(outputFile,"dc.b\t");
					currentLine = afterFirstLine;
				}
				// if it is second line then again display of dc.b 
				else
				{
					fprintf(outputFile,"\ndc.b\t");
				}
				bytesCount = 0;
			}

			// displaying $ symbol in front of every byte 
			if (bytesCount == 0)
			{
				fprintf(outputFile, "$");
			}
			else
			{
				fprintf(outputFile, ", $");
			}

			bytesCount++;

			// storing the byte in variable Value
			sprintf(Value, "%02X", byte);
			fwrite(Value, strlen(Value), 1, outputFile);


			// if byte count become 16 it goes to second line
			if (bytesCount >= maxBytes)
			{
				bytesCount = 0;
			}
			counter++;
		}

		// closing the file
		fclose(outputFile);

		printf("\nData Written Successfully\n");
	}
}

/*
* Function   :  convertAsmStdin()
* Parameter  :  void
* return     :  none
* Description:  this function convert standard input into assmebly
*               by taking input from console by displaying output in console
*/
void convertAsmStdout(void)
{
	//variable declaration
	FILE* outputFile = NULL;
	int bytesCount = 0;
	int byte = 0;
	char Value[three] = { 0 };
	char currentLine = firstLine;

	// creating new text file to store the input user
	outputFile = fopen("temp.txt", "wb");

	// if file is empty then it will display the error 
	if (outputFile == NULL)
	{
		//error
		printf("\nFile I/O Error");
	}
	// else it will take input and prints to file
	else
	{
		//userinput 
		printf("Enter your input:\n");

		while ((byte = fgetc(stdin)) != EOF)
		{
			if (bytesCount == 0)
			{
				// displaying dc.b in firstline of file
				if (currentLine == firstLine)
				{
					fprintf(outputFile, "dc.b\t");
					currentLine = afterFirstLine;
				}
				// if it is second line then again display of dc.b 
				else
				{
					fprintf(outputFile, "\ndc.b\t");
				}
				bytesCount = 0;
			}

			// displaying $ symbol in front of every byte 
			if (bytesCount == 0)
			{
				fprintf(outputFile, "$");
			}
			else
			{
				fprintf(outputFile, ", $");
			}

			bytesCount++;

			// storing the byte in variable Value
			sprintf(Value, "%X", byte);

			if (Value[1] == '\0')
			{
				Value[1] = Value[0];
				Value[0] = '0'; // displaying 0 when user press enter 
			}

			// displaying the value (converted text) 
			fprintf(outputFile, "%c", Value[0]);
			fprintf(outputFile, "%c", Value[1]);

			// if byte count become 16 it goes to second line
			if (bytesCount >= maxBytes)
			{
				bytesCount = 0;
			}

		}
		//closing the file
		fclose(outputFile);
	}

	printf("\n");
	printf("Output Result:\n");


	char record[lineSize] = "";
	FILE* fileToRead = NULL;


	// reading
	fileToRead = fopen("temp.txt", "r");


	// printing the content of file 
	while (fgets(record, lineSize, fileToRead))
	{
		printf("%s", record);
	}

	fclose(fileToRead);

	printf("\n");

	//deleting the file
	remove("temp.txt");

}
