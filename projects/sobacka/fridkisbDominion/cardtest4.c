/*
Andrew Soback
Card Test 1 
Assignment 3

Tests Village'
Village card gains the player one card, and two actions
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
  	gainCard(village, &G, 2, currentPlayer);  // 3rd parameter is toFlag, 2 equals hand

	int prevHandCount = G.handCount[currentPlayer];
	int prevActions = G.numActions;
	int prevPlayed = G.playedCardCount;

	int i, vPos;
	for (i = 0; i < G.handCount[currentPlayer]; i++){
		if(G.hand[currentPlayer][i] == village){
			vPos = i;
			break;
		}
	}
	// Test apparent successful run of card (return value of 0)
	int res;
  	res = playCard(vPos, 0, 0 ,0, &G);
  	assertTrue(res == 0, __LINE__, failFlag);

  	assertTrue(G.handCount[currentPlayer] == prevHandCount, __LINE__, failFlag);
  	assertTrue(G.numActions == prevActions + 1, __LINE__, failFlag); //Only increment 1 because one action was spent, two were gained
  	assertTrue(G.playedCardCount == ++prevPlayed, __LINE__, failFlag);
  	
	if (*failFlag == 0) printf("TEST SUCCESSFULLY COMPLETED: Card Test 4 \n");
	 else printf("TEST FAILED: Card Test 4 \n");

	return 0;
}


void assertTrue(int value, int line, int* failFlag){
	if(value == 0){
		printf("Error on line %d\n", line);
		*failFlag = 1;
	}
}
