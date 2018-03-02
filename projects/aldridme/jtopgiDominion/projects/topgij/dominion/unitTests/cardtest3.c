#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CARD adventurer

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

int test_TwoTreasureInDeck() { //No shuffle needed
  int card = adventurer;
  int testPassed = 1;
  char msg[255] = {'\0'};
  int i, player, choice1, choice2, choice3, handPos, coinBonus = 0;
  struct gameState g_res, g_exp;

  print_testName("Verify that two treasures in deck works as expected");

  /* Initialize necessary (used) gameState attributes */
  g_res.numPlayers = 2;
  g_res.whoseTurn = 0;
  player = g_res.whoseTurn;
  g_res.handCount[player] = 5;
  g_res.deckCount[player] = 5;

  // Give the player non-treasure cards in hand to test against
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = province;
    g_res.deck[player][i] = copper;
  }

  // Need adventurer in hand
  g_res.hand[player][g_res.handCount[player] - 1] = adventurer;

  copyGameState(&g_res, &g_exp);

  //play_adventurer(&g_res, 0, g_res.whoseTurn, 0);

  cardEffect(card, choice1, choice2, choice3, &g_res, handPos, &coinBonus);

  /* Verify that deck decreased by 2 */
  g_exp.deckCount[player] = g_exp.deckCount[player] - 2;

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

  /* Verify that treasure is in hand */
  if (g_res.hand[player][g_res.handCount[player] - 2] != g_res.hand[player][g_res.handCount[player] - 1]){
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Last two in hand are: %d and %d", g_res.hand[player][g_res.handCount[player] - 2], g_res.hand[player][g_res.handCount[player] - 1]);
    print_testFailed(msg);
  }
  else {
    if (g_res.hand[player][g_res.handCount[player] - 2] == copper) {
      memset(msg, 0, sizeof(msg));
      snprintf(msg, sizeof(msg), "Last two in hand are: %d and %d", g_res.hand[player][g_res.handCount[player] - 2], g_res.hand[player][g_res.handCount[player] - 1]);
      print_testPassed(msg);
    }
    else {
      memset(msg, 0, sizeof(msg));
      snprintf(msg, sizeof(msg), "Last two in hand are: %d and %d", g_res.hand[player][g_res.handCount[player] - 2], g_res.hand[player][g_res.handCount[player] - 1]);
      print_testFailed(msg);
    }
  }

  /* Verify that hand increased by 1 (1 discard, 2 cards gained) */
  g_exp.handCount[player]++;
  if (g_res.handCount[player] != g_exp.handCount[player]){
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Handcount is %d and expected %d", g_res.handCount[player], g_exp.handCount[player]);
    print_testFailed(msg);
  }
  else {
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Handcount is %d and expected %d", g_res.handCount[player], g_exp.handCount[player]);
    print_testPassed(msg);
  }

  return testPassed;

}

int test_noTreasureInDeck() { //No shuffle needed
  int card = adventurer;
  int testPassed = 1;
  char msg[255] = {'\0'};
  int shuffled, i, player, choice1, choice2, choice3, handPos, coinBonus = 0;
  struct gameState g_res, g_exp;

  print_testName("Verify that no treasure in deck works as expected");

  /* Initialize necessary (used) gameState attributes */
  g_res.numPlayers = 2;
  g_res.whoseTurn = 0;
  player = g_res.whoseTurn;
  g_res.handCount[player] = 25;
  g_res.deckCount[player] = 2;

  // Give the player treasure cards in hand to test against and non treasure in deck
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = copper;
  }
  for (i = 0; i < g_res.deckCount[player]; i++) {
    g_res.deck[player][i] = province;
  }


  // Need adventurer in hand
  g_res.hand[player][g_res.handCount[player] - 1] = adventurer;

  copyGameState(&g_res, &g_exp);

  //play_adventurer(&g_res, 0, g_res.whoseTurn, 0);
  cardEffect(card, choice1, choice2, choice3, &g_res, handPos, &coinBonus);


  /* Verify that deck is different (shuffled) */
  for (i = 0; i < g_res.deckCount[player]; i++) {
    if (g_res.deck[player][i] != province) {
      shuffled = 1;
      break;
    }
  }

  if (!shuffled){
    testPassed = 0;
    print_testFailed("Deck does not contains different cards, unsuccessfully shuffled");
  }
  else {
    print_testPassed("Deck contains different cards, successfully shuffled");
  }

  /* Verify that treasure is in hand */
  if (g_res.hand[player][g_res.handCount[player] - 2] != g_res.hand[player][g_res.handCount[player] - 1]){
    testPassed = 0;
    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg), "Last two in hand are: %d and %d", g_res.hand[player][g_res.handCount[player] - 2], g_res.hand[player][g_res.handCount[player] - 1]);
    print_testFailed(msg);
  }
  else {
    if (g_res.hand[player][g_res.handCount[player] - 2] == copper) {
      memset(msg, 0, sizeof(msg));
      snprintf(msg, sizeof(msg), "Last two in hand are: %d and %d", g_res.hand[player][g_res.handCount[player] - 2], g_res.hand[player][g_res.handCount[player] - 1]);
      print_testPassed(msg);
    }
    else {
      memset(msg, 0, sizeof(msg));
      snprintf(msg, sizeof(msg), "Last two in hand are: %d and %d", g_res.hand[player][g_res.handCount[player] - 2], g_res.hand[player][g_res.handCount[player] - 1]);
      print_testFailed(msg);
    }
  }

  /* Verify that if deck/hand decreased in size, discard increased */
  int deckPlusHand_after = g_res.deckCount[player] + g_res.handCount[player];
  int deckPlusHand_before = 27;

  if (deckPlusHand_after < deckPlusHand_before) {
    // Verify discard increased
    if (g_res.discardCount[player] > g_exp.discardCount[player]) {
      print_testPassed("Discard increased when deck/hand decreased");
    }
    else {
      print_testFailed("Discard didn't increase as expected when deck/hand decreased");
    }
  }
  return testPassed;

}

int main() {
  int testPassed = 1;
  srand(time(NULL));

  printf("***************************************\n");
  printf("*         Testing: Adventure Card   \n");
  printf("***************************************\n\n");


  if (!test_TwoTreasureInDeck()) {
    testPassed = 0;
  }

  if (!test_noTreasureInDeck()) {
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
