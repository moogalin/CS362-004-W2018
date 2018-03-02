#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CARD mine

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

int test_invalidChoice1() {
  int card = mine;
  int testPassed = 1;
  int i, player, choice1, choice2, choice3, handPos, coinBonus = 0;
  struct gameState g_res, g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Initialize necessary (used) gameState attributes */
  g_res.whoseTurn = 0;
  player = g_res.whoseTurn;
  g_res.handCount[player] = 5;
  g_res.deckCount[player] = 5;
  g_res.discardCount[player] = 5;
  g_res.playedCardCount = 0;

  //Initialize hand to Mine cards to prevent garbage values
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = card;
    g_res.deck[player][i] = card;
    g_res.discard[player][i] = card;
    g_res.playedCards[i] = -1;
  }

  handPos = 4;

  /**
   Test 1: Choice 1 cannot be trashed
   **/
  print_testName("Cannot trash non-treasure cards");
  choice1 = card;
  g_res.hand[player][handPos] = province; //non-treasure card

  copyGameState(&g_res, &g_exp);

  //Play Mine
  cardEffect(card, choice1, choice2, choice3, &g_res, handPos, &coinBonus);

  /* Verify gameState did not change */
  if (!gameStatesEqual(&g_exp, &g_res)) {
    testPassed = 0;
    print_testFailed("Game state changed on invalid trash choice");
  }
  else {
    print_testPassed("Game state didn't change on invalid trash choice");
  }
  return testPassed;
}

int test_invalidChoice2() {
  int card = mine;
  int testPassed = 1;
  int i, player, choice1, choice2, choice3, handPos, coinBonus = 0;
  struct gameState g_res, g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Initialize necessary (used) gameState attributes */
  g_res.whoseTurn = 0;
  player = g_res.whoseTurn;
  g_res.handCount[player] = 5;
  g_res.deckCount[player] = 5;
  g_res.discardCount[player] = 5;
  g_res.playedCardCount = 0;

  //Initialize hand to Mine cards to prevent garbage values
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = card;
    g_res.deck[player][i] = card;
    g_res.discard[player][i] = card;
    g_res.playedCards[i] = -1;
  }

  handPos = 4;

  /**
   Test 2: Choice 2 is an invalid card choice
   **/
  print_testName("Cannot gain non-treasure cards");
  choice1 = copper; //valid
  choice2 = curse; //invalid
  g_res.hand[player][handPos] = copper; //valid


  copyGameState(&g_res, &g_exp);

  //Play Mine
  cardEffect(card, choice1, choice2, choice3, &g_res, handPos, &coinBonus);

  /* Verify gameState did not change */
  if (!gameStatesEqual(&g_exp, &g_res)) {
    testPassed = 0;
    print_testFailed("Game state changed on invalid gain choice");
  }
  else {
    print_testPassed("Game state didn't change on invalid gain choice");
  }

  return testPassed;
}

int test_Choice2GreaterThanChoice1() {
  int card = mine;
  int testPassed = 1;
  int i, player, choice1, choice2, choice3, handPos, coinBonus = 0;
  struct gameState g_res, g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Initialize necessary (used) gameState attributes */
  g_res.whoseTurn = 0;
  player = g_res.whoseTurn;
  g_res.handCount[player] = 5;
  g_res.deckCount[player] = 5;
  g_res.discardCount[player] = 5;
  g_res.playedCardCount = 0;

  //Initialize hand to Mine cards to prevent garbage values
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = card;
    g_res.deck[player][i] = card;
    g_res.discard[player][i] = card;
    g_res.playedCards[i] = -1;
  }

  handPos = 4;

  /**
   Test 2: Choice 2 costs >3 more than Choice 1
   **/
  print_testName("Cannot get treasure worth > 3 more than treasure in hand");
  choice1 = copper; //cost is 0
  choice2 = gold; //cost is 6
  g_res.hand[player][choice1] = copper; //valid


  copyGameState(&g_res, &g_exp);

  //Play Mine
  cardEffect(card, choice1, choice2, choice3, &g_res, handPos, &coinBonus);

  /* Verify gameState did not change */
  if (!gameStatesEqual(&g_exp, &g_res)) {
    testPassed = 0;
    print_testFailed("Game state changed purchasing gold from copper");
  }
  else {
    print_testPassed("Game state didn't change purchasing gold from copper");
  }

  return testPassed;
}

