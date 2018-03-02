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


/* Test Oracle: Only assert deck count if no shuffle occurred */
int assertDeckCount(int flag, struct gameState g_exp, struct gameState g_res, int player) {

  /* Test if no shuffle occurred */
  if (flag == 3) {
    if (g_res.deckCount[player] == (g_exp.deckCount[player] - 2))
      return 1;
    else return 0;
  }
  return -1;
}

/* Test Oracle: Assert that discard pile does not contain a treasure */
int assertDiscard(int flag, struct gameState g_exp, struct gameState g_res, int player) {
  int i;

  for (i = 0; i < g_res.discardCount[player]; i++) {
    if (g_res.discard[player][i] == gold)
      return 0;
    else if (g_res.discard[player][i] == silver)
      return 0;
    else if (g_res.discard[player][i] == copper)
      return 0;
  }

  return 1;

}

/* Test Oracle: Assert that hand increases (or not) as expected */
int assertHandCount(int flag, struct gameState g_exp, struct gameState g_res, int player) {

  // One treasure in hand, hand did not increase
  if ((flag == 1) | (flag == 2)) {
    if (g_res.handCount[player] != g_exp.handCount[player]) {
      return 0;
    }
    return 1;
  }

  // Two treasure in hand, hand increases by 1
  if (flag <= 5 && flag >= 3) {
    if (g_res.handCount[player] != (g_exp.handCount[player] + 1)) {
      return 0;
    }
    return 1;
  }

  return 0;

}

/* Test Oracle: Assert that one+ treasures are gained to hand */
int assertTreasureInHand(int flag, struct gameState g_exp, struct gameState g_res, int player) {
  // One treasure in hand
  if ((flag == 1) | (flag == 2)) {
    if (g_res.hand[player][g_res.handCount[player] - 1] == copper) {
      return 1;
    }
    else if (g_res.hand[player][g_res.handCount[player] - 1] == silver) {
      return 1;
    }
    else if (g_res.hand[player][g_res.handCount[player] - 1] == gold) {
      return 1;
    }
    else {
      return 0;
    }
  }

  // Two treasure in hand
  if (flag <= 5 && flag >= 3) {
    if (g_res.hand[player][g_res.handCount[player] - 1] == copper) {

      if (g_res.hand[player][g_res.handCount[player] - 2] == copper) {
        return 1;
      }
      else if (g_res.hand[player][g_res.handCount[player] - 2] == silver) {
        return 1;
      }
      else if (g_res.hand[player][g_res.handCount[player] - 2] == gold) {
        return 1;
      }
    }
    else if (g_res.hand[player][g_res.handCount[player] - 1] == silver) {

      if (g_res.hand[player][g_res.handCount[player] - 2] == copper) {
        return 1;
      }
      else if (g_res.hand[player][g_res.handCount[player] - 2] == silver) {
        return 1;
      }
      else if (g_res.hand[player][g_res.handCount[player] - 2] == gold) {
        return 1;
      }
    }
    else if (g_res.hand[player][g_res.handCount[player] - 1] == gold) {

      if (g_res.hand[player][g_res.handCount[player] - 2] == copper) {
        return 1;
      }
      else if (g_res.hand[player][g_res.handCount[player] - 2] == silver) {
        return 1;
      }
      else if (g_res.hand[player][g_res.handCount[player] - 2] == gold) {
        return 1;
      }
    }
  }

  // Error
  return 0;
}

