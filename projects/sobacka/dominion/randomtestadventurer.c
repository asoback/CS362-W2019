/*
Andrew Soback
Random Tester for Adventurer Card
Assignment 4

Adventurer draws cards, discards them if they are not treasure cards, and keeps treasures, until two treasures have been drawn.
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
    struct gameState G;
    initializeGame(players, k, seed, &G); // Game initialized with a random number of playes, as well as a random seed

    int currentPlayer = whoseTurn(&G);
    gainCard(adventurer, &G, 2, currentPlayer);  // 3rd parameter is toFlag, 2 equals hand

    // Remove all cards from deck, by setting deck count to 0
    G.deckCount[currentPlayer] = 0;
    // Add random number of coppers to deck, inc deck count each time.
    int coppers = rand() % 11; //0 - 10 coppers to add to deck
    for(i = 0; i < coppers; i++){
      G.deck[currentPlayer][i] = copper;
      G.deckCount[currentPlayer]++;
    }
    // Add random number (0-10) of estates as well, then shuffle
    int estates = rand() % 11;
     for(i = 0; i < estates; i++){
      G.deck[currentPlayer][i] = estate;
      G.deckCount[currentPlayer]++;
    }

    shuffle(currentPlayer, &G);

    // Set random number of buys (0-10)
    G.numBuys = rand() % 11;
    // Set random number of actions (1-10). This must be at least 1 or else the card cannoted be played
    G.numActions = (rand() % 10) + 1;

    // Get values to be compared later
    int testDeckCount = G.deckCount[currentPlayer];
    int testHandCount = G.handCount[currentPlayer];
    int testActions = G.numActions;
    int testBuys = G.numBuys;
    int testPlayed = G.playedCardCount;
    int testCoins = G.coins;

    int aPosition; // aPosition used to mark the adventurer card position
    for (i = 0; i < G.handCount[currentPlayer]; i++){
      if(G.hand[currentPlayer][i] == adventurer){
        aPosition = i;
        break;
      }
    }

    // Test apparent successful run of card (return value of 0)
    int res;
    res = playCard(aPosition, 0, 0 ,0, &G);
    assertTrue(res == 0, __LINE__, failFlag);



    if(testDeckCount >= 2){
      assertTrue(G.deckCount[currentPlayer] <= testDeckCount - 2, __LINE__, failFlag); // At least two cards drawn from deck
      assertTrue(G.handCount[currentPlayer] >= testHandCount + 1, __LINE__, failFlag); // One card played and at least two drawn
    }
    else if(testDeckCount == 1){
      assertTrue(G.deckCount[currentPlayer] <= testDeckCount - 1, __LINE__, failFlag); // At least one drawn from deck
      assertTrue(G.handCount[currentPlayer] >= testHandCount, __LINE__, failFlag); // One card is played, and one always drawn, which evens out
    }
    else if(testDeckCount == 0){
      assertTrue(G.deckCount[currentPlayer] <= testDeckCount, __LINE__, failFlag);
      assertTrue(G.handCount[currentPlayer] >= testHandCount - 1, __LINE__, failFlag); //One card is played, none drawn
    }
    // This line should never be called
    else{
      assertTrue(0, __LINE__, failFlag);
    }

    // Test that if there were two+ coppers in deck before, that the hand now contains exactly two more coppers
    if (coppers >= 2){
      assertTrue(G.coins == testCoins + 2, __LINE__, failFlag);
    }
    // Only one copper
    else if(coppers == 1){
      assertTrue(G.coins == testCoins + 1, __LINE__, failFlag);
    }
    // No coppers
    else if (coppers == 0){
      assertTrue(G.coins == testCoins, __LINE__, failFlag);
    }
    else {
      assertTrue(0, __LINE__, failFlag);
    }

    // Actions should be one less than previously
    assertTrue(G.numActions = testActions - 1, __LINE__, failFlag);

    // Buys should not be affected by this card
    assertTrue(G.numBuys == testBuys + 2, __LINE__, failFlag);

    // The number of cards played should have increased by 1
    assertTrue(G.playedCardCount == testPlayed + 1, __LINE__, failFlag);

    // Current player should not change
    assertTrue(whoseTurn(&G) == currentPlayer, __LINE__, failFlag);
  }


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



/*
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
    assertTrue(G.discardCount[currentPlayer] == 1, __LINE__, failFlag);

    // There should only be two cards in the hand, both coppers
    assertTrue(G.handCount[currentPlayer] == 2, __LINE__, failFlag);
    assertTrue(G.hand[currentPlayer][0] == copper, __LINE__, failFlag);
    assertTrue(G.hand[currentPlayer][1] == copper, __LINE__, failFlag);
*/
