#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYERS 4
#define NUM_SUPPLYCARDS 27

int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

/* Print game state for debugging */
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

/* Copy game state from original to copy */
void copyGameState(struct gameState * g_original, struct gameState * g_copy) {
  int i,j;

  g_copy->numPlayers = g_original->numPlayers;

  for (i = 0; i < NUM_SUPPLYCARDS; i++) {
    g_copy->supplyCount[i] = g_original->supplyCount[i];
  }

  for (i = 0; i < NUM_SUPPLYCARDS; i++) {
    g_copy->embargoTokens[i] = g_original->embargoTokens[i];
  }

  g_copy->outpostPlayed = g_original->outpostPlayed;
  g_copy->outpostTurn = g_original->outpostTurn;
  g_copy->whoseTurn = g_original->whoseTurn;
  g_copy->phase = g_original->phase;
  g_copy->numActions = g_original->numActions;
  g_copy->coins = g_original->coins;
  g_copy->numBuys = g_original->numBuys;

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_HAND; j++){
      g_copy->hand[i][j] = g_original->hand[i][j];
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    g_copy->handCount[i] = g_original->handCount[i];
  }

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_DECK; j++){
      g_copy->deck[i][j] = g_original->deck[i][j];
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    g_copy->deckCount[i] = g_original->deckCount[i];
  }

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_DECK; j++){
      g_copy->discard[i][j] = g_original->discard[i][j];
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    g_copy->discardCount[i] = g_original->discardCount[i];
  }

  for (i = 0; i < MAX_DECK; i++) {
    g_copy->playedCards[i] = g_original->playedCards[i];
  }

  g_copy->playedCardCount = g_original->playedCardCount;
}

int gameStatesEqual(struct gameState * g_original, struct gameState * g_copy) {
  int i,j;
  if (g_copy->numPlayers != g_original->numPlayers) {
    return 0;
  }

  for (i = 0; i < NUM_SUPPLYCARDS; i++) {
    if (g_copy->supplyCount[i] != g_original->supplyCount[i]) {
      return 0;
    }
  }

  for (i = 0; i < NUM_SUPPLYCARDS; i++) {
    if (g_copy->embargoTokens[i] != g_original->embargoTokens[i]) {
      return 0;
    }
  }

  if (g_copy->outpostPlayed != g_original->outpostPlayed) {
    return 0;
  }

  if (g_copy->outpostTurn != g_original->outpostTurn) {
    return 0;
  }

  if (g_copy->whoseTurn != g_original->whoseTurn) {
    return 0;
  }

  if (g_copy->phase != g_original->phase) {
    return 0;
  }

  if (g_copy->numActions != g_original->numActions) {
    return 0;
  }

  if (g_copy->coins != g_original->coins) {
    return 0;
  }

  if (g_copy->numBuys != g_original->numBuys) {
    return 0;
  }

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_HAND; j++){
      if (g_copy->hand[i][j] != g_original->hand[i][j]) {
        return 0;
      }
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    if(g_copy->handCount[i] != g_original->handCount[i]){
      return 0;
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_DECK; j++){
      if(g_copy->deck[i][j] != g_original->deck[i][j]) {
        return 0;
      }
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    if(g_copy->deckCount[i] != g_original->deckCount[i]) {
      return 0;
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++){
    for (j = 0; j < MAX_DECK; j++){
      if(g_copy->discard[i][j] != g_original->discard[i][j]) {
        return 0;
      }
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    if(g_copy->discardCount[i] != g_original->discardCount[i]) {
      return 0;
    }
  }

  for (i = 0; i < MAX_DECK; i++) {
    if(g_copy->playedCards[i] != g_original->playedCards[i]) {
      return 0;
    }
  }

  if(g_copy->playedCardCount != g_original->playedCardCount) {
    return 0;
  }

  return 1;
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

int test_coins(int coin_denom, int coin_value) {
  int testPassed = 1;
  int i, player, coins;
  char * coinName;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Initialize relevant values */
  g_res.whoseTurn = rand() % MAX_PLAYERS;
  player = g_res.whoseTurn;
  g_res.coins = rand() % 100; //Ensure that this random number doesn't persist
  g_res.handCount[player] = (rand() % 10) + 5; //Random number between 5 and 14

  if (coin_denom == copper){
    coinName = "copper";
  }
  else if (coin_denom == silver){
    coinName = "silver";
  }
  else if (coin_denom == gold){
    coinName = "gold";
  }

  /* Make all cards province (non-treasure) */
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = province;
  }

  /* Make one or more coin_denom cards */
  for (i = 0; i < g_res.handCount[player]; i++ ) {
    g_res.hand[player][i] = coin_denom;
  }

  /* Copy gameState */
  copyGameState(&g_res, &g_exp);

  /* Update Coins with no bonus */
  updateCoins(player, &g_res, 0);

  /* Calculated expected value */
  coins = 0;
  for (i = 0; i < g_exp.handCount[player]; i++) {
    if (g_exp.hand[player][i] == coin_denom) {
      coins = coins + coin_value;
    }
  }

  if (g_res.coins != coins) {
    testPassed = 0;
    char msg[100] = {'\0'};
    snprintf(&msg, sizeof(msg),"Expected %d  %s Actual %d are not equal.\n", coins,coinName, g_res.coins);
    print_testFailed(msg);
  }
  else {
    char msg[100] = {'\0'};
    snprintf(&msg, sizeof(msg),"Expected %s coins and actual coins are equal.\n", coinName);
    print_testPassed(msg);
  }

  return testPassed;
}

int test_noCoins() {
  int testPassed = 1;
  int i, player, coins;
  char * coinName;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Initialize relevant values */
  g_res.whoseTurn = rand() % MAX_PLAYERS;
  player = g_res.whoseTurn;
  g_res.coins = 0;
  g_res.handCount[player] = (rand() % 10) + 5; //Random number between 5 and 14

  /* Make all cards province (non-treasure) */
  for (i = 0; i < g_res.handCount[player]; i++) {
    g_res.hand[player][i] = province;
  }

  /* Copy gameState */
  copyGameState(&g_res, &g_exp);

  /* With no coins, ensure game state does not change */
  if (!gameStatesEqual(&g_res, &g_exp)) {
    testPassed = 0;
    print_testFailed("Game state changed with no coins in hand.");
  }
  else {
    print_testPassed("Game state didn't change with no coins in hand.");
  }

  return testPassed;
}

int main() {
  srand(time(0));

  int testsPassed = 1;

  printf("***************************************\n");
  printf("*         Testing: updateCoins()   \n");
  printf("***************************************\n\n");

  if (!test_coins(copper, 1)){
    testsPassed = 0;
  }

  if (!test_coins(silver, 2)){
    testsPassed = 0;
  }

  if (!test_coins(gold, 3)){
    testsPassed = 0;
  }

  if (!test_noCoins()){
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
