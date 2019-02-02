/*
Andrew Soback
Unit Test 4
Assignment 3

Unit test 4 tests the whoseTurn() function

This function takes a pointer to a gamestate struct as an argument
it retuns an int, which represents the player number (0 or 1 in a two person game)

To test, make sure that who's turn is correct, compared to what is expected.
*/


#include "dominion.h"
#include <stdio.h>

void assertTrue(int, int, int*);

int main(){
	//Set up game to use for testing
	struct gameState G;
  	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    int numplayers = 2;

    int res = initializeGame(numplayers, k, 2, &G);
    assertTrue(res, _LINE_, &failFlag);

    // initializeGame sets whoseTurn to 0
    // check to make sure this is true
    assertTrue(whoseTurn(&G), _LINE_, &failFlag);

    // Set whoseTurn to 1, and check that the correct value was returned by the funciton
    G->whoseTurn = 1;
    assertTrue(whoseTurn(&G) -1, _LINE_, &failFlag);

    // Free memory allocated to the test game
    free(&G);

	if (*failFlag == 0) printf("TEST SUCCESSFULLY COMPLETED\n");
    else printf("TEST FAILED\n");    

	return 0;
}

void assertTrue(int value, int line, int* failFlag){
	if(value != 0){
		printf("Error near line %d\n", line);
		*failFlag = 1;
	}
}
