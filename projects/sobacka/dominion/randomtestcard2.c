/*
Andrew Soback
Random Tester 2
Assignment 4
Tests Smithy

Smithy gains the player 3 cards from their deck to their hand, when played.
Last changed: 2/25/19
*/

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void assertTrue(int, int, int*);

int main(){
	int val = 0;
	int *failFlag;
	failFlag = &val;

  srand(time(NULL));
  //This test is just to make sure that my assert true works
  assertTrue(1, __LINE__, failFlag);

  // Run 10,000 random tests.
  int x;
  for (x = 0; x < 10000; x++){
    int i;
    int seed = (rand() % 10) + 1;
    int players = (rand() % 7) +  2; // 2 to 8 players 

    int k[10] = {smithy, adventurer, council_room, village, minion, mine, cutpurse, sea_hag, tribute, ambassador};
    struct gameState* G = newGame();
    initializeGame(players, k, seed, G); // Game initialized with a random number of playes, as well as a random seed

    int currentPlayer = whoseTurn(G);
    //gainCard(smithy, G, 2, currentPlayer);  // 3rd parameter is toFlag, 2 equals hand

    // Remove all cards from deck, by setting deck count to 0
    G->deckCount[currentPlayer] = 0;
    // Add random number of coppers to deck, inc deck count each time.
    int coppers = rand() % 11; //0 - 10 coppers to add to deck
    for(i = 0; i < coppers; i++){
      G->deck[currentPlayer][i] = copper;
      G->deckCount[currentPlayer]++;
    }

    // Set random number of buys (0-10)
    G->numBuys = rand() % 11;
    // Set random number of actions (1-10). This must be at least 1 or else the card cannoted be played
    G->numActions = (rand() % 10) + 1;

    // Get values to be compared later
    int testDeckCount = G->deckCount[currentPlayer];
    int testHandCount = G->handCount[currentPlayer];
    int testActions = G->numActions;
    int testBuys = G->numBuys;
    int testPlayed = G->playedCardCount;

    int smithyPosition = testHandCount - 1; // smithyPos used to mark the smithy card position
    
    G->hand[currentPlayer][smithyPosition] = smithy;

    // Test apparent successful run of card (return value of 0)
    int res;
    res = playCard(smithyPosition, 0, 0 ,0, G);
    assertTrue(res == 0, __LINE__, failFlag);

    // So long as there are enough cards in the deck, one card is removed from the hand, and three are added
    // Three are also removed from the deck
    if(testDeckCount >= 3){
      assertTrue(G->deckCount[currentPlayer] == testDeckCount - 3, __LINE__, failFlag);
      assertTrue(G->handCount[currentPlayer] == testHandCount + 2, __LINE__, failFlag);
    }
    // With only two cards in the deck, two are added to the hand and one is played, and the deck should now have no cards
    else if(testDeckCount == 2){
      assertTrue(G->deckCount[currentPlayer] == 0, __LINE__, failFlag);
      assertTrue(G->handCount[currentPlayer] == testHandCount + 1, __LINE__, failFlag);
    }
    // If there is only one card in the deck, one card is played, one is added to the hand, and the deck should now be 0
    else if(testDeckCount == 1){
      assertTrue(G->deckCount[currentPlayer] == 0, __LINE__, failFlag);
      assertTrue(G->handCount[currentPlayer] == testHandCount, __LINE__, failFlag);
    }
    // In this case, the handcount should decrease, as one card has been played
    // However, the deck count should remain the same, as nothing was in it to draw from
    else if(testDeckCount == 0){
      assertTrue(G->deckCount[currentPlayer] == 0, __LINE__, failFlag);
      assertTrue(G->handCount[currentPlayer] == testHandCount - 1, __LINE__, failFlag);
    }
    // This line should never be called
    else{
      assertTrue(0, __LINE__, failFlag);
    }

    // Actions should be one less than previously
    assertTrue(G->numActions = testActions - 1, __LINE__, failFlag);

    // Buys should not be affected by this card
    assertTrue(G->numBuys == testBuys + 2, __LINE__, failFlag);

    // The number of cards played should have increased by 1
    assertTrue(G->playedCardCount == testPlayed + 1, __LINE__, failFlag);

    // Current player should not change
    assertTrue(whoseTurn(G) == currentPlayer, __LINE__, failFlag);
    free(G);
  }

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
