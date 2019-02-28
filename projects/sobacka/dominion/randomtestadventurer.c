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
  clearLines();

  int i;
	int val = 0;
	int *failFlag;
	failFlag = &val;
	struct gameState* G;

  int k[10] = {smithy, adventurer, council_room, village, minion, mine, cutpurse, sea_hag, tribute, ambassador};
  srand(time(NULL));
 	
  //This test is just to make sure that my assert true works
	assertTrue(1, __LINE__, failFlag);
	
  int seed, players, x, coinType;
  // Run 10,000 random tests.
  for (x = 0; x < 10000; x++){
    seed = (rand() % 10) + 1;
    players = (rand() % 7) +  2; // 2 to 8 players 
	  coinType = rand() % 3; // 0 for copper, 1 for silver, and 2 for gold
    G = newGame();
    initializeGame(players, k, seed, G); // Game initialized with a random number of playes, as well as a random seed

    int currentPlayer = whoseTurn(G);
    //gainCard(adventurer, G, 2, currentPlayer);  // 3rd parameter is toFlag, 2 equals hand

    // Remove all cards from deck, by setting deck count to 0
    G->deckCount[currentPlayer] = 0;
    // Add random number of coppers to deck, inc deck count each time.
    int coinAdd = rand() % 11; //0 - 10 coins of a type to add to deck
    for(i = 0; i < coinAdd; i++){
    	if(coinType == 0){G->deck[currentPlayer][i] = copper;}	
    	else if(coinType == 1){G->deck[currentPlayer][i] = silver;}
    	else {G->deck[currentPlayer][i] = gold;}
      G->deckCount[currentPlayer]++;
    }

    // Add random number (0-10) of estates as well, then shuffle
    int estates = rand() % 11;
    for(i = coinAdd; i < (estates + coinAdd); i++){
      G->deck[currentPlayer][i] = estate;
      G->deckCount[currentPlayer]++;
    }
    
	  shuffle(currentPlayer, G);
    // Set random number of buys (0-10)
    G->numBuys = rand() % 11;
    // Set random number of actions (1-10). This must be at least 1 or else the card cannoted be played
    G->numActions = (rand() % 10) + 1;
	  //setting my own hand, to make sure that all variables are intentional
	  for( i = 0; i < 4; i++){
	   	G->hand[currentPlayer][i] == copper;
	  }
    G->hand[currentPlayer][4] = adventurer;
	  G->handCount[currentPlayer] = 5;
    int aPos = 4; // aPos used to mark the adventurer card position
  
    // Get values to be compared later
    int testDeckCount = G->deckCount[currentPlayer];
    int testHandCount = G->handCount[currentPlayer];
    int testActions = G->numActions;
    int testBuys = G->numBuys;
    int testPlayed = G->playedCardCount;

	  updateCoins(currentPlayer, G, 0);
    int testCoins = G->coins;

    // Test apparent successful run of card (return value of 0)
    int res;

    //This line is being used to prevent a segfault for a known bug in the playAdventure function. Documented in my assignment 4 PDF
    if(coinAdd == 0){
      continue;
    }
    res = playCard(aPos, 0, 0 ,0, G);
    assertTrue(res == 0, __LINE__, failFlag);

    if(testDeckCount >= 2){
      assertTrue(G->deckCount[currentPlayer] <= testDeckCount - 2, __LINE__, failFlag); // At least two cards drawn from deck
      assertTrue(G->handCount[currentPlayer] >= testHandCount + 1, __LINE__, failFlag); // One card played and at least two drawn
    }
    else if(testDeckCount == 1){
      assertTrue(G->deckCount[currentPlayer] <= testDeckCount - 1, __LINE__, failFlag); // At least one drawn from deck
      assertTrue(G->handCount[currentPlayer] >= testHandCount, __LINE__, failFlag); // One card is played, and one always drawn, which evens out
    }
    else if(testDeckCount == 0){
      assertTrue(G->deckCount[currentPlayer] <= testDeckCount, __LINE__, failFlag);
      assertTrue(G->handCount[currentPlayer] >= testHandCount - 1, __LINE__, failFlag); //One card is played, none drawn
    }
    // This line should never be called
    else{
      assertTrue(0, __LINE__, failFlag);
    }

    // Test that if there were two+ coins in deck before, that the hand now contains exactly two more coppers
    if (coinAdd >= 2){
      assertTrue(G->coins == testCoins + (coinType+1)*2, __LINE__, failFlag);
    }
    // Only one coins
    else if(coinAdd == 1){
      assertTrue(G->coins == testCoins + (coinType+1)*2, __LINE__, failFlag);
    }
    // No coins
    else if (coinAdd == 0){
      assertTrue(G->coins == testCoins, __LINE__, failFlag);
    }
    else {
      assertTrue(0, __LINE__, failFlag);
    }

    updateCoins(currentPlayer, G, 0);
    // Actions should be one less than previously
    assertTrue(G->numActions = testActions - 1, __LINE__, failFlag);

    // Buys should not be affected by this card
    assertTrue(G->numBuys == testBuys, __LINE__, failFlag);

    // The number of cards played should have increased by 1
    assertTrue(G->playedCardCount == testPlayed + 1, __LINE__, failFlag);
    
    // Current player should not change
    assertTrue(whoseTurn(G) == currentPlayer, __LINE__, failFlag);
    free(G);
  }

	if (*failFlag == 0) printf("TEST SUCCESSFULLY COMPLETED: Card Test 2 \n");
  else printf("TEST FAILED: Card Test 2 \n");

	return 0;
}

void assertTrue(int value, int line, int* failFlag){
	if(value == 0){
		errorLine[line]++;
		*failFlag = 1;
	}
}
