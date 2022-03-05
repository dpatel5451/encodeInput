#include "asmAndSREC.h"




void printCC(FILE* outputFile, int srecWords)
{

	char value[3] = "";

	sprintf(value, "%d", srecWords);


	if (srecWords > 9)
	{
		fprintf(outputFile, "%c%c", value[0], value[1]);
	}
	
	if(srecWords <= 9)
	{
		fprintf(outputFile, "0%c", value[0]);
	}
}

void printAAAA(FILE* outputFile, int srecWords)
{

	char value[four] = "";

	sprintf(value, "%d", srecWords);


	if (srecWords >= 1000 && srecWords < 10000)
	{
		fprintf(outputFile, "%c%c%c%c", value[0], value[1], value[2], value[3]);
	}

	if (srecWords >= 100 && srecWords < 1000)
	{
		fprintf(outputFile, "0%c%c%c", value[0], value[1], value[2]);
	}

	if (srecWords >= 10 && srecWords < 100)
	{
		fprintf(outputFile, "00%c%c", value[0], value[1]);
	}

	if (srecWords >= 0 && srecWords < 10)
	{
		fprintf(outputFile, "000%c", value[0]);
	}
	
}


void convertSREC(char* inputFileName, char* outputFileName)
{
	FILE* inputFile = NULL;
	FILE* outputFile = NULL;
	unsigned int byte = 0;
	char Value[three] = "";
	int characters[maxBytes] = { 0 };
	int counter = 0;
	int counter1 = 0;
	unsigned char checkSUM = 0;

	char* fileToRead = inputFileName + 2;
	char* fileToPrint = outputFileName + 2;

	inputFile = fopen(fileToRead, "rb");
	outputFile = fopen(fileToPrint, "wb");

	if (inputFile == NULL || outputFile == NULL)
	{
		printf("\nFile I/O Error");
	}
	else
	{

		fprintf(outputFile, "S0140000446565702D476175726176E0");


		while ((byte = fgetc(inputFile)) != EOF)
		{

			characters[counter] = byte;
			counter++;

			if (counter == maxBytes)
			{
				fprintf(outputFile, "\nS1");
				int words = counter - three;
				printCC(outputFile, words);
				counter = 0;

				fprintf(outputFile, "%04X", counter1);

				while (counter != maxBytes)
				{

					checkSUM = checkSUM + characters[counter];
					sprintf(Value, "%02X", characters[counter]);

					fprintf(outputFile, Value);

					counter++;

				}

				words = three + counter1;
				checkSUM = words + maxBytes + checkSUM;

				checkSUM = ~checkSUM & 0xFF;

				counter = 0;

				sprintf(Value, "%02X", checkSUM);
				fprintf(outputFile, Value);

				counter1 = counter1 + maxBytes;
			}
		}
		if (counter > 0)
		{
			int currentCount = 0;
			checkSUM = 0;

			fprintf(outputFile, "\nS1");
			int words = counter + three;
			sprintf(Value, "%02X", words);

			fprintf(outputFile, Value);
			fprintf(outputFile, "%04X", counter1);

			while (currentCount != counter)
			{

				checkSUM = characters[currentCount] + checkSUM;

				sprintf(Value, "%02X", characters[currentCount]);
				fprintf(outputFile, Value);

				currentCount++;
			}
			
			words = counter + three;

			checkSUM = words + counter1 + checkSUM;	//+1 for checksum count, +2 for address
			checkSUM = ~checkSUM & 0xFF;

			sprintf(Value, "%02X", checkSUM);
			fprintf(outputFile, Value);

		}
		counter1 = counter1 + maxBytes;


		fprintf(outputFile, "\nS503");
		int divison = counter1 / maxBytes;
		printAAAA(outputFile, divison);

		checkSUM = three;
		checkSUM = checkSUM + divison;
		checkSUM = ~checkSUM & 0xFF;

		sprintf(Value, "%02X", checkSUM);

		fprintf(outputFile, Value);

		fprintf(outputFile, "\nS9030000FC");

		fclose(inputFile);
		fclose(outputFile);

		printf("Data Written Successfully\n");
	}


	

}



