/*
* assignment5.c
* SpellCheck
*/

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
*
* Many students find it helpful to declare global variables (often arrays). You are welcome to use
* globals if you find them helfpul. Global variables are by no means necessary for this project.*/

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
* exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
* You are expected to use reasonable programming style. I strongly encourage you to avoid big functions
* (while there are always exceptions, a good rule of thumb is about 15 lines in a function).
* So, plan on implementing spellCheck by writing two or three other "support functions" that
* help make the actual spell checking easier for you.
* There are no explicit restictions on using functions from the C standard library. However,
* for this project you should avoid using functionality from the C++ standard libary. You will
* almost certainly find it easiest to just write everything you need from scratch!*/

//TODO:

/*return 1 if the ASCII interpretation of
* c is an upper case letter.
* return 0 otherwise*/
int isUpperCase(char c) {
	if (c >= 'A' && c <= 'Z') {
		return 1;
	}
	else {
		return 0;
	}
}

/*return 1 if the ASCII interpretation of
* c is a lower case letter.
* return 0 otherwise*/
int isLowerCase(char c) {
	if (c >= 'a' && c <= 'z') {
		return 1;
	}
	else {
		return 0;
	}
}

/*return 1 c is an Alphabet.
* return 0 otherwise*/
int isAlphabet(char c) {
	return isUpperCase(c) || isLowerCase(c);
}

/*if the ASCII interpretation of c is a letter, then
* return a number between 0 and 25 indicating which letter of
* the alphabet c represents.  For example, if c is the ASCII
* encoding for 'A', then we should return 0.  If c is the
* ASCII encoding for 'e', then we should return 4.
* if the ASCII interpretation of c is not a letter, then
* return -1.*/
int ASCII2Int(char c) {
	if (isUpperCase(c)) {
		return c - 'A';
	}
	else if (isLowerCase(c)) {
		return c - 'a';
	}
	else {
		return -1;
	}
}

//assumes i is between 0 and 25 inclusive
char int2LowerCase(int i) {
	char c = 'a' + i;
	return c;
}

int compare(int word[], char dictionary[], int tcount) {
	int index = 0;
	int match = 0;
	int counter = 0;
	int potential = FALSE;

	//while file has strings
	while (dictionary[index] != 0) {
		//seach line by line
		while ((dictionary[index] != '\n') && (dictionary[index] != 0)) {

			if(counter < tcount) {
				if (ASCII2Int(dictionary[index]) == word[counter]) {
					match++;
				}
			}
			if (match == tcount) {
				potential = TRUE;
			}
			index++;
			counter++;
		}
		//if match word in character and number of
		if ((counter == match) && (potential == TRUE)) {
			return 0;
		}
		index++;
		counter = 0;
		match = 0;
	}
	return 1;
}

void spellCheck(char article[], char dictionary[]) {
	int index = 0;
	int tindex = 0;
	//int count = 0;
	int temp[50] = { 0 };
	int tcount = 0;
	int word = FALSE;
	int end = FALSE;
	int check = 0;
	int doublecheck = 0;

	//Testing
	char *allchar;
	int total = 0;
	int allcount = 0;
	while (article[total] != 0) {
		total++;
	}
	allchar = calloc(total, sizeof(char));
	//End testing

	while ((article[index] != 0) && (end == FALSE)) {
		while(isAlphabet(article[index]) == 1) {
			word = TRUE;
			temp[tindex] = ASCII2Int(article[index]);
			tcount++;
			tindex++;
			index++;
			if (article[index] == 0) {
				end = TRUE;
			}
		}

		if (tcount < 2) {
			word = FALSE;
		}
		if (word == TRUE) {
			check = compare(temp, dictionary, tcount);
			word = FALSE;
		}
		if (check == 1) {
			//Testing for check
			doublecheck = compare(temp, allchar, tcount);
			//End testing

			if (doublecheck == 1) {
				for (int i = 0; i < tcount; i++) {
					printf("%c", int2LowerCase(temp[i]));
					allchar[allcount] = int2LowerCase(temp[i]);
					allcount++;
				}
				printf("\n");
				allchar[allcount] = '\n';
				allcount++;
			}
			tcount = 0;
			tindex = 0;
			check = 0;
		}
		tcount = 0;
		tindex = 0;
		index++;
	}
}





