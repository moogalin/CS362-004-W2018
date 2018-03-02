#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Copy game state from original to copy */
void copyGameState(struct gameState * g_original, struct gameState * g_copy) {
  int i,j;

  g_copy->numPlayers = g_original->numPlayers;

  for (i = 0; i < NUM_SUPPLYCARDS; i++) {
    g_copy->supplyCount[i] = g_original->supplyCount[i];
  }

  for (i = 0; i < NUM_SUPPLYCARDS; i++) {
    g_copy->embargoTokens[i] = g_original->embargoTokens[i];
  }

  g_copy->outpostPlayed = g_original->outpostPlayed;
  g_copy->outpostTurn = g_original->outpostTurn;
  g_copy->whoseTurn = g_original->whoseTurn;
  g_copy->phase = g_original->phase;
  g_copy->numActions = g_original->numActions;
  g_copy->coins = g_original->coins;
  g_copy->numBuys = g_original->numBuys;

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_HAND; j++){
      g_copy->hand[i][j] = g_original->hand[i][j];
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    g_copy->handCount[i] = g_original->handCount[i];
  }

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_DECK; j++){
      g_copy->deck[i][j] = g_original->deck[i][j];
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    g_copy->deckCount[i] = g_original->deckCount[i];
  }

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_DECK; j++){
      g_copy->discard[i][j] = g_original->discard[i][j];
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    g_copy->discardCount[i] = g_original->discardCount[i];
  }

  for (i = 0; i < MAX_DECK; i++) {
    g_copy->playedCards[i] = g_original->playedCards[i];
  }

  g_copy->playedCardCount = g_original->playedCardCount;
}

/* Verify game states are equal */
int gameStatesEqual(struct gameState * g_original, struct gameState * g_copy) {
  int i,j;
  if (g_copy->numPlayers != g_original->numPlayers) {
    return 0;
  }

  for (i = 0; i < NUM_SUPPLYCARDS; i++) {
    if (g_copy->supplyCount[i] != g_original->supplyCount[i]) {
      return 0;
    }
  }

  for (i = 0; i < NUM_SUPPLYCARDS; i++) {
    if (g_copy->embargoTokens[i] != g_original->embargoTokens[i]) {
      return 0;
    }
  }

  if (g_copy->outpostPlayed != g_original->outpostPlayed) {
    return 0;
  }

  if (g_copy->outpostTurn != g_original->outpostTurn) {
    return 0;
  }

  if (g_copy->whoseTurn != g_original->whoseTurn) {
    return 0;
  }

  if (g_copy->phase != g_original->phase) {
    return 0;
  }

  if (g_copy->numActions != g_original->numActions) {
    return 0;
  }

  if (g_copy->coins != g_original->coins) {
    return 0;
  }

  if (g_copy->numBuys != g_original->numBuys) {
    return 0;
  }

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_HAND; j++){
      if (g_copy->hand[i][j] != g_original->hand[i][j]) {
        return 0;
      }
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    if(g_copy->handCount[i] != g_original->handCount[i]){
      return 0;
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_DECK; j++){
      if(g_copy->deck[i][j] != g_original->deck[i][j]) {
        return 0;
      }
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    if(g_copy->deckCount[i] != g_original->deckCount[i]) {
      return 0;
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_DECK; j++){
      if(g_copy->discard[i][j] != g_original->discard[i][j]) {
        return 0;
      }
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    if(g_copy->discardCount[i] != g_original->discardCount[i]) {
      return 0;
    }
  }

  for (i = 0; i < MAX_DECK; i++) {
    if(g_copy->playedCards[i] != g_original->playedCards[i]) {
      return 0;
    }
  }

  if(g_copy->playedCardCount != g_original->playedCardCount) {
    return 0;
  }

  return 1;
}

/* Print game state for debugging */
void printGameState(struct gameState * g, char s[]) {
  int i,j;

  printf("***************************************\n");
  printf("*         GameState %s:                  \n", s);
  printf("* NumPlayers: %d", g->numPlayers);
  printf("\n* SupplyCount[treasure_map+1]: ");
  for (i=0; i < (treasure_map+1); i++)
  {
    printf("\n**  SupplyCount[%d] = %d", i, g->supplyCount[i]);
  }
  printf("\n* embargoTokens[treasure_map+1]: ");
  for (i=0; i < (treasure_map+1); i++)
  {
    printf("\n**  embargoTokens[%d] = %d", i, g->embargoTokens[i]);
  }
  printf("\n* outpostPlayed: %d", g->outpostPlayed);
  printf("\n* outpostTurn: %d", g->outpostTurn);
  printf("\n* whoseTurn: %d", g->whoseTurn);
  printf("\n* phase: %d", g->phase);
  printf("\n* numActions: %d", g->numActions);
  printf("\n* coins: %d", g->coins);
  printf("\n* numBuys: %d", g->numBuys);
  printf("\n* hand[MAX_PLAYERS][MAX_HAND]: ");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    for (j=0; j < MAX_HAND; j++)
    {
      printf("\n**  hand[%d][%d] = %d", i,j, g->hand[i][j]);
    }
  }
  printf("\n* handCount[MAX_PLAYERS]");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    printf("\n**  handCount[%d] = %d", i,g->handCount[i]);
  }
  printf("\n* deck[MAX_PLAYERS][MAX_DECK]");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    for (j=0; j < MAX_DECK; j++)
    {
      printf("\n**  deck[%d][%d] = %d", i,j, g->deck[i][j]);
    }
  }
  printf("\n* deckCount[MAX_PLAYERS]");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    printf("\n**  deckCount[%d] = %d", i,g->deckCount[i]);
  }
  printf("\n* discard[MAX_PLAYERS][MAX_DECK]");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    for (j=0; j < MAX_DECK; j++)
    {
      printf("\n**  discard[%d][%d] = %d", i,j, g->discard[i][j]);
    }
  }
  printf("\n* discardCount[MAX_PLAYERS]");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    printf("\n**  discardCount[%d] = %d", i,g->discardCount[i]);
  }
  printf("\n* playedCards[MAX_DECK]");
  for (i=0; i < (MAX_DECK); i++)
  {
    printf("\n**  playedCards[%d] = %d", i,g->playedCards[i]);
  }
  printf("\n* playedCardCount %d", g->playedCardCount);
  printf("\n***************************************\n");
}

void print_testName(char s[]) {
   printf("*TEST: %s\n", s);
}

void print_testPassed(char s[]) {
   printf("*       PASS: %s\n", s);
}

void print_testFailed(char s[]) {
   printf("*       FAIL: %s\n", s);
}

int rand_int(int a, int b){
  int random = (rand() % (b - a + 1) + a );
  return random;
}
