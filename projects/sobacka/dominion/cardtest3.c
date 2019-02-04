/*
Andrew Soback
Card Test 1 
Assignment 3

Tests Council Room
Playing council room gains 4 cards, increments buy, and each other player also draws a card

Test:
	Test that card count has increased by 3, and all are legitimate cards
	Check players buys have increased
	Check that each other player now has an extra card
	Check that the card played has been discarded
*/

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

void assertTrue(int, int, int*);

int main(){
	int *failFlag;
	*failFlag = 0;

	int k[10] = {smithy, adventurer, council_room, village, minion, mine, cutpurse, sea_hag, tribute, ambassador};
  	struct gameState G;
  	initializeGame(2, k, 1, &G); //Two player game, with the above array of cards, random seed, and the gamestate struct
  	int currentPlayer = whoseTurn(&G);

	int prevHandCount = G.handCount[currentPlayer];
	int prevBuys = G.numBuys;

	// Add a Smithy to hand
  	gainCard(council_room, &G, 2, currentPlayer);  // 3rd parameter is toFlag, 2 equals hand

  	// Get council room position
  	int crPosition;
  	for(i = 0; i < handCount; i++){
  		if( G.hand[currentPlayer][i] == council_room){
  			crPosition = i;
  			break;
  		}
  	}

  	// Test successful play of council room
  	int res;
  	res = playCard(crPosition, 0, 0 ,0, &G);
  	assertTrue(res, __LINE__, failFlag);

  	// Test that 4 new cards have arrived (Testing for validity of the cards coming to the hand from the deck can be tested in drawCard())
  	assertTrue(G.handCount[currentPlayer] - prevHandCount == 4, __LINE__, failFlag);

  	// check that one card has been discarded, and that it is the correct card
  	assertTrue(G.discardCount[currentPlayer] == 1, __LINE__, failFlag);
  	assertTrue(G.discard[currentPlayer][0] == council_room, __LINE__, failFlag);

  	// Check that there is one more buy after playing the card
  	assertTrue(G.numBuys +1 == prevBuys, __LINE__, failFlag);

  	// Check that each other player has also drawn one card
  	//Each other player draws a card
  	for (i = 0; i < G.numPlayers; i++){
    	if ( i != currentPlayer ){
        	assertTrue(G.handCount[i] == ++prevBuys, __LINE__, failFlag);
      	}
  	}

  	if (*failFlag == 0) printf("TEST SUCCESSFULLY COMPLETED: Card Test 3 \n");
    else printf("TEST FAILED: Card Test 3 \n");

	return 0;
}


void assertTrue(int value, int line, int* failFlag){
	if(value != 0){
		printf("Error on line %d\n", line);
		*failFlag = 1;
	}
}