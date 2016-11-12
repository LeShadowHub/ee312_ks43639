#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

//palindrome
int index = 0;
int left = 0;
int once = 0;
int totalIndex = 0;
int pos = 0;

//palindrom func- check if palindrome
int check(char *input, int leftIndex, int rightIndex) {

	//base case
	if (leftIndex >= rightIndex) {
		return 1;
	}
	//recursion
	if (input[leftIndex] == input[rightIndex]) {
		return check(input, leftIndex + 1, rightIndex - 1);
	}
	index--;
	return 0;
}

//palindrome func- print string
void printAll(char *input) {

	char str[100];

	strncpy(str, input + left, (index + 1) - left);
	str[(index + 1) - left] = '\0';
	printf("%s", str);

	printf(" ");
}

//parenthesis func
void printParens(int n, int openParen, int closeParen) {
	static char str[MAX_SIZE];

	if (closeParen == n) {
		printf("%s \n", str);
		return;
	}
	else {
		if (openParen > closeParen) {
			str[pos] = ')';
			pos++;
			printParens(n, openParen, closeParen + 1);
			pos--;
		}
		if (openParen < n) {
			str[pos] = '(';
			pos++;
			printParens(n, openParen + 1, closeParen);
			pos--;
		}
	}
}

void generateAllMatchedParens(int n) {
	if (n > 0) {
		pos = 0;
		printParens(n, 0, 0);
		return;
	}
}

void generateAllPalindromicDecompositions(char str[]) {
	if (once == 0) {
		totalIndex = strlen(str);
		once = 1;
		index = totalIndex - 1;
	}

	//base case
	if (check(str, left, index) == 1) {
		printAll(str);
		left = (index + 1);
		index = (totalIndex - 1);
	}
	//recursion
	if(left != totalIndex) {
		generateAllPalindromicDecompositions(str);
	}

	//finish 
	if (left == totalIndex) {
		//printAll(str);
		printf("\n");
		index = 0;
		left = 0;
		once = 0;
	}
}
