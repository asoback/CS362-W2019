/*
Andrew Soback
Random Tester 1 
Assignment 4
Tests Village

Village card gains the player one card, and two actions
Last changed: 2/25/19
*/

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void assertTrue(int, int, int*);
int errorLine[150]; //Global is used to count the number of times an error occurs

//Set the count of all lines to 0, no errors have occured yet
void clearLines(){
  int i;
  for (i = 0; i < 150; i++){
    errorLine[i] = 0;
  }
}

void printErrors(){
  int i;
  for (i = 0; i < 150; i++){
    if (errorLine[i] > 0){
      printf("Error on line %d\n occured %d times", line, errorLine[i]);
    }
  }
}

int main(){
	int val = 0;
	int *failFlag;
	failFlag = &val;
	srand(time(NULL));
	//This test is just to make sure that my assert true works
	assertTrue(1, __LINE__, failFlag);

	// Run 10,000 random tests.
	int x;
	for ( x = 0; x < 10000; x++){
		int i;
		int seed = (rand() % 10) + 1;
		int players = (rand() % 7) +  2; // 2 to 8 players 

		int k[10] = {smithy, adventurer, council_room, village, minion, mine, cutpurse, sea_hag, tribute, ambassador};
  		struct gameState* G = newGame();
  		initializeGame(players, k, seed, G); //Game initialized with a random number of playes, as well as a random seed

  		int currentPlayer = whoseTurn(G);
  		
		//remove all cards from deck, by setting deck count to 0
  		G->deckCount[currentPlayer] = 0;
  		//add random number of coppers to deck, inc deck count each time.
  		int coppers = rand() % 11; //0 - 10 coppers to add to deck
  		for(i = 0; i < coppers; i++){
  			G->deck[currentPlayer][i] = copper;
  			G->deckCount[currentPlayer]++;
  		}

  		//set random number of buys (0-10)
  		G->numBuys = rand() % 11;
  		//set random number of actions (1-10). This must be at least 1 or else the card cannoted be played
  		G->numActions = (rand() % 10) + 1;

  		//Get values to be compared later
  		int testDeckCount = G->deckCount[currentPlayer];
  		int testHandCount = G->handCount[currentPlayer];
		int testActions = G->numActions;
		int testBuys = G->numBuys;
		int testPlayed = G->playedCardCount;

		int vPos = testHandCount - 1; // vPos used to mark the village card position
		
		G->hand[currentPlayer][vPos] = village;

		// Test apparent successful run of card (return value of 0)
		int res;
	  	res = playCard(vPos, 0, 0 ,0, G);
	  	assertTrue(res == 0, __LINE__, failFlag);

	  	// So long as there are enough cards in the deck, one card is removed from the hand, and two are added
	  	// Two are also removed from the deck
	  	if(testDeckCount >= 2){
	  		assertTrue(G->deckCount[currentPlayer] == testDeckCount - 1, __LINE__, failFlag);
	  		assertTrue(G->handCount[currentPlayer] == testHandCount, __LINE__, failFlag);
	  	}

	  	// If there is only one card in the deck, one card is played, one is added to the hand, and the deck should now be 0
	  	else if(testDeckCount == 1){
	  		assertTrue(G->deckCount[currentPlayer] == 0, __LINE__, failFlag);
	  		assertTrue(G->handCount[currentPlayer] == testHandCount, __LINE__, failFlag);
	  	}
	  	// In this case, the handcount should decrease, as one card has been played
	  	// However, the deck count should remain the same, as nothing was in it to draw from
	  	else if(testDeckCount == 0){
	  		assertTrue(G->deckCount[currentPlayer] == testDeckCount, __LINE__, failFlag);
	  		assertTrue(G->handCount[currentPlayer] == testHandCount - 1, __LINE__, failFlag);
	  	}
	  	// This line should never be called
	  	else{
	  		assertTrue(0, __LINE__, failFlag);
	  	}

	  	// Two actions are added, but 1 is used by playing the card, so the number of actions should only increment 1
	  	assertTrue(G->numActions = testActions + 1, __LINE__, failFlag);

	  	// The number of buys should stay the same
		assertTrue(G->numBuys == testBuys, __LINE__, failFlag);

	  	// The number of cards played should have increased by 1
	  	assertTrue(G->playedCardCount == testPlayed + 1, __LINE__, failFlag);

	  	// Current player should not change
	  	assertTrue(whoseTurn(G) == currentPlayer, __LINE__, failFlag);

		free(G);
	}

	//Print final status of tester
	if (*failFlag == 0) printf("TEST SUCCESSFULLY COMPLETED: Random Test Card 1 \n");
	else printf("TEST FAILED:  Random Test Card 1 \n");

	return 0;
}

void assertTrue(int value, int line, int* failFlag){
	if(value == 0){
		errorLine[line]++;
		*failFlag = 1;
	}
}
