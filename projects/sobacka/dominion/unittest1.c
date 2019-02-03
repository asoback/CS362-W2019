/*
Andrew Soback
Unit Test 1 
Assignment 3

Tests kingdomCards() function
This function takes as arguments 10 cards, represented as integers.
It allocates memory for those 10 cards, and returns a pointer to an integer array of them. (Pointer should be freed)
It performs no error checking, which could be worthwhile to add in the future if necessary.

Test that a pointer is returned, and is not null
Test that it contains 10 integers, that are the same as expected
*/

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

void assertTrue(int, int, int*);

int main(){
	int *failFlag;
	*failFlag = 0;

	int a[10]; //Array of 10 cards
	int *p = NULL; //Pointer to capture returned data from function
	//Set card (int) values
	for (int i = 0; i < 10; i++){
		a[i] = i;
	}

	//Begin testing
//	p = kingdomCards(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);

 	 kingdomCards(1,      1,    1,    1,    1,    1,    1,    1,    1,    1);

	//Test that P is not null
	assertTrue(p!=NULL, __LINE__, failFlag);

	//Test values to be as expected
	for (int i = 0; i < 10; i++){
		assertTrue(a[i] == p[i], __LINE__, failFlag);
	}

	//Release dynamically allocated memory by kindomCards()
	free(p);

	if (*failFlag == 0) printf("TEST SUCCESSFULLY COMPLETED: kingdomCards() \n");
    else printf("TEST FAILED: kingdomCards() \n");

	return 0;
}

void assertTrue(int value, int line, int* failFlag){
	if(value != 0){
		printf("Error on line %d\n", line);
		*failFlag = 1;
	}
}
