#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CARD villager

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

int test_Actions(int numActions) {
  int card = village;
  int testPassed = 1;
  char msg[255] = {'\0'};
  int player, bonus, choice1, choice2, choice3, handPos = 0;
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
  snprintf(msg, sizeof(msg), "Verify Actions increases by 2");
  print_testName(msg);


  copyGameState(&g_res, &g_exp);

  cardEffect(card, choice1, choice2, choice3, &g_res, handPos, &bonus);

  /* Verify that deck decreased by 1 */
  g_exp.deckCount[player] = g_exp.deckCount[player] - 1;

  if (g_res.deckCount[player] != g_exp.deckCount[player]){
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual deckCount %d does not equal Expected %d", g_res.deckCount[player], g_exp.deckCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual deckCount %d equals Expected %d", g_res.deckCount[player], g_exp.deckCount[player]);
    print_testPassed(msg);
  }

  /* Verify that hand stays the same */
  if (g_res.handCount[player] != g_exp.handCount[player]){
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual handCount %d does not equal Expected %d", g_res.handCount[player], g_exp.handCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual handCount %d equals Expected %d", g_res.handCount[player], g_exp.handCount[player]);
    print_testPassed(msg);
  }

  /* Verify that actions increased as expected */
  g_exp.numActions = numActions + 2;
  if (g_res.numActions != g_exp.numActions){
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual numActions %d does not equal Expected %d", g_res.numActions, g_exp.numActions);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual numActions %d equals Expected %d", g_res.numActions, g_exp.numActions);
    print_testPassed(msg);
  }

  return testPassed;

}

int test_handCount(int handCount) {
  int card = village;
  int testPassed = 1;
  char msg[255] = {'\0'};
  int player, bonus, choice1, choice2, choice3, handPos= 0;
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
  snprintf(msg, sizeof(msg), "Verify HandCount stays the same (1 drawn card, 1 discarded card)");
  print_testName(msg);

  copyGameState(&g_res, &g_exp);

  cardEffect(card, choice1, choice2, choice3, &g_res, handPos, &bonus);

  /* Verify that deck decreased by 1 */
  g_exp.deckCount[player] = g_exp.deckCount[player] - 1;

  if (g_res.deckCount[player] != g_exp.deckCount[player]){
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual deckCount %d does not equal Expected %d", g_res.deckCount[player], g_exp.deckCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual deckCount %d equals Expected %d", g_res.deckCount[player], g_exp.deckCount[player]);
    print_testPassed(msg);
  }

  /* Verify that hand stays same */
  if (g_res.handCount[player] != g_exp.handCount[player]){
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual handCount %d does not equal Expected %d", g_res.handCount[player], g_exp.handCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual handCount %d equals Expected %d", g_res.handCount[player], g_exp.handCount[player]);
    print_testPassed(msg);
  }

  /* Verify that actions increased as expected */
  g_exp.numActions = g_exp.numActions + 2;
  if (g_res.numActions != g_exp.numActions){
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual numActions %d does not equal Expected %d", g_res.numActions, g_exp.numActions);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual numActions %d equals Expected %d", g_res.numActions, g_exp.numActions);
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
