#include <stdio.h>


/*
* return 1 if the ASCII interpretation of
* c is an upper case letter.
* return 0 otherwise
*/
int isUpperCase(char c) {
	if (c >= 'A' && c <= 'Z') {
		return 1;
	}
	else {
		return 0;
	}
}

/*
* return 1 if the ASCII interpretation of
* c is a lower case letter.
* return 0 otherwise
*/
int isLowerCase(char c) {
	if (c >= 'a' && c <= 'z') {
		return 1;
	}
	else {
		return 0;
	}
}

/*
* return 1 c is an Alphabet.
* return 0 otherwise
*/
int isAlphabet(char c) {
	return isUpperCase(c) || isLowerCase(c);
}

/*
* if the ASCII interpretation of c is a letter, then
* return a number between 0 and 25 indicating which letter of
* the alphabet c represents.  For example, if c is the ASCII
* encoding for 'A', then we should return 0.  If c is the
* ASCII encoding for 'e', then we should return 4.
* if the ASCII interpretation of c is not a letter, then
* return -1.
*/
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

/*
* assumes i is between 0 and 25 inclusive
*/
char int2UpperCase(int i) {
	char c = 'A' + i;
	return c;
}

/*
* assumes i is between 0 and 25 inclusive
*/
char int2LowerCase(int i) {
	char c = 'a' + i;
	return c;
}

/*
* This function takes in a message and computes the frequencies of all the alphabets
*/
void buildHistogram(char message[], int messageLength, int histogram[], int histogramLength) {

	int index = 0;
	int temp = 0;

	while (index < histogramLength) {
		histogram[index] = 0;
		index++;
	}
	index = 0;

	while(index < messageLength) {
		if (isAlphabet(message[index]) == 1) {
			temp = ASCII2Int(message[index]);
			histogram[temp] += 1;
			index++;
		}
		else {
			index++;
		}
	}
}

/*
* This function computes the maximum value in an array and returns the index location\
* for which the maximum value occured
*/

int maxIndex(int myArray[], int arrayLength) {

	int max = 0;
	int index = 0;

	for (int i = 0; i < arrayLength; i++) {
		if (myArray[i] > max) {
			max = myArray[i];
			index = i;
		}
	}
	return index;
}

/*
* Encrypt the string s using the rotation cypher
* Each letter in s should be shifted "shift" letters to the
* right.  For example, if "shift" is 2, then "a zebra" should be
* changed to "c bgdtc".  Note that when shifting past the end
* of the alphabet, we wrap around again to a.
*
* Only change the letters in s.  Do not change spaces, punctuation
* or numbers in s.
* For full credit, you should keep upper case letters as
* upper case, and leave lower case letters as lower case.  So, if
* s had been the string "a ZeBra", you should change s to be
* "c BgDtc".
*/
void encrypt(char message[], int messageLength, int shift) {
	
	int index = 0;

	while (index < messageLength) {
		if (isAlphabet(message[index]) == 1) {
			if (isUpperCase(message[index]) == 1) {
				message[index] = ((message[index] - 65 + shift) % 26) + 65;
				index++;
			}
			else if(isLowerCase(message[index])){
				message[index] = ((message[index] - 97 + shift) % 26) + 97;
				index++;
			}
		}
		else {
			index++;
		}
	}
}

/*
* return a number between 0 and 25 indicating which letter
* of the alphabet is most common in the string s 
*/
int mostFrequentLetter(char message[], int messageLength) {
	/*
	* Build the histogram and get the index of most frequent alphabet
	*/
	int alphaLength = 26;
	int myHistogram[26] = {0};
	//int counter = 0;
	int mostCommon = 0;

	buildHistogram(message, messageLength, myHistogram, alphaLength);

	//Testing
	//Find all most frequent
	int max = 0;
	int hold = 0;
	int index = 0;
	int counter = 0;
	int allFreq[26] = {0};

	for (int i = 0; i < alphaLength; i++) {
		if (myHistogram[i] > max) {
			hold = i;
			max = myHistogram[i];
		}
	}

	for (int i = 0; i < alphaLength; i++) {
		if (myHistogram[i] == max) {
			allFreq[index] = i;
			index++;
			counter++;
		}
	}

	//search through message for first occurance
	for (int j = 0; j < messageLength; j++) {
		for (int k = 0; k < counter; k++) {
			if (ASCII2Int(message[j]) == allFreq[k]) {
				mostCommon = allFreq[k];
				k = counter;
				j = messageLength;
			}
		}
	}
	//End

	//mostCommon = maxIndex(myHistogram, alphaLength);
	return mostCommon;
}

void decrypt(char cypher[], int cypherLength, int common) {
	int shift = 0;
	int encommon = 0;

	encommon = mostFrequentLetter(cypher, cypherLength);
	shift = common - encommon;
	if (shift < 0) {
		shift += 26;
	}
	encrypt(cypher, cypherLength, shift);
}


