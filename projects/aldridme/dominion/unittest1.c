#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PLAYERS 2

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

int rand_int(int a, int b){
  int random = (rand() % (b - a + 1) + a );
  printf("rand = %d\n", random);

  return random;
}

int test_gameOverConditions()
{
  int i = 0;
  int random;
  int testPassed = 1;
  int emptied[treasure_map+1] = {0};
  struct gameState g;
  initializeGame(2, k, rand() % 100,  &g);

  /* Game over when 3 supply piles are empty */
  /* Randomly empty 3 supply piles */
  do {
    random = rand_int(0, 26);

    if (emptied[random] != 1){
      emptied[random] = 1;
      g.supplyCount[random] = 0;
      printf("Emptied %d\n", random);
      i++;
    }
  }
  while (i < 3);

  if (isGameOver(&g)){
    testPassed = 0;
    print_testFailed("Game Over test with 3 empty supply decks");
  }

  return testPassed;
}

void print_testPassed(char s[]) {
  printf("***************************************\n");
  printf("*       PASS: %s\n", s);
  printf("***************************************\n\n");
}

void print_testFailed(char s[]) {
  printf("***************************************\n");
  printf("*       FAIL: %s\n", s);
  printf("***************************************\n\n");
}

int main() {
  srand(time(0));

  int testsPassed = 1;

  printf("***************************************\n");
  printf("*         Testing: isGameOver()   *\n");
  printf("***************************************\n\n");

  if (!test_gameOverConditions()) {
    testsPassed = 0;
  }

  if (testsPassed) {
    printf("***************************************\n");
    printf("*       All Tests Passed              *\n");
    printf("***************************************\n\n");
  }
  else {
    printf("***************************************\n");
    printf("*       One or more Tests Failed      *\n");
    printf("***************************************\n\n");
  }

  return 0;
}