int test_validChoices() {
  int card = mine;
  int testPassed = 1;
  char msg[255] = {'\0'};
  int i, player, choice1, choice2, choice3, handPos, coinBonus = 0;
  struct gameState g_res, g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Initialize necessary (used) gameState attributes */
  g_res.whoseTurn = 0;
  player = g_res.whoseTurn;
  g_res.handCount[player] = 5;
  g_res.deckCount[player] = 5;
  g_res.discardCount[player] = 5;
  g_res.playedCardCount = 0;

  //Initialize hand to Mine cards to prevent garbage values
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = card;
    g_res.deck[player][i] = card;
    g_res.discard[player][i] = card;
    g_res.playedCards[i] = -1;
  }

  handPos = 4;

  /**
   Test 2: Choice 2 costs >3 more than Choice 1
   **/
  print_testName("Can get treasure worth <= 3 more than treasure in hand");
  choice1 = copper; //cost is 0
  choice2 = silver; //cost is 3
  g_res.hand[player][handPos] = copper; //valid


  copyGameState(&g_res, &g_exp);

  //Play Mine
  cardEffect(card, choice1, choice2, choice3, &g_res, handPos, &coinBonus);

  /* Verify gameState changed */
  if (gameStatesEqual(&g_exp, &g_res)) {
    testPassed = 0;
    print_testFailed("Game state didn't change purchasing silver from copper");
  }
  else {
    print_testPassed("Game state changed purchasing silver from copper");
  }

  /* Verify card is gained to hand */
  if (g_res.handCount[player] != g_exp.handCount[player]) {
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual handCount %d does not equal Expected %d", g_res.handCount[player], g_exp.handCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual handCount %d equals expected", g_res.handCount[player]);
    print_testPassed(msg);
  }

  /* Verify card is gained to discard */
  g_exp.discardCount[player]++; //Expect additional discarded card
  if (g_res.discardCount[player] != g_exp.discardCount[player]) {
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual discardCount %d does not equal Expected %d", g_res.discardCount[player], g_exp.discardCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual discardCount %d equals expected", g_res.discardCount[player]);
    print_testPassed(msg);
  }

  /* Verify card is trashed */
  g_exp.playedCardCount++; //Expect additional discarded card
  if (g_res.playedCardCount != g_exp.playedCardCount) {
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Actual playedCards %d does not equal Expected %d", g_res.playedCardCount, g_exp.playedCardCount);
    print_testFailed(msg);
  }
  else {
    if (g_res.playedCards[g_res.playedCardCount - 1] != copper) {
      memset(msg, 0, sizeof(msg));
      snprintf(msg, sizeof(msg), "Actual trashed card %d equals expected", g_res.playedCards[g_res.playedCardCount - 1]);
      print_testFailed(msg);
    }

    else {
      memset(msg, 0, sizeof(msg));
      snprintf(msg, sizeof(msg), "Actual trashed card %d equals expected and trashed count is as expected", g_res.playedCards[g_res.playedCardCount - 1]);
      print_testPassed(msg);
    }
  }


  return testPassed;
}

int main() {
  int testPassed = 1;
  srand(time(NULL));

  printf("***************************************\n");
  printf("*         Testing: Mine Card   \n");
  printf("***************************************\n\n");


  if (!test_invalidChoice1()) {
    testPassed = 0;
  }

  if (!test_invalidChoice2()) {
    testPassed = 0;
  }

  if (!test_Choice2GreaterThanChoice1()) {
    testPassed = 0;
  }

  if (!test_validChoices()) {
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
