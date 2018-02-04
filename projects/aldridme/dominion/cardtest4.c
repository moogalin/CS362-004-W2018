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
#define CARD mine

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

void print_testName(char s[]) {
   printf("*TEST: %s\n", s);
}

void print_testPassed(char s[]) {
   printf("*       PASS: %s\n", s);
}

void print_testFailed(char s[]) {
   printf("*       FAIL: %s\n", s);
}

int test_Actions(int numActions) {
  int card = village;
  int testPassed = 1;
  char msg[255] = {'\0'};
  int i, player, bonus, choice1, choice2, choice3, handPos, coinBonus = 0;
  struct gameState g_res, g_exp;

  /* Initialize necessary (used) gameState attributes */
  g_res.numPlayers = 2;
  g_res.whoseTurn = 0;
  player = g_res.whoseTurn;
  g_res.handCount[player] = 5;
  g_res.deckCount[player] = 5;
  g_res.numActions = numActions;
  g_res.hand[player][0] = card;
  handPos = 0;

  memset(msg, 0, sizeof(msg));
  snprintf(&msg, sizeof(msg), "Verify Actions increases by 2");
  print_testName(msg);


  copyGameState(&g_res, &g_exp);

  cardEffect(card, choice1, choice2, choice3, &g_res, handPos, &bonus);

  /* Verify that deck decreased by 1 */
  g_exp.deckCount[player] = g_exp.deckCount[player] - 1;

  if (g_res.deckCount[player] != g_exp.deckCount[player]){
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

  /* Verify that hand stays the same */
  if (g_res.handCount[player] != g_exp.handCount[player]){
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

  /* Verify that actions increased as expected */
  g_exp.numActions = numActions + 2;
  if (g_res.numActions != g_exp.numActions){
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(&msg, sizeof(msg), "Actual numActions %d does not equal Expected %d", g_res.numActions, g_exp.numActions);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(&msg, sizeof(msg), "Actual numActions %d equals Expected %d", g_res.numActions, g_exp.numActions);
    print_testPassed(msg);
  }

  return testPassed;

}

int test_handCount(int handCount) {
  int card = village;
  int testPassed = 1;
  char msg[255] = {'\0'};
  int i, player, bonus, choice1, choice2, choice3, handPos, coinBonus = 0;
  struct gameState g_res, g_exp;

  /* Initialize necessary (used) gameState attributes */
  g_res.numPlayers = 2;
  g_res.whoseTurn = 0;
  player = g_res.whoseTurn;
  g_res.handCount[player] = handCount;
  g_res.deckCount[player] = 5;
  g_res.numActions = 5;
  g_res.hand[player][0] = card;
  handPos = 0;

  memset(msg, 0, sizeof(msg));
  snprintf(&msg, sizeof(msg), "Verify HandCount stays the same (1 drawn card, 1 discarded card)");
  print_testName(msg);

  copyGameState(&g_res, &g_exp);

  cardEffect(card, choice1, choice2, choice3, &g_res, handPos, &bonus);

  /* Verify that deck decreased by 1 */
  g_exp.deckCount[player] = g_exp.deckCount[player] - 1;

  if (g_res.deckCount[player] != g_exp.deckCount[player]){
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

  /* Verify that hand stays same */
  if (g_res.handCount[player] != g_exp.handCount[player]){
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

  /* Verify that actions increased as expected */
  g_exp.numActions = g_exp.numActions + 2;
  if (g_res.numActions != g_exp.numActions){
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(&msg, sizeof(msg), "Actual numActions %d does not equal Expected %d", g_res.numActions, g_exp.numActions);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(&msg, sizeof(msg), "Actual numActions %d equals Expected %d", g_res.numActions, g_exp.numActions);
    print_testPassed(msg);
  }

  return testPassed;

}

int main() {
  int testPassed = 1;
  srand(time(NULL));

  printf("***************************************\n");
  printf("*         Testing: Village Card   \n");
  printf("***************************************\n\n");

  print_testName("Test Actions = 0");
  if (!(test_Actions(0))) {
    testPassed = 0;
  }

  print_testName("Test Actions = 1");
  if (!(test_Actions(1))) {
    testPassed = 0;
  }

  print_testName("Test handCount = 0");
  if (!test_handCount(0)) {
    testPassed = 0;
  }

  print_testName("Test handCount = 1");
  if (!test_handCount(1)) {
    testPassed = 0;
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
