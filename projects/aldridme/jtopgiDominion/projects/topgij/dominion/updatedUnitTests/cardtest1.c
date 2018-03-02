#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CARD smithy

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

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
    snprintf(msg, sizeof(msg), "Actual handCount %d does not equal Expected %d", g_res.handCount[player], g_exp.handCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual handCount %d equals Expected %d", g_res.handCount[player], g_exp.handCount[player]);
    print_testPassed(msg);
  }

  //Assert discard contains 1 additional card
  g_exp.discardCount[player]++;
  if (g_res.discardCount[player] != g_exp.discardCount[player]) {
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual discardCount %d does not equal Expected %d", g_res.discardCount[player], g_exp.discardCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual discardCount %d equals Expected %d", g_res.discardCount[player], g_exp.discardCount[player]);
    print_testPassed(msg);
  }

  //Assert deck pile contains 3 less cards
  g_exp.deckCount[player] = g_exp.deckCount[player] - 3;
  if (g_res.deckCount[player] != g_exp.deckCount[player]) {
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
