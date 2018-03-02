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

int test_coins(int coin_denom, int coin_value) {
  int testPassed = 1;
  int i, player, coins;
  char * coinName;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Initialize relevant values */
  g_res.whoseTurn = rand() % MAX_PLAYERS;
  player = g_res.whoseTurn;
  g_res.coins = rand() % 100; //Ensure that this random number doesn't persist
  g_res.handCount[player] = (rand() % 10) + 5; //Random number between 5 and 14


  if (coin_denom == copper){
    coinName = "copper";
  }
  else if (coin_denom == silver){
    coinName = "silver";
  }
  else if (coin_denom == gold){
    coinName = "gold";
  }

  /* Make all cards province (non-treasure) */
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = province;
  }

  /* Make one or more coin_denom cards */
  for (i = 0; i < g_res.handCount[player]; i++ ) {
    g_res.hand[player][i] = coin_denom;
  }

  /* Copy gameState */
  copyGameState(&g_res, &g_exp);

  /* Update Coins with no bonus */
  updateCoins(player, &g_res, 0);

  /* Calculated expected value */
  coins = 0;
  for (i = 0; i < g_exp.handCount[player]; i++) {
    if (g_exp.hand[player][i] == coin_denom) {
      coins = coins + coin_value;
    }
  }

  if (g_res.coins != coins) {
    testPassed = 0;
    char msg[100] = {'\0'};
    snprintf(msg, sizeof(msg),"Expected %d  %s Actual %d are not equal.", coins,coinName, g_res.coins);
    print_testFailed(msg);
  }
  else {
    char msg[100] = {'\0'};
    snprintf(msg, sizeof(msg),"Expected %s coins and actual coins are equal.", coinName);
    print_testPassed(msg);
  }

  return testPassed;
}

int test_noCoins() {
  int testPassed = 1;
  int i, player;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Initialize relevant values */
  g_res.whoseTurn = rand() % MAX_PLAYERS;
  player = g_res.whoseTurn;
  g_res.coins = 0;
  g_res.handCount[player] = (rand() % 10) + 5; //Random number between 5 and 14

  /* Make all cards province (non-treasure) */
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = province;
  }

  /* Copy gameState */
  copyGameState(&g_res, &g_exp);

  /* With no coins, ensure game state does not change */
  if (!gameStatesEqual(&g_res, &g_exp)) {
    testPassed = 0;
    print_testFailed("Game state changed with no coins in hand.");
  }
  else {
    print_testPassed("Game state didn't change with no coins in hand.");
  }

  return testPassed;
}

int main() {
  srand(time(0));

  int testsPassed = 1;

  printf("***************************************\n");
  printf("*         Testing: updateCoins()   \n");
  printf("***************************************\n\n");

  if (!test_coins(copper, 1)){
    testsPassed = 0;
  }

  if (!test_coins(silver, 2)){
    testsPassed = 0;
  }

  if (!test_coins(gold, 3)){
    testsPassed = 0;
  }

  if (!test_noCoins()){
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
