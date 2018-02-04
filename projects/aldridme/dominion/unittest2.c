#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYERS 4
#define NUM_SUPPLYCARDS 27

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

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

void print_testPassed(char s[]) {
  printf("**\n");
  printf("*       PASS: %s\n", s);
  printf("**\n\n");
}

void print_testFailed(char s[]) {
  printf("**\n");
  printf("*       FAIL: %s\n", s);
  printf("**\n\n");
}

int rand_int(int a, int b){
  int random = (rand() % (b - a + 1) + a );
  return random;
}

/* Validate whoseTurn */
int test_whoseTurn() {
  int testPassed = 1;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Game states should be duplicate */
  copyGameState(&g_res, &g_exp);

  /* Choose non-last player  */
  g_res.whoseTurn = MAX_PLAYERS - 2;
  g_exp.whoseTurn = g_res.whoseTurn;

  /* Update expected player */
  g_exp.whoseTurn++;

  endTurn(&g_res);

  /* Assert result = expected player */
  if (g_res.whoseTurn != g_exp.whoseTurn) {
    testPassed = 0;
    print_testFailed("Next player does not equal expected result");
  }
  else {
    print_testPassed("When current player is not last player, next player is not first player");
  }

  /* Choose last player and test that first player has next turn */
  g_res.whoseTurn = g_res.numPlayers - 1;


  endTurn(&g_res);

  /* Assert result = expected player */
  if (g_res.whoseTurn != 0) {
    testPassed = 0;
    print_testFailed("Next player does not equal expected result");
  }
  else {
    print_testPassed("When current player is last player, next player is first player")
  }

  /* All tests passed */
  if (testPassed) {
    print_testPassed("Next player equals expected result");
  }

  return testPassed;
}

/* Validate Game State reset */
int test_resetGameState() {
  int i;
  int testPassed = 1;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Set necessary values that should reset*/
  g_res.whoseTurn = rand() % (g_res.numPlayers - 1);
  g_res.phase = 2;
  g_res.numActions = 4;
  g_res.numBuys = 5;
  g_res.handCount[g_res.whoseTurn] = 6;

  /* Game states should be duplicate */
  copyGameState(&g_res, &g_exp);

  endTurn(&g_res);

  /* Validate previous players' hand is empty */
  if (g_res.handCount[g_exp.whoseTurn] != 0) {
    testPassed = 0;
    print_testFailed("Previous player's hand is not empty");
  }
  else {
    print_testPassed("Previous player's hand is empty");
  }

  /* Validate next player has 5 cards in hand */
  if (g_res.handCount[g_res.whoseTurn] != 5) {
    testPassed = 0;
    print_testFailed("Next player's hand does not have 5 cards");
  }
  else {
    print_testPassed("Next player's hand has 5 cards");
  }

  /* Validate next player has 1 action only */
  if (g_res.numActions != 1) {
    testPassed = 0;
    print_testFailed("Next player does not have exactly 1 action");
  }
  else {
    print_testPassed("Next player has exactly 1 action");
  }

  /* Validate next player has 1 buy only */
  if (g_res.numBuys != 1) {
    testPassed = 0;
    print_testFailed("Next player does not have exactly 1 buy");
  }
  else {
    print_testPassed("Next player has exactly 1 buy");
  }

  /* Validate next player in Phase 0 */
  if (g_res.phase != 0) {
    testPassed = 0;
    print_testFailed("Turn phase is incorrect");
  }
  else {
    print_testPassed("Turn phase is correct");
  }

  /* Validate outpost not played */
  if (g_res.outpostPlayed != 0) {
    testPassed = 0;
    print_testFailed("Outpost played not reset");
  }
  else {
    print_testPassed("Outpost played reset");
  }

  /* Validate played card count is 0 */
  if (g_res.playedCardCount != 0){
    testPassed = 0;
    print_testFailed("Played card count is not zero");
  }
  else {
    print_testPassed("Played card count is zero");
  }

  return testPassed;
}

int main() {
  srand(time(0));

  int testsPassed = 1;

  printf("***************************************\n");
  printf("*         Testing: endTurn()   \n");
  printf("***************************************\n\n");

  if (!test_whoseTurn()) {
    testsPassed = 0;
  }

  if (!test_resetGameState()) {
    testsPassed = 0;
  }

  if (testsPassed) {
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
