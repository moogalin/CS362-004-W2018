#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

int test_noBuys() {
  int testPassed = 1;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Ensure current player has no buys*/
  g_res.numBuys = 0;

  /* Give at least one supply to card, then buy*/
  g_res.supplyCount[province] = 1;

  /* Copy game state */
  copyGameState(&g_res, &g_exp);

  /* Attempt buy */
  buyCard(province, &g_res);

  /* Validate game state has not changed with unsuccessful buy*/
  if(!gameStatesEqual(&g_res, &g_exp)){
    testPassed = 0;
    print_testFailed("Purchase with no buys should not change game state");
  }
  else {
    print_testPassed("Purchase with no buys didn't change game state");
  }

  return testPassed;
}

int test_noSupplies() {
  int testPassed = 1;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Ensure that supply of card is zero*/
  g_res.supplyCount[province] = 0;

  /* Copy game state */
  copyGameState(&g_res, &g_exp);

  /* Attempt buy */
  buyCard(province, &g_res);

  /* Validate game state has not changed without supplies*/
  if(!gameStatesEqual(&g_res, &g_exp)){
    testPassed = 0;
    print_testFailed("Purchase with no supply of card should not change game state");
  }
  else {
    print_testPassed("Purchase with no supply of card didn't change game state");
  }

  return testPassed;
}

int test_notEnoughCoins() {
  int testPassed = 1;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Ensure that coins < cost of card*/
  g_res.coins = 2;

  /* Copy game state */
  copyGameState(&g_res, &g_exp);

  /* Attempt buy */
  buyCard(mine, &g_res); //mine costs 5 which is greater than 2 coins

  /* Validate game state has not changed without supplies*/
  if(!gameStatesEqual(&g_res, &g_exp)){
    testPassed = 0;
    print_testFailed("Purchase with less coins than cost of card should not change game state");
  }
  else {
    print_testPassed("Purchase with less coins than cost of card didn't change game state");
  }

  return testPassed;
}

int test_buyCard() {
  int testPassed = 1;
  int player;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Ensure at least one buy, one supply, and enough coins */
  g_res.whoseTurn = (rand() % MAX_PLAYERS);
  player = g_res.whoseTurn;
  g_res.numBuys = (rand() % 5) + 1;
  g_res.supplyCount[gold] = (rand() % 5) + 1; // Costs 6
  g_res.coins = (rand() % 6) + 6;
  g_res.discardCount[player] = 5;
  g_res.discard[player][g_res.discardCount[player] - 1] = province; // Last Card before buy


  /* Copy game state */
  copyGameState(&g_res, &g_exp);

  /* Attempt buy */
  buyCard(gold, &g_res);

  /* Validate discard count incremented*/
  if (g_res.discardCount[player] != g_exp.discardCount[player] + 1) {
    testPassed = 0;
    print_testFailed("Player does not have additional card in discard pile");
  }
  else {
    /* Validate card is in discard */
    if (g_res.discard[player][g_res.discardCount[player] - 1] == gold) {
      print_testPassed("Player received card in discard pile");
    }
    else {
      testPassed = 0;
      print_testFailed("Player does not have purchased card in discard pile");
    }
  }

  /* Validate supply of gold card was reduced */
  g_exp.supplyCount[gold]--;
  if (g_res.supplyCount[gold] != (g_exp.supplyCount[gold])) {
    testPassed = 0;
    print_testFailed("Supply of bought card not reduced by one");
  }
  else {
    print_testPassed("Supply of bought card reduced by one");
  }

  /* Validate total coins decreased by bought card cost */
  g_exp.coins = g_exp.coins - 6; // Cost of Gold
  if (g_res.coins != g_exp.coins) {
    testPassed = 0;
    print_testFailed("Total coins did not decrease with purchase");
  }
  else {
    print_testPassed("Total coins decreased with purchase");
  }

  return testPassed;
}

int main() {
  srand(time(0));

  int testsPassed = 1;

  printf("***************************************\n");
  printf("*         Testing: buyCard()   \n");
  printf("***************************************\n\n");

  if (!test_noBuys()) {
    testsPassed = 0;
  }

  if (!test_noSupplies()) {
    testsPassed = 0;
  }

  if (!test_notEnoughCoins()) {
    testsPassed = 0;
  }

  if (!test_buyCard()) {
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
