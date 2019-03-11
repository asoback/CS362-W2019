/*
Andrew Soback
Card Test 1 
Assignment 3

Tests smithy
Smithy gains the player 3 cards from their deck to their hand, when played.

Should fail due to bug introduced for assignment 2. Incorrect number of cards

Test:
	Make sure the card count in hand is 2 more than before (+3 -1 for the played smithy card)
	Make sure the deck comtains two less cards than before

Testing that the cards came from the deck and are now in the hand should be done on the drawCard() function

*/

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

void assertTrue(int, int, int*);

int main(){
	int val = 0;
	int *failFlag;
	failFlag = &val;
	int i;

	//Variables to save for comparison against gamestate
	int currentPlayer, handCount, deckCount, playedCardCount, smithyPosition;

	int k[10] = {smithy, adventurer, council_room, village, minion, mine, cutpurse, sea_hag, tribute, ambassador};
  	struct gameState G;
  	initializeGame(2, k, 1, &G); //Two player game, with the above array of cards, random seed, and the gamestate struct

  	currentPlayer = whoseTurn(&G);

  	// Get hand count
  	handCount = G.handCount[currentPlayer];

  	// Get deck count
  	deckCount = G.deckCount[currentPlayer];

	// Add a Smithy to hand
  	gainCard(smithy, &G, 2, currentPlayer);  // 3rd parameter is toFlag, 2 equals hand

  	// Get smithy position
  	for(i = 0; i <= handCount; i++){
  		if( G.hand[currentPlayer][i] == smithy){
  			smithyPosition = i;
  			break;
  		}
  	}

  	// Play smithy
  	playCard(smithyPosition, 0, 0, 0, &G);

  	// Testing starts here...

  	// Check that the number of cards in hand is 3 more than previously
  	assertTrue(G.handCount[currentPlayer] == handCount + 3, __LINE__, failFlag);

  	// Check deck contains 3 less than before
  	assertTrue(G.deckCount[currentPlayer] == deckCount - 3, __LINE__, failFlag);
  	
  	// Check that smithy has been played
  	assertTrue(G.playedCards[0] == smithy, __LINE__, failFlag);

	if (*failFlag == 0) printf("TEST SUCCESSFULLY COMPLETED: Card Test 1 \n");
   	else printf("TEST FAILED: Card Test 1 \n");

	return 0;
}


void assertTrue(int value, int line, int* failFlag){
	if(value == 0){
		printf("Error on line %d\n", line);
		*failFlag = 1;
	}
}
