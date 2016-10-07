#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

//#define INPUT_FILE "assignment-2.c"
//#define OUTPUT_FILE "outputfile.txt"
#define BEGIN_FCN {
#define END_FCN }
#define TRUE 1
#define FALSE 0

int totalFunc = 0;
int totalLOC = 0;
int linesOfCode = 0;
int reCount = FALSE;
int lineCommentOn = FALSE;
int multCommentOn = FALSE;
int quoteOn = FALSE;
int quoteTrack = 2;
int funcStart = FALSE;

//search for number of lines of codes
void findLOC(char *fpIn, char *line) {

	if (reCount == TRUE) {
		linesOfCode = 0;
		reCount = FALSE;
	}

	//loop through line for codes
	for (int i = 0; i < strlen(line); i++) {

		//Finding comments
		if (line[i] == '/') {
			if (line[i + 1] == '/') {
				lineCommentOn = TRUE;
				break;
			}
			if (line[i + 1] == '*') {
				multCommentOn = TRUE;
			}
		}

		//Finding quotes
		if (line[i] == '"') {
			if ((quoteTrack % 2) == 0) {
				quoteOn = TRUE;
				quoteTrack++;
			}
			else {
				quoteOn = FALSE;
				quoteTrack++;
			}	
		}
		
		//End comment
		if (line[i] == '*' && line[i + 1] == '/') {
			multCommentOn = FALSE;
		}

		//check
		//printf("%c\n", line[i]);

		//If no comment or quotes
		if ((multCommentOn == FALSE) && (quoteOn == FALSE) && (line[i] == ';')) {
			linesOfCode++;
			totalLOC++;
		}
	}
	//check
	//printf("%d\n", linesOfCode);
	lineCommentOn = FALSE;
}

//find and print function name
void findFunc(char *fpIn, char *fwIn, char *line) {

	int counter = 0;
	int lineCounter = 0;
	char func[256];

	while (line[lineCounter] != ' ') {
		lineCounter++;
	}
	lineCounter++;

	while ((counter != 256) && (line[lineCounter] != '(')) {
		func[counter] = line[lineCounter];
		counter++;
		lineCounter++;
	}
	
	func[counter] = '\0';
	//check
	//printf("%s\n", func);
	
	//print char by char
	for (int i = 0; i != strlen(func); i++) {
		putc(func[i], fwIn);
		putchar(func[i]);
	}
	//fprintf(fwIn, "\t\t");
	//printf("%d\n", strlen(func));

	//Fix tabing
	if (strlen(func) < 40) {
		//Testing for perfection
		/*if (strlen(func) % 2 == 1) {
			for (int j = (22 - strlen(func)); j >= 0; j -= 2) {
				fprintf(fwIn, "\t");
			}
		}
		else {
			for (int j = (22 - strlen(func)); j >= 0; j -= 3) {
				fprintf(fwIn, "\t");
			}
			fprintf(fwIn, "\t\t");
		}*/

		//Works for most cases
		for (int j = (40 - strlen(func)); j >= 0; j -= 8) {
			fprintf(fwIn, "\t");
			printf("\t");
		}
	}
	else {
		fprintf(fwIn, "\t");
		printf("\t");
	}
}

int main(void) {

	//int Bcounter = 0;
	//int Ecounter = 0;
	int checkBE = 1;
	int noFunc = TRUE;
	int done = FALSE;
	char *Bstr = "BEGIN_FCN";
	char *Estr = "END_FCN";

	char temp[256];
	char holder[256];
	char fileNameIn[80];
	char fileNameOut[80];
	int hCounter = 0;
	//char *line;

	while (done == FALSE) {

		//reset all
		totalFunc = 0;
		totalLOC = 0;
		linesOfCode = 0;
		reCount = FALSE;
		lineCommentOn = FALSE;
		multCommentOn = FALSE;
		quoteOn = FALSE;
		quoteTrack = 2;
		funcStart = FALSE;

		FILE *fp;
		printf("Enter file name to read from(Enter STOP to exit): ");
		gets(fileNameIn);

		//check STOP
		if (fileNameIn[0] == 'S') {
			if (fileNameIn[1] == 'T') {
				if (fileNameIn[2] == 'O') {
					if (fileNameIn[3] == 'P') {
						done = TRUE;
						break;
					}
				}
			}
		}
		//printf("File name entered is: %\n", fileNameIn);
		fp = fopen(fileNameIn, "r");

		if (fp == NULL) {
			printf("Cannot open %s\n", fileNameIn);
			getchar();
			exit(EXIT_FAILURE);
		}

		FILE *fw;
		printf("Enter file name to write to: ");
		gets(fileNameOut);
		//printf("File name entered is: %\n", fileNameOut);
		fw = fopen(fileNameOut, "w");

		if (fw == NULL) {
			printf("Cannot open %s\n", fileNameOut);
			getchar();
			exit(EXIT_FAILURE);
		}

		//File heading and name
		fprintf(fw, "File Counting Summary Table\n");
		fprintf(fw, "\nFilename: %s\n", fileNameIn);
		fprintf(fw, "\nFunction Name\t\t\t# Lines of Code\n\n");

		printf("File Counting Summary Table\n");
		printf("\nFilename: %s\n", fileNameIn);
		printf("\nFunction Name\t\t\t# Lines of Code\n\n");

		//Check if BEGIN match END in all file
		while (fgets(temp, 256, fp) != NULL) {

			/*if (strstr(temp, Bstr) == NULL) {
				line = *temp;
			}*/
			hCounter = 0;
			if (strstr(temp, Bstr) != NULL) {
				//printf("%s", strstr(temp, Bstr));
				//Bcounter++;
				totalFunc++;
				noFunc = FALSE;
				if (checkBE != 1) {
					printf("Mis-matched BEGIN-END in file");
					getchar();
					exit(EXIT_FAILURE);
				}
				//check
				//printf("BEGIN FOUND\n");
				funcStart = TRUE;
				findFunc(fp, fw, holder);
				checkBE = 0;
			}
			if (strstr(temp, Estr) != NULL) {
				//printf("%s", strstr(temp, Estr));
				//Ecounter++;
				if (checkBE != 0) {
					printf("Mis-matched BEGIN-END in file");
					getchar();
					exit(EXIT_FAILURE);
				}
				funcStart = FALSE;

				//print LoC to file
				fprintf(fw, "%d\n", linesOfCode);
				printf("%d\n", linesOfCode);

				reCount = TRUE;
				checkBE = 1;
			}

			//Hold line prior to BEGIN
			while (hCounter != 256) {
				holder[hCounter] = temp[hCounter];
				hCounter++;
			}

			//Start search for lines of code
			if (funcStart == TRUE) {
				findLOC(fp, holder);
			}
		}

		if (noFunc == TRUE) {
			printf("No Functions found in file");
			getchar();
			exit(EXIT_FAILURE);
		}
		if (checkBE == 0) {
			printf("Mis-matched BEGIN-END in file(Missing END)");
			getchar();
			exit(EXIT_FAILURE);
		}
		//printf("BEGIN: %d\n", Bcounter);
		//printf("END: %d", Ecounter);

		//print total func and loc
		fprintf(fw, "\nTotal Function: %d\n", totalFunc);
		fprintf(fw, "Total Lines of Code: %d\n", totalLOC);

		printf("\nTotal Function: %d\n", totalFunc);
		printf("Total Lines of Code: %d\n", totalLOC);

		fclose(fw);
		fclose(fp);
	}
	return 0;
}