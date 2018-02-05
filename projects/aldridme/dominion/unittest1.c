#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

/* Test if game over is triggered by 3 empty supply piles */
int test_GameOverEmpty() {
  int i = 0;
  int random;
  int testPassed = 1;
  int emptied[NUM_SUPPLYCARDS] = {0};
  struct gameState g;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g);

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
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g);

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
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g);

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
