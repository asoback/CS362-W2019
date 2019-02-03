/*
Andrew Soback
Card Test 1 
Assignment 3

Tests adventurer
Adventurer draws cards, discards them if they are not treasure cards, and keeps treasures, until two treasures have been drawn.

Test:
	Set player deck to be specific, know how many should be discarded, what will be gained
	Check the discard pile
	call updateCoin and make sure it is correct
*/

#include "dominion.h"
#include <stdio.h>

void assertTrue(int, int, int*);

int main(){
	int *failFlag;
	*failFlag = 0;

	int k[10] = {smithy, adventurer, council_room, village, minion, mine, cutpurse, sea_hag, tribute, ambassador};
  	struct gameState G;
  	initializeGame(2, k, 1, &G); //Two player game, with the above array of cards, random seed, and the gamestate struct

  	int currentPlayer = whoseTurn(&G);
  	// Set deck to be what I want
  	int i;
  	for (i = 0; i < MAX_DECK; i++){
  		G->deck[currentPlayer][i] = -1;
  	}
  	G->deck[currentPlayer][0] = estate;
  	G->deck[currentPlayer][1] = copper;
  	G->deck[currentPlayer][2] = estate;
  	G->deck[currentPlayer][3] = copper;
  	G->deck[currentPlayer][4] = copper;
  	
  	// Set hand to be what I want
  	for (i = 0; i < MAX_HAND; i++){
  		G->hand[currentPlayer][i] = -1;
  	}
  	G->hand[currentPlayer][0] = adventurer;

  	// Play Adventurer
  	playCard(0, 0, 0, 0, &failFlag); //First parameter is the position of the adventurer in the hand (0)

  	// Check discard pile
  	assertTrue(G->discardCount[currentPlayer] == 2, _LINE_, &failFlag);

  	// There should only be two cards in the hand, both coppers
  	assertTrue(G->handCount[currentPlayer] == 2, _LINE_, &failFlag);
  	assertTrue(G->hand[currentPlayer][0] == copper, _LINE_, &failFlag);
  	assertTrue(G->hand[currentPlayer][0] == copper, _LINE_, &failFlag);

  	if (*failFlag == 0) printf("TEST SUCCESSFULLY COMPLETED: kingdomCards() \n");
    else printf("TEST FAILED: kingdomCards() \n");

    // Free memory allocated to the test game
    free(&G);

	return 0;
}


void assertTrue(int value, int line, int* failFlag){
	if(value != 0){
		printf("Error on line %d\n", line);
		*failFlag = 1;
	}
}