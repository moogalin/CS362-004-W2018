#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PLAYERS 4
#define NUM_SUPPLYCARDS 27
#define CARD smithy

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};



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

void print_testName(char s[]) {
   printf("*TEST: %s\n", s);
}

void print_testPassed(char s[]) {
   printf("*       PASS: %s\n", s);
}

void print_testFailed(char s[]) {
   printf("*       FAIL: %s\n", s);
}

int main() {
  srand(time(NULL));

  int testPassed = 1;
  char msg[255] = {'\0'};
  int i, player, choice1, choice2, choice3, handPos, coinBonus = 0;
  struct gameState g_res, g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  printf("***************************************\n");
  printf("*         Testing: Smithy Card   \n");
  printf("***************************************\n\n");

  /* Initialize necessary (used) gameState attributes */
  g_res.whoseTurn = 0;
  player = g_res.whoseTurn;
  g_res.handCount[player] = 5;
  g_res.deckCount[player] = 5;
  g_res.discardCount[player] = 5;
  g_res.playedCardCount = 0;

  //Initialize hand to Smithy cards to prevent garbage values
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = CARD;
    g_res.deck[player][i] = CARD;
    g_res.discard[player][i] = CARD;
    g_res.playedCards[i] = -1;
  }

  handPos = 4;

  //Copy gameStates
  copyGameState(&g_res, &g_exp);

  //Play Smithy
  cardEffect(CARD, choice1, choice2, choice3, &g_res, handPos, &coinBonus);

  //Assert hand contains 3 additional cards minus smithy played
  g_exp.handCount[player] = g_exp.handCount[player] + 2;
  if (g_res.handCount[player] != g_exp.handCount[player]) {
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(&msg, sizeof(msg), "Actual handCount %d does not equal Expected %d", g_res.handCount[player], g_exp.handCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(&msg, sizeof(msg), "Actual handCount %d equals Expected %d", g_res.handCount[player], g_exp.handCount[player]);
    print_testPassed(msg);
  }

  //Assert discard contains 1 additional card
  g_exp.discardCount[player]++;
  if (g_res.discardCount[player] != g_exp.discardCount[player]) {
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(&msg, sizeof(msg), "Actual discardCount %d does not equal Expected %d", g_res.discardCount[player], g_exp.discardCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(&msg, sizeof(msg), "Actual discardCount %d equals Expected %d", g_res.discardCount[player], g_exp.discardCount[player]);
    print_testPassed(msg);
  }

  //Assert deck pile contains 3 less cards
  g_exp.deckCount[player] = g_exp.deckCount[player] - 3;
  if (g_res.deckCount[player] != g_exp.deckCount[player]) {
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(&msg, sizeof(msg), "Actual deckCount %d does not equal Expected %d", g_res.deckCount[player], g_exp.deckCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(&msg, sizeof(msg), "Actual deckCount %d equals Expected %d", g_res.deckCount[player], g_exp.deckCount[player]);
    print_testPassed(msg);
  }

  if (testPassed) {
    printf("***************************************\n");
    printf("*       Overall: All Tests Passed      \n");
    printf("***************************************\n\n");
  }
  else {
    printf("***************************************\n");
    printf("*       Overall: One or more Tests Failed\n");
    printf("***************************************\n\n");
  }

  return 0;
}
