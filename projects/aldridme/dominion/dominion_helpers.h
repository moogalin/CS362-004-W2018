#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int play_adventurer(struct gameState *state, int drawntreasure, int currentPlayer, int z);
int play_smithy(int currentPlayer, struct gameState * state, int handPos);
int play_mine(int currentPlayer, struct gameState * state, int choice1, int choice2, int handPos);
int play_ambassador(int currentPlayer, struct gameState * state, int choice1, int choice2, int handPos);
int play_treasure_map(int currentPlayer, struct gameState *state, int handPos);
int cardEffect(int card, int choice1, int choice2, int choice3,
	       struct gameState *state, int handPos, int *bonus);

#endif