/* Generate random game state and call Test Oracles against it */
void randomTestIteration(int * treasures, int * discard, int * hand, int * deck, int * deckTotals) {

  int i, player, handPos;
  int random;
  int treasure;
  int temp;
  int flag = -1;
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
    //printf("initialized hand\n");
  }
  for (i = 0; i < g_res.deckCount[player]; i++) {
    g_res.deck[player][i] = k[rand() % 9];
    //printf("initiliazed deck\n");
  }
  for (i = 0; i < g_res.discardCount[player]; i++) {
    g_res.discard[player][i] = k[rand() % 9];
    //printf("initialized discard\n");
  }
  for (i = 0; i < g_res.playedCardCount; i++) {
    g_res.playedCards[i] = k[rand() % 9];
    //printf("initialized playcount\n");
  }

  // Initialize random hand position and assign adventurer to it
  handPos = rand() % g_res.handCount[player] - 1;

  if (handPos < 0) {
    handPos = 0;
  }

  g_res.hand[player][handPos] = CARD;

  // Randomly place treasure into deck and or discard
  random = rand() % 2; // 0 1 or 2 treasure placed into deck

  /* Randomly place one treasure in either deck or discard */
  if (random == 1) {
    random = rand() % 2;
    /* place single treasure in deck */
    if (random == 0) {
      flag = 1;
      random = rand() % g_res.deckCount[player]; //random location
      treasure = (rand() % 3) + 4; //enums 4 5 or 6 are treasure cards
      g_res.deck[player][random] = treasure;
    }
    /* place single treasure in discard */
    else {
      flag = 2;
      random = rand() % g_res.discardCount[player]; //random location
      treasure = (rand() % 3) + 4; //enums 4 5 or 6 are treasure cards
      g_res.discard[player][random] = treasure;
    }

  }

  /* Randomly place one+ treasure in either deck or discard */
  else {
    random = rand() % 3;
    /* place both treasures in deck */
    if (random == 0) {
      flag = 3;
      random = rand() % g_res.deckCount[player]; //random location
      temp = random;
      treasure = (rand() % 3) + 4; //enums 4 5 or 6 are treasure cards
      g_res.deck[player][random] = treasure;

      // Make sure second treasure doesn't replace first
      while(1) {
        random = rand() % g_res.deckCount[player]; //random location
        if (random != temp) break;
        /* Deck doesn't have more than one card in it */
        if (g_res.deckCount[player] <= 1) {
          flag = 1;
          break;
        }
      }
      treasure = (rand() % 3) + 4;
      g_res.deck[player][random] = treasure;
    }
    /* place both treasures in discard */
    else if (random == 1) {
      flag = 4;
      random = rand() % g_res.discardCount[player]; //random location
      temp = random;
      treasure = (rand() % 3) + 4; //enums 4 5 or 6 are treasure cards
      g_res.discard[player][random] = treasure;

      // Make sure second treasure doesn't replace first
      while(1) {
        random = rand() % g_res.discardCount[player]; //random location
        if (random != temp) break;
        /* Discard does not have more than one card in it */
        if (g_res.discardCount[player] <= 1) {
          flag = 2;
          break;
        }
      }
      treasure = (rand() % 3) + 4;
      g_res.discard[player][random] = treasure;
    }
    /* Place one treasure in deck and one in discard */
    else {
      flag = 5;
      //Random discard location
      random = rand() % g_res.discardCount[player]; //random location
      treasure = (rand() % 3) + 4;
      g_res.discard[player][random] = treasure;

      //Random deck location
      random = rand() % g_res.deckCount[player];
      treasure = (rand() % 3) + 4;
      g_res.deck[player][random] = treasure;
    }
  }

  //Copy gameStates
  copyGameState(&g_res, &g_exp);

  //Play adventurer
  //play_adventurer(&g_res, 0, player, -10);
  cardEffect(adventurer, 0, 0, 0, &g_res, 0, 0);

  /* Test Oracles */
  if (!assertTreasureInHand(flag, g_exp, g_res, player)) {
    (*treasures)++;
  }

  if (!assertDiscard(flag, g_exp, g_res, player)) {
    (*discard)++;
  }

  if (!assertHandCount(flag, g_exp, g_res, player)) {
    (*hand)++;
  }

  /* Deck count oracle only called in the event both treasures are in deck */
  temp = assertDeckCount(flag, g_exp, g_res, player);
  if (temp == 1) {
    (*deck)++;
    (*deckTotals)++;
  }
  else if (temp == 0) {
    (*deckTotals)++;
  }
}

int main() {
  int i;
  int treasureCount = 0;
  int discardCount = 0;
  int handCount = 0;
  int deckCount = 0;
  int deckTotalTests = 0;
  time_t timeNow = time(NULL);
  char msg[255] = {'\0'};

  srand(timeNow);
  printf("***************************************\n");
  printf("*         Testing: Adventure Card   \n");
  printf("***************************************\n\n");

  printf("Srand Seed: %s\n", ctime(&timeNow));

  for (i = 0; i < ITERATIONS; i++) {
    randomTestIteration(&treasureCount, &discardCount, &handCount, &deckCount, &deckTotalTests);
  }

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "Actual treasure in hand did not equal expected %d out of %d times.", treasureCount, ITERATIONS);
  print_testFailed(msg);

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "Actual hand count did not equal expected %d out of %d times.", handCount, ITERATIONS);
  print_testFailed(msg);

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "Actual discard count did not equal expected %d out of %d times.", discardCount, ITERATIONS);
  print_testFailed(msg);

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "Actual deck count did not equal expected %d out of %d times.", deckCount, deckTotalTests);
  print_testFailed(msg);

  printf("***************************************\n\n");

  return 0;
}
