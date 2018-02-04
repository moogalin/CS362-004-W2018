#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PLAYERS 2
#define NUM_SUPPLYCARDS 27

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

void printGameState(struct gameState * g, char s[]) {
  int i,j;

  printf("***************************************\n");
  printf("*         GameState %s:                  \n", s);
  printf("* NumPlayers: %d", g->numPlayers);
  printf("\n* SupplyCount[treasure_map+1]: ");
  for (i=0; i < (treasure_map+1); i++)
  {
    printf("\n**  SupplyCount[%d] = %d", i, g->supplyCount[i]);
  }
  printf("\n* embargoTokens[treasure_map+1]: ");
  for (i=0; i < (treasure_map+1); i++)
  {
    printf("\n**  embargoTokens[%d] = %d", i, g->embargoTokens[i]);
  }
  printf("\n* outpostPlayed: %d", g->outpostPlayed);
  printf("\n* outpostTurn: %d", g->outpostTurn);
  printf("\n* whoseTurn: %d", g->whoseTurn);
  printf("\n* phase: %d", g->phase);
  printf("\n* numActions: %d", g->numActions);
  printf("\n* coins: %d", g->coins);
  printf("\n* numBuys: %d", g->numBuys);
  printf("\n* hand[MAX_PLAYERS][MAX_HAND]: ");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    for (j=0; j < MAX_HAND; j++)
    {
      printf("\n**  hand[%d][%d] = %d", i,j, g->hand[i][j]);
    }
  }
  printf("\n* handCount[MAX_PLAYERS]");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    printf("\n**  handCount[%d] = %d", i,g->handCount[i]);
  }
  printf("\n* deck[MAX_PLAYERS][MAX_DECK]");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    for (j=0; j < MAX_DECK; j++)
    {
      printf("\n**  deck[%d][%d] = %d", i,j, g->deck[i][j]);
    }
  }
  printf("\n* deckCount[MAX_PLAYERS]");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    printf("\n**  deckCount[%d] = %d", i,g->deckCount[i]);
  }
  printf("\n* discard[MAX_PLAYERS][MAX_DECK]");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    for (j=0; j < MAX_DECK; j++)
    {
      printf("\n**  discard[%d][%d] = %d", i,j, g->discard[i][j]);
    }
  }
  printf("\n* discardCount[MAX_PLAYERS]");
  for (i=0; i < (MAX_PLAYERS); i++)
  {
    printf("\n**  discardCount[%d] = %d", i,g->discardCount[i]);
  }
  printf("\n* playedCards[MAX_DECK]");
  for (i=0; i < (MAX_DECK); i++)
  {
    printf("\n**  playedCards[%d] = %d", i,g->playedCards[i]);
  }
  printf("\n* playedCardCount %d", g->playedCardCount);
  printf("\n***************************************\n");
}

void print_testPassed(char s[]) {
  printf("**\n");
  printf("*       PASS: %s\n", s);
  printf("**\n\n");
}

void print_testFailed(char s[]) {
  printf("**\n");
  printf("*       FAIL: %s\n", s);
  printf("**\n\n");
}

int rand_int(int a, int b){
  int random = (rand() % (b - a + 1) + a );
  return random;
}

/* Test if game over is triggered by 3 empty supply piles */
int test_GameOverEmpty() {
  int i = 0;
  int random;
  int testPassed = 1;
  int emptied[NUM_SUPPLYCARDS] = {0};
  struct gameState g;
  initializeGame(2, k, rand() % 100,  &g);

  /*****
  **
  ** TEST:  Game over when 3 supply piles are empty
  **
  ******/

  do {   // Randomly empty 3 supply piles
    random = rand_int(0, 26);

    if (emptied[random] != 1){
      emptied[random] = 1;
      g.supplyCount[random] = 0;
      i++;
    }
  }
  while (i < 3);

  /* Check for game over with 3 empty supply piles */
  if (!isGameOver(&g)){
    testPassed = 0;
    print_testFailed("Game over with 3 empty supply decks");
  }
  else {
    print_testPassed("Game over with 3 empty supply decks");
  }
  return testPassed;
}

/* Test if game over is triggered by no province cards */
int test_GameOverProvince() {
  int i;
  int testPassed = 1;
  struct gameState g;
  initializeGame(2, k, rand() % 100,  &g);

  /*****
  **
  ** TEST: Game over when province pile is empty
  **
  ******/

  /* Make sure all supplies are non-zero so isGameOver is not triggered
  by 3+ empty supply decks */
  for (i = 0; i < NUM_SUPPLYCARDS; i++) {
    g.supplyCount[i] = 1;
  }

  // Empty Provence Count
  g.supplyCount[province] = 0;

  if (!isGameOver(&g)){
    testPassed = 0;
    print_testFailed("Game over with no provence cards");
  }
  else {
    print_testPassed("Game over with no provence cards");
  }

  return testPassed;
}

/* Test if game is NOT over */
int test_notGameOver() {
  int i;
  int testPassed = 1;
  struct gameState g;
  initializeGame(2, k, rand() % 100,  &g);

  /*****
  **
  ** TEST: Game not over due to non-zero province and <3 empty decks
  **
  ******/

  /* Test with Non-Zero province and no empty supply decks */
  for (i = 0; i < NUM_SUPPLYCARDS; i++) {
    g.supplyCount[i] = 1;
  }

  if (isGameOver(&g)) {
    testPassed = 0;
    print_testFailed("Game over with non-zero province and <3 empty decks");
  }
  else {
    print_testPassed("Game over with non-zero province and <3 empty decks");

  }
  return testPassed;
}


int main() {
  srand(time(0));

  int testsPassed = 1;

  printf("***************************************\n");
  printf("*         Testing: isGameOver()   \n");
  printf("***************************************\n\n");

  if (!test_GameOverEmpty()) {
    testsPassed = 0;
  }
  if (!test_GameOverProvince()) {
    testsPassed = 0;
  }
  if (!test_notGameOver()) {
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
