/*
Andrew Soback
Card Test 1 
Assignment 3

Tests smithy
Smithy gains the player 3 cards from their deck to their hand, when played.

Test:
	Make sure the card count in hand is 2 more than before (+3 -1 for the played smithy card)
	Make sure the deck comtains two less cards than before

Testing that the cards came from the deck and are now in the hand should be done on the drawCard() function

*/

#include "dominion.h"
#include <stdio.h>

void assertTrue(int, int, int*);

int main(){
	int *failFlag;
	*failFlag = 0;

	//Variables to save for comparison against gamestate
	int currentPlayer, handCount, deckCount, playedCardCount, smithyPosition;

	int hand[MAX_HAND];
  	int deck[MAX_DECK];
  	int playedCards[MAX_DECK];

	int k[10] = {smithy, adventurer, council_room, village, minion, mine, cutpurse, sea_hag, tribute, ambassador};
  	struct gameState G;
  	initializeGame(2, k, 1, &G); //Two player game, with the above array of cards, random seed, and the gamestate struct

  	currentPlayer = whoseTurn(&G);

  	// Get hand count
  	handCount = G->handCount[currentPlayer];

  	// Get what is in hand
  	int i;
  	for(i = 0; i < handCount; i++){
  		hand[i] = G->hand[currentPlayer][i];
  	}

  	// Get deck count
  	deckCount = G->deckCount[currentPlayer];

  	// Get what is in deck
  	for(i=0; i < deckCount; i++){
  		deck[i] = G->deck[currentPlayer][i];
  	}

	// Add a Smithy to hand
  	gainCard(smithy, &G, 2, currentPlayer);  // 3rd parameter is toFlag, 2 equals hand

  	// Get smithy position
  	for(i = 0; i < handCount; i++){
  		if( G->hand[currentPlayer][i] == smithy){
  			smithyPosition = i;
  			break;
  		}
  	}

  	// Play smithy
  	playCard(smithyPosition, 0, 0, 0, &failFlag);

  	// Testing starts here...

  	// Check that the number of cards in hand is 3 more than previously
  	assertTrue(G->handCount[currentPlayer] == handCount + 3, _LINE_, &failFlag);

  	// Check what is in hand, determine what is new
  	int countdown = G->handCount[currentPlayer];
  	int j;
  	int gainedCard[3];
  	int k = 0; //Used to count up for gainedCard array

  	for (i = 0; i < G->handCount[currentPlayer]){ 		// For every card in the hand now
  		for(j = 0; j < handCount; j++){  				// For every card that was in the hand before
  			if(hand[j] == G->hand[currentPlayer][i]){	
  				--countdown;
  				break;
  			}
  		}
  	}
  	assertTrue(countdown==3, _LINE_, &failFlag)

  	// Check deck contains 2 less than before
  	assertTrue(G->deckCount[currentPlayer] == deckCount - 3, _LINE_, &failFlag);
  	
  	// Check that smithy has been played
  	assertTrue(G->playedCards[0] == smithy, _LINE_, &failFlag);


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