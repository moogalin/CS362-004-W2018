#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CARD village

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

int assertDeckCount(struct gameState g_exp, struct gameState g_res, int player) {
  /* Verify that deck decreased by 1 */
  g_exp.deckCount[player] = g_exp.deckCount[player] - 1;

  if (g_res.deckCount[player] != g_exp.deckCount[player]){
    //memset(msg, 0, sizeof(msg));
    //snprintf(msg, sizeof(msg), "Actual deckCount %d does not equal Expected %d", g_res.deckCount[player], g_exp.deckCount[player]);
    //print_testFailed(msg);
    return 0;
  }
  return 1;
}

int assertHandCount(struct gameState g_exp, struct gameState g_res, int player) {
  /* Verify that hand stays the same */
  if (g_res.handCount[player] != g_exp.handCount[player]){
    //memset(msg, 0, sizeof(msg));
    //snprintf(msg, sizeof(msg), "Actual handCount %d does not equal Expected %d", g_res.handCount[player], g_exp.handCount[player]);
    //print_testFailed(msg);
    return 0;
  }
  return 1;
}

int assertActionCount(struct gameState g_exp, struct gameState g_res, int player) {
  /* Verify that actions increased as expected */
  g_exp.numActions = g_exp.numActions + 2;
  if (g_res.numActions != g_exp.numActions){
    //memset(msg, 0, sizeof(msg));
    //snprintf(msg, sizeof(msg), "Actual numActions %d does not equal Expected %d", g_res.numActions, g_exp.numActions);
    //print_testFailed(msg);
    return 0;
  }
  return 1;
}

void randomTestIteration(int * deck, int * hand, int * actions) {
  int i, player, handPos;
  int numPlayers = ((rand() % 3) + 2);
  struct gameState g_res, g_exp;
  initializeGame(numPlayers, k, rand() % 100 + 1,  &g_res);

  /* Initialize necessary (used) gameState attributes */
  g_res.whoseTurn = rand() % numPlayers;
  player = g_res.whoseTurn;
  g_res.handCount[player] = rand() % (MAX_CARDS / 4) + 1;
  g_res.deckCount[player] = rand() % (MAX_CARDS / 4) + 1;
  g_res.discardCount[player] = rand() % (MAX_CARDS / 4) + 1;
  g_res.playedCardCount = rand() % (MAX_CARDS / 4) + 1;

  //Initialize random cards in hand, deck, discard, and played stacks
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = k[rand() % 9];
  }
  for (i = 0; i < g_res.deckCount[player]; i++) {
    g_res.deck[player][i] = k[rand() % 9];
  }
  for (i = 0; i < g_res.discardCount[player]; i++) {
    g_res.discard[player][i] = k[rand() % 9];
  }
  for (i = 0; i < g_res.playedCardCount; i++) {
    g_res.playedCards[i] = k[rand() % 9];
  }

  /* Initialize random position and assign Village card to it */
  handPos = rand() % g_res.handCount[player] - 1;

  if (handPos < 0) {
    handPos = 0;
  }

  g_res.hand[player][handPos] = CARD;

  /* Initialize random number of actions */
  g_res.numActions = rand() % MAX_HAND;


  //Copy gameStates
  copyGameState(&g_res, &g_exp);

  //Play village
  play_village(player, &g_res, handPos);

  /* Test Oracles */
  //Assert Deck Count decreases by one
  if (!assertDeckCount(g_exp, g_res, player)) {
    (*deck)++;
  }

  //Assert Hand Count stays the same
  if (!assertHandCount(g_exp, g_res, player)) {
    (*hand)++;
  }

  //Assert Action count increases by two
  if (!assertActionCount(g_exp, g_res, player)) {
    (*actions)++;
  }

}

int main() {
  int i;
  int deckCountFails = 0;
  int handCountFails = 0;
  int actionFails = 0;
  time_t timeNow = time(NULL);
  char msg[255] = {'\0'};

  srand(timeNow);
  printf("***************************************\n");
  printf("*         Testing: Village Card   \n");
  printf("***************************************\n\n");

  printf("Srand Seed: %s\n", ctime(&timeNow));

  for (i = 0; i < ITERATIONS; i++) {
    randomTestIteration(&deckCountFails, &handCountFails, &actionFails);
  }

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "Actual deckCount did not equal expected %d out of %d times.", handCountFails, ITERATIONS);
  print_testFailed(msg);

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "Actual handCount did not equal expected %d out of %d times.", handCountFails, ITERATIONS);
  print_testFailed(msg);

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "Actual numActions did not equal expected %d out of %d times.", actionFails, ITERATIONS);
  print_testFailed(msg);


  printf("***************************************\n\n");


  return 0;
}
