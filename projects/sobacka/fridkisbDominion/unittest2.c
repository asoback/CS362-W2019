/*
Andrew Soback
Unit Test 2 
Assignment 3

Tests initializeGame() function
Before running this test, be sure to test drawCard, shuffle, and updateCoins functions

intializeGame() takes number of players, an array of 10 kingdomCards, a randmomSeed, and a pointer to a gameState struct
Returns 0 on success, or -1 on failure.

Testing:
	Number of players must be between 2 and MAX_PLAYERS
	No duplicate cards allowed
	Supply counts must be accurate to game specification
	Only the 10 kingdom cards, 3 treasure cards, 3 victory cards, and curses have any supply in the game
	Each player must have the correct number of copper and estate cards at the beginning of the game
	Each player must have only those two types of cards]
	The other values are correctly initialized
*/

#include "rngs.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void assertTrue(int, int, int*);

int main(){
	int *failFlag;
	int val = 0;
	failFlag = &val;

	// Cards chosen are not important to this function, so long as they are different
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};
  struct gameState G;

  // Fail on out of bounds number of players
  assertTrue(initializeGame(-1, k, 2, &G) == -1, __LINE__, failFlag);
  assertTrue(initializeGame(0, k, 2, &G) == -1, __LINE__, failFlag);
  assertTrue(initializeGame(1, k, 2, &G) == -1, __LINE__, failFlag);
  assertTrue(initializeGame(MAX_PLAYERS +1, k, 2, &G) == -1, __LINE__, failFlag);
  // Succeed on boundary case of max players
  assertTrue(initializeGame(MAX_PLAYERS, k, 2, &G) == 0, __LINE__, failFlag);
  memset(&G, 0, sizeof(struct gameState));   // clear the game state

  // fail on duplicate cards
  k[0] = gardens; // k[1] is also gardener
  assertTrue(initializeGame(2, k, 2, &G) == -1, __LINE__, failFlag);
  k[0] = adventurer;

  // Succeed with correct number of players and all different cards
  int numPlayers = 2;
 	assertTrue(initializeGame(numPlayers, k, 2, &G) == 0, __LINE__, failFlag);

    // Check supply counts are correct per game specifications
 	assertTrue(G.supplyCount[curse] == 10, __LINE__, failFlag);
 	assertTrue(G.supplyCount[estate] == 8, __LINE__, failFlag);
	assertTrue(G.supplyCount[duchy] == 8, __LINE__, failFlag);
	assertTrue(G.supplyCount[province] == 8, __LINE__, failFlag);
	assertTrue(G.supplyCount[copper] == (60 - (7 * numPlayers)), __LINE__, failFlag);
	assertTrue(G.supplyCount[silver] == 40, __LINE__, failFlag);
	assertTrue(G.supplyCount[gold] == 30, __LINE__, failFlag);

	// Same for kingdom cards
	assertTrue(G.supplyCount[adventurer] == 10, __LINE__, failFlag);
	assertTrue(G.supplyCount[gardens] == 8, __LINE__, failFlag);
	assertTrue(G.supplyCount[embargo] == 10, __LINE__, failFlag);
	assertTrue(G.supplyCount[village] == 10, __LINE__, failFlag);
	assertTrue(G.supplyCount[minion] == 10, __LINE__, failFlag);
	assertTrue(G.supplyCount[mine] == 10, __LINE__, failFlag);
	assertTrue(G.supplyCount[cutpurse] == 10, __LINE__, failFlag);
	assertTrue(G.supplyCount[sea_hag] == 10, __LINE__, failFlag);
	assertTrue(G.supplyCount[tribute] == 10, __LINE__, failFlag);
	assertTrue(G.supplyCount[smithy] == 10, __LINE__, failFlag);

  // Check that only 17 cards have any supply ( All unsused cards should not have any available supply)
	int cardCount = 0;
	int i;
	for (i = curse; i < treasure_map; i++){
		if (G.supplyCount[i] > 0){
			cardCount++;
		}
	}
	assertTrue(cardCount == 17, __LINE__, failFlag);
  
  // Check that each deck is correct (3 estates "e" and 7 copper "c" and 0 others)
  int e, c, j; // j used for for-loop 
	for (i = 0; i < numPlayers; i++){
		e = 0;
		c = 0;
		// Check deck count is correct
  		for(j = 0; j < G.deckCount[i]; j++){
  			if (G.deck[i][j] == estate){
  				e++;
  			}
  			else if(G.deck[i][j] == copper){
  				c++;
  			}
  			else{
  				assertTrue(0, __LINE__, failFlag); //Fail on any other cards
  			}
  		}
		for (j = 0; j < G.handCount[i]; j++){
			if (G.hand[i][j] == estate){ e++;}
			else if (G.hand[i][j] == copper) { c++; }
			else { assertTrue(0, __LINE__, failFlag); }
		}
			// Assert that there are 3 estates and 7 coppers in each deck
  		assertTrue(e == 3, __LINE__, failFlag);
  		assertTrue(c == 7, __LINE__, failFlag);
	}
	// Check remaining values affected by this function
	assertTrue(G.numPlayers == numPlayers, __LINE__,  failFlag); 
	assertTrue(G.outpostPlayed == 0, __LINE__,  failFlag);
	assertTrue(G.phase == 0, __LINE__,  failFlag);
	assertTrue(G.numActions == 1, __LINE__,  failFlag);
	assertTrue(G.numBuys == 1, __LINE__,  failFlag);
	assertTrue(G.playedCardCount == 0, __LINE__,  failFlag);
	assertTrue(G.whoseTurn == 0, __LINE__,  failFlag);
	assertTrue(G.handCount[0] == 5, __LINE__,  failFlag); 
	assertTrue(G.handCount[1] == 0, __LINE__,  failFlag); 
	for (i = 0; i <= treasure_map; i++){
    	  assertTrue(G.embargoTokens[i] == 0, __LINE__, failFlag);
   	}

  	if(*failFlag == 0) { printf("TEST SUCCESSFULLY COMPLETED: Unit Test 2\n"); }
  	else { printf("TEST FAILED: Unit Test 2\n"); }

  	return 0;
}

void assertTrue(int value, int line, int* failFlag){
	if(value == 0){
		printf("Error near line %d\n", line);
		*failFlag = 1;
	}
}
