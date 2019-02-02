/*
Andrew Soback
Unit Test 3 
Assignment 3

Tests updateCoins() function
updateCoins takes an int for player number (0 or 1 for two player game), a gameState, and an int for bonus
it always returns 0, (Though there isnt much use for this, it may be best to change to a void function in the future)

It makes changes to the struct gamestate "coins" variable
To test:
	Make changes to the players hand, and compare expected vs actual 'coins' value
	change the "bonus" value, and ensure that it is correctly updated.
	switch players, and manually set the other players hand. This is to make sure that nothing carries over from the prev. player
*/

#include "dominion.h"
#include <stdio.h>

void assertTrue(int, int, int*);

int main(){
	int *failFlag;
	*failFlag = 0;

	//Set up game to use for testing
	struct gameState G;
  	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    int numplayers = 2;

    int res = initializeGame(numplayers, k, 2, &G);
    assertTrue(res, _LINE_, &failFlag);

    // 1st test: Check if given hand is correct
    int currentPlayer = G->whoseTurn;
    int c, s, g; //copper, silver, and gold counts.

    updateCoins(currentPlayer, G, 0);
    int i;
    for (i = 0; i < G->handCount[currentPlayer]; i++){
    	if (G->hand[currentPlayer][i] == copper) {c++;}
      	else if (G->hand[currentPlayer][i] == silver) {s++;}
      	else if (G->hand[player][i] == gold) {g++;}
    }
    //copper + silver + gold minus G->coins should equal 0 if correct
    assertTrue( c + (s*2) + (g*3) - G->coins, _LINE_, &failFlag);

    // 2nd test: Add cards, check that coins are correct
    for (i = 0; i < 5; i++){
    	G->hand[currentPlayer][i] = gold; //5 golds equals 15 'coins'
    }
    updateCoins(currentPlayer, G, 0);
    assertTrue(G->coins - 15, _LINE_, &failFlag);

    // 3rd Test: Change bonus value, and make sure that it is still correct
    updateCoins(currentPlayer, G, 3);
    assertTrue(G->coins - 18, _LINE_, &failFlag);

    // 4th test: Switch players, draw 5 cards coppers, check to make sure coins are correct after updateCoins() called
    currentPlayer = 1;
    for (i = 0; i < 5; i++){
    	G->hand[currentPlayer][i] = copper; //5 copper equals 5 'coins'
    }
    //Important: function relies on the gamestate storing the number of cards. If the number of cards in a hand is changed, this also needs to change
    G->handCount[currentPlayer] = 5; 
    updateCoins(currentPlayer, G, 0);
    assertTrue(G->coins - 5, _LINE_, &failFlag);

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