void stdinSREC(char* outputFileName)
{

	FILE* outputFile = NULL;
	unsigned int Byte = 0;
	char Value[three] = { 0 };
	int characters[maxBytes] = { 0 };
	int counter = 0;
	int counter1 = 0;
	unsigned char checkSUM = 0;

	char* fileToPrint = outputFileName + 2;

	outputFile = fopen(fileToPrint, "wb");

	if (outputFile == NULL)
	{
		printf("\nFile I/O error");
	}
	else
	{
		fprintf(outputFile, "S0140000446565702D476175726176E0");
		printf("Enter your input:\n");
		while ((Byte = fgetc(stdin)) != EOF)
		{

			characters[counter] = Byte;
			counter++;

			if (counter == maxBytes)
			{
				fprintf(outputFile, "\nS1");
				int words = counter - three;
				printCC(outputFile, words);
				counter = 0;

				fprintf(outputFile, "%04X", counter1);
				while (counter != maxBytes) 
				{

					checkSUM = checkSUM + characters[counter];
					sprintf(Value, "%02X", characters[counter]);

					fprintf(outputFile, Value);
					counter++;

				}

				words = counter1 + three;
				checkSUM = checkSUM + words + maxBytes;
				checkSUM = ~checkSUM & 0xFF;

				counter = 0;

				sprintf(Value, "%02X", checkSUM);

				fprintf(outputFile, Value);

				counter1 = counter1 + maxBytes;


			}

		}

		if (counter > 0)
		{
			int currentCount = 0;
			checkSUM = 0;
			fprintf(outputFile, "\nS1");
			int words = counter + three;
			sprintf(Value, "%02X", words);

			fprintf(outputFile, Value);

			fprintf(outputFile, "%04X", counter1);

			while (currentCount != counter) {

				checkSUM = checkSUM + characters[currentCount];
				sprintf(Value, "%02X", characters[currentCount]);

				fprintf(outputFile, Value);


				currentCount++;
			}

			words = counter + three;
			checkSUM = checkSUM + words + counter1;
			checkSUM = ~checkSUM & 0xFF;

			sprintf(Value, "%02X", checkSUM);
			fprintf(outputFile, Value);
		}

		counter1 = counter1 + maxBytes;

		fprintf(outputFile, "\nS503");

		int divison = counter1 / maxBytes;
		printAAAA(outputFile, divison);

		checkSUM = three;
		checkSUM = checkSUM + divison;
		checkSUM = ~checkSUM & 0xFF;

		sprintf(Value, "%02X", checkSUM);

		fprintf(outputFile, Value);


		fprintf(outputFile, "\nS9030000FC");

		fclose(outputFile);

		printf("\nData Written Successfully\n");
	}

	
}




void stdinoutSREC(void)
{
	FILE* outputFile = NULL;
	unsigned int Byte = 0;
	char Value[three] = { 0 };
	int characters[maxBytes] = { 0 };
	int counter = 0;
	int counter1 = 0;
	unsigned char checkSUM = 0;

	outputFile = fopen("temp.txt", "wb");

	if (outputFile == NULL)
	{
		printf("\nFile I/O error");
	}
	else
	{
		fprintf(outputFile, "S0140000446565702D476175726176E0");

		printf("Enter your input:\n");
		while ((Byte = fgetc(stdin)) != EOF)
		{


			characters[counter] = Byte;
			counter++;

			if (counter == maxBytes)
			{
				fprintf(outputFile, "\nS1");
				int words = counter - three;
				printCC(outputFile, words);
				counter = 0;

				fprintf(outputFile, "%04X", counter1);
				while (counter != maxBytes) {

					checkSUM = checkSUM + characters[counter];
					sprintf(Value, "%02X", characters[counter]);

					fprintf(outputFile, Value);
					counter++;

				}
				words = three + counter1;
				checkSUM = checkSUM + words + maxBytes;
				checkSUM = ~checkSUM & 0xFF;

				counter = 0;

				sprintf(Value, "%02X", checkSUM);

				fprintf(outputFile, Value);

				counter1 = counter1 + maxBytes;


			}

		}

		if (counter > 0)
		{
			int currentCount = 0;
			checkSUM = 0;
			fprintf(outputFile, "\nS1");
			int words1 = counter + three;
			sprintf(Value, "%02X", words1);

			fprintf(outputFile, Value);

			fprintf(outputFile, "%04X", counter1);

			while (currentCount != counter) {

				checkSUM = checkSUM + characters[currentCount];
				sprintf(Value, "%02X", characters[currentCount]);

				fprintf(outputFile, Value);


				currentCount++;
			}

			words1 = counter + three;
			checkSUM = checkSUM + words1 + counter1;
			checkSUM = ~checkSUM & 0xFF;

			sprintf(Value, "%02X", checkSUM);
			fprintf(outputFile, Value);
		}

		counter1 = counter1 + maxBytes;

		fprintf(outputFile, "\nS503");

		int divison = counter1 / maxBytes;
		printAAAA(outputFile, divison);

		checkSUM = three;
		checkSUM = checkSUM + divison;
		checkSUM = ~checkSUM & 0xFF;

		sprintf(Value, "%02X", checkSUM);

		fprintf(outputFile, Value);


		fprintf(outputFile, "\nS9030000FC");


		fclose(outputFile);
	}


	printf("\n");
	printf("Output Result:\n");

	char record[120] = "";
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