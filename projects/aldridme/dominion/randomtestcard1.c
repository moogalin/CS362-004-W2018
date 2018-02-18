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


/* Test Oracle: Verify 3 cards gained to hand */
int assertThreeGainedHand(struct gameState g_exp, struct gameState g_res, int player) {
  g_exp.handCount[player] = g_exp.handCount[player] + 2;

  if (g_res.handCount[player] != g_exp.handCount[player]) {
    return 0;
  }
  return 1;
}

/* Test Oracle: Verify 1 card gained to discard */
int assertOneGainedDiscard(struct gameState g_exp, struct gameState g_res, int player) {
  g_exp.discardCount[player]++;

  if (g_res.discardCount[player] != g_exp.discardCount[player]) {
    return 0;
  }
  return 1;
}

/* Test Oracle: Verify 3 cards lost from deck */
int assertThreeLostDeck(struct gameState g_exp, struct gameState g_res, int player) {
  g_exp.deckCount[player] = g_exp.deckCount[player] - 3;

  if (g_res.deckCount[player] != g_exp.deckCount[player]) {
    return 0;
  }
  return 1;
}

void randomTestIteration(int * hand, int * discard, int * deck) {

    int i, player, handPos;
    int numPlayers = ((rand() % 2) + 2);
    struct gameState g_res, g_exp;
    initializeGame(numPlayers, k, rand() % 100 + 1,  &g_res);

    /* Initialize necessary (used) gameState attributes */
    g_res.whoseTurn = rand() % (numPlayers - 1);
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

    /* Initialize random position and assign Smithy card to it */
    handPos = rand() % g_res.handCount[player] - 1;

    if (handPos < 0) {
      handPos = 0;
    }

    g_res.hand[player][handPos] = CARD;

    //Copy gameStates
    copyGameState(&g_res, &g_exp);

    //Play Smithy
    play_smithy(player, &g_res, handPos);

    /* Test Oracles */
    //Assert hand contains 3 additional cards minus smithy played
    if (!assertThreeGainedHand(g_exp, g_res, player)) {
      (*hand)++;
    }

    //Assert discard contains 1 additional card
    if (!assertOneGainedDiscard(g_exp, g_res, player)) {
      (*discard)++;
    }

    //Assert deck pile contains 3 less cards
    if (!assertThreeLostDeck(g_exp, g_res, player)) {
      (*deck)++;
    }

  }



int main() {
  int i;
  int threeGainedHandFails = 0;
  int oneGainedDiscardFails = 0;
  int threeLostDeckFails = 0;
  time_t timeNow = time(NULL);
  char msg[255] = {'\0'};

  srand(timeNow);

  printf("***************************************\n");
  printf("*         Testing: Smithy Card   \n");
  printf("***************************************\n\n");

  printf("Srand Seed: %s\n", ctime(&timeNow));

  for (i = 0; i < ITERATIONS; i++) {
    randomTestIteration(&threeGainedHandFails, &oneGainedDiscardFails, &threeLostDeckFails);
  }

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "Actual handCount did not equal expected %d out of %d times.", threeGainedHandFails, ITERATIONS);
  print_testFailed(msg);

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "Actual discardCount did not equal expected %d out of %d times.", oneGainedDiscardFails, ITERATIONS);
  print_testFailed(msg);

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "Actual deckCount did not equal expected %d out of %d times.", threeLostDeckFails, ITERATIONS);
  print_testFailed(msg);


  printf("***************************************\n\n");

  return 0;
}
