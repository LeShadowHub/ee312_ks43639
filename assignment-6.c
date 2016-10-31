#include <stdlib.h>
#include <stdio.h>

//Initialize the starting point of the array
void init_heap(char heap[]) {
	
	//start heap to 2496
	int *p = (int*)(&heap[0]);
	*p = 2496;
	//int check = (int)*p;
	//printf("%d\n", check);

	//End heap to 2496
	int *s = (int*)(&heap[9992]);
	*s = 2496;
	//check = (int)*s;
	//printf("%d\n", check);
}

//Change bytes to words
int byteToword(int numbytes) {
	int temp = (int)((double)numbytes / 4 + 0.9);
	//printf("%d", temp);
	return temp;
}

//Allocate requested memory
char *my_malloc(char heap[], int numbytes) {
	printf("My malloc called\n");

	if (numbytes == 0) {
		printf("Nothing was allocated");
		return NULL;
	}

	/*****************************/
	int index = 9992;
	//int counter = 0;
	int total = 2496;
	int *temp;
	int setMeta = 0;
	int spaceAvail = 0;
	int oneMetaOffset = 8;
	int twoMetaOffset = 16;
	int test = 0;
	char *botMetaData;

	//get positions of bottom total metadata
	//counter = *(int*)(&heap[0]);
	for (int i = 1; i < 10000; i++) {
		if (*(int*)(&heap[i]) == *(int*)(&heap[0])) {
			botMetaData = &heap[i];
			break;
		}
	}

	//pointer to heap of index
	temp = (int*)(&heap[index]);
	//printf("%d\n", *temp);
	//test = *(int*)(&heap[index]);
	//printf("%d\n", test);

	//Check to see if negative or less than needed bytes
	while ((*temp < 0) || ((*temp) < (byteToword(numbytes)))) {
		//check if bytes over total;
		if (byteToword(numbytes) > total) {
			printf("Sorry nothing is available!\n");
			return NULL;
		}
		//decrease total for checking
		if (*temp < 0) {
			total += *temp;
			if (byteToword(numbytes) > total) {
				printf("Sorry nothing is available!\n");
				return NULL;
			}
		}
		//change positive to negative 
		//jump numbytes plus two metadata offset 
		if (*(int*)(&heap[index]) >= 0) {
			index = index - (4 * (*(int*)(&heap[index]))) - twoMetaOffset;
		}
		else {
			index = index + (4 * (*(int*)(&heap[index]))) - twoMetaOffset;
			temp = (int*)(&heap[index]);
		}
	}

	//If there is enough space
	if (*temp >= byteToword(numbytes)) {
		if (temp == botMetaData) {
			setMeta = 1;
			//printf("set confirm\n");
		}
		//printf("Space left\n");

		//check to see if need to split
		spaceAvail = ((*temp + 4) - (byteToword(numbytes) + 4));
		if (spaceAvail < 5) {
			//printf("return all\n");
			index -= (4 * (*temp));
			*temp = -(*temp);
			*(int*)(&heap[index - 8]) = *temp;
			//printf("%d\n", *(int*)(&heap[index - 8]));

			return &heap[index];
		}

		//set bottom metadata
		*(int*)(&heap[index]) = -(byteToword(numbytes));
		//printf("%d\n", *(int*)(&heap[index]));
		//index up numbytes
		index -= (4 * byteToword(numbytes) + oneMetaOffset);
		//set top metadata
		*(int*)(&heap[index]) = -(byteToword(numbytes));

		//set TOTAL metadata if need to
		if ((index != 0) && (setMeta == 1)) {
			//top metadata
			*(int*)(&heap[0]) -= (byteToword(numbytes) + 4);
			//printf("%d\n", *(int*)(&heap[0]));
			//bottom metadata
			*(int*)(&heap[index - 8]) = *(int*)(&heap[0]);
			//printf("%d\n", *(int*)(&heap[index - 8]));
		}
		else {
			*(int*)(&heap[index - 8]) = spaceAvail - 4;
			//printf("split meta\n");
			//printf("%d\n", *(int*)(&heap[index - 8]));
			int save = index;
			save -= ((4 * (spaceAvail - 4)) + twoMetaOffset);
			*(int*)(&heap[save]) = spaceAvail - 4;
		}
		//heap[9984] = 5;
		return &heap[index + 8];
	}

	//If nothing is done, no space
	printf("Sorry nothing is available!\n");
	return NULL;
}

//Deallocate requested memory
void my_free(char slab[], char *p) {

	//printf("My free called\n");

	int oneMetaOffset = 8;
	int twoMetaOffset = 16;
	int index = 9992;
	int wordData = 0;
	int sumWord = 0;
	int counter = 0;
	char *hold;
	//printf("%d", *(int*)(p));

	//free top, bottom metadata
	*(int*)(p - 8) = -(*(int*)(p - 8));

	wordData = *(int*)(p - 8);
	*(int*)(p + (wordData * 4)) = *(int*)(p - 8);

	//checking output
	int temp = (int)(*(p - 8));
	int temp2 = (int)(*(p + (wordData * 4)));
	//printf("%d %d\n", temp, temp2);

	//grouping blocks together
	while (index > 0) {
		while ((*(int*)(&slab[index]) > 0) && (index >0)) {
			sumWord += *(int*)(&slab[index]);
			index -= ((*(int*)(&slab[index]) * 4) + twoMetaOffset);
			if (*(int*)(&slab[index]) > 0) {
				counter++; 
				sumWord += 4; 
			}
		}
		if (counter > 0) {
			*(int*)(&slab[index + oneMetaOffset]) = sumWord;
			*(int*)(&slab[index + twoMetaOffset + (sumWord * 4)]) = sumWord;
			counter = 0;
		}
		if (index > 0) {
			index += ((*(int*)(&slab[index]) * 4) - twoMetaOffset);

		}
	}

	
}
