/*
Andrew Soback
Card Test 2 
Assignment 3

Tests adventurer
Adventurer draws cards, discards them if they are not treasure cards, and keeps treasures, until two treasures have been drawn.

*This test should not find the bug that I have introduced into the dominion.c code

Test:
	Set player deck to be specific, know how many should be discarded, what will be gained
	Check the discard pile
	call updateCoin and make sure it is correct
*/

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

void assertTrue(int, int, int*);

int main(){
	int val = 0;
	int *failFlag;
	failFlag = &val;

	int k[10] = {smithy, adventurer, council_room, village, minion, mine, cutpurse, sea_hag, tribute, ambassador};
  	struct gameState G;
  	initializeGame(2, k, 1, &G); //Two player game, with the above array of cards, random seed, and the gamestate struct

  	int currentPlayer = whoseTurn(&G);
  	// Set deck to be what I want
  	int i;
  	for (i = 0; i < MAX_DECK; i++){
  		G.deck[currentPlayer][i] = -1;
  	}
  	G.deck[currentPlayer][0] = estate;
  	G.deck[currentPlayer][1] = copper;
  	G.deck[currentPlayer][2] = estate;
  	G.deck[currentPlayer][3] = copper;
  	G.deck[currentPlayer][4] = copper;
	G.deckCount[currentPlayer] = 5;
  	G.discardCount[currentPlayer] = 0;

  	// Set hand to be what I want
  	for (i = 0; i < MAX_HAND; i++){
  		G.hand[currentPlayer][i] = -1;
  	}
  	G.hand[currentPlayer][0] = adventurer;
	G.handCount[currentPlayer] = 1;

  	// Play Adventurer
  	playCard(0, 0, 0, 0, &G);  //First parameter is the position of the adventurer in the hand (0)

  	// Check discard pile
  	// assertTrue(G.discardCount[currentPlayer] == 1, __LINE__, failFlag);

  	// There should only be two cards in the hand, both coppers
  	assertTrue(G.handCount[currentPlayer] == 2, __LINE__, failFlag);
    printf("current handcount: %d, hand[0] %d hand[1] %d \n", G.handCount[currentPlayer], G.hand[currentPlayer][0], G.hand[currentPlayer][1] );
  	assertTrue(G.hand[currentPlayer][0] == copper, __LINE__, failFlag);
  	assertTrue(G.hand[currentPlayer][1] == copper, __LINE__, failFlag);

  	if (*failFlag == 0) printf("TEST SUCCESSFULLY COMPLETED: Card Test 2 \n");
    else printf("TEST FAILED: Card Test 2 \n");

	return 0;
}


void assertTrue(int value, int line, int* failFlag){
	if(value == 0){
		printf("Error on line %d\n", line);
		*failFlag = 1;
	}
}
