/*
Andrew Soback
Card Test 3 
Assignment 3

Tests Council Room
Playing council room gains 4 cards, increments buy, and each other player also draws a card

Due to bug I have introduced for assignment two, this test should fail (on incorrect number of buys)
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
	int val = 0;
	int *failFlag;
	failFlag = &val;

	int k[10] = {smithy, adventurer, council_room, village, minion, mine, cutpurse, sea_hag, tribute, ambassador};
  	struct gameState G;
  	initializeGame(2, k, 1, &G); //Two player game, with the above array of cards, random seed, and the gamestate struct
  	int currentPlayer = whoseTurn(&G);

	int prevHandCount = G.handCount[currentPlayer];
	int prevHandCount2 = G.handCount[1]; //previous handcount for player 2
	int prevBuys = G.numBuys;

	// Add a Smithy to hand
  	gainCard(council_room, &G, 2, currentPlayer);  // 3rd parameter is toFlag, 2 equals hand

  	// Get council room position
  	int crPosition;
	int i;
  	for(i = 0; i < G.handCount[currentPlayer]; i++){
  		if( G.hand[currentPlayer][i] == council_room){
  			crPosition = i;
  			break;
  		}
  	}

  	// Test successful play of council room
  	int res;
  	res = playCard(crPosition, 0, 0 ,0, &G);
  	assertTrue(res == 0, __LINE__, failFlag);

  	// Test that 4 new cards have arrived (Testing for validity of the cards coming to the hand from the deck can be tested in drawCard())
  	assertTrue(G.handCount[currentPlayer] - prevHandCount == 4, __LINE__, failFlag);

  	// check that one card has been played, and that it is the correct card
  	assertTrue(G.playedCardCount == 1, __LINE__, failFlag);
  	assertTrue(G.playedCards[0] == council_room, __LINE__, failFlag);

  	// Check that there is one more buy after playing the card
  	assertTrue(G.numBuys == prevBuys + 1, __LINE__, failFlag);
	printf("num buys %d old buys %d \n", G.numBuys, prevBuys);	
  	// Check that each other player has also drawn one card
  	//Each other player draws a card
  	for (i = 0; i < G.numPlayers; i++){
  	  	if ( i != currentPlayer ){
        		assertTrue(G.handCount[i] == ++prevHandCount2, __LINE__, failFlag);
      		}
  	}

  	if (*failFlag == 0) printf("TEST SUCCESSFULLY COMPLETED: Card Test 3 \n");
    else printf("TEST FAILED: Card Test 3 \n");

	return 0;
}


void assertTrue(int value, int line, int* failFlag){
	if(value == 0){
		printf("Error on line %d\n", line);
		*failFlag = 1;
	}
}
