#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

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
    print_testPassed("When current player is last player, next player is first player");
  }

  /* All tests passed */
  if (testPassed) {
    print_testPassed("Next player equals expected result");
  }

  return testPassed;
}

/* Validate Game State reset */
int test_resetGameState() {
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
