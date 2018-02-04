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

int test_noBuys() {
  int testPassed = 1;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Ensure current player has no buys*/
  g_res.numBuys = 0;

  /* Give at least one supply to card, then buy*/
  g_res.supplyCount[province] = 1;

  /* Copy game state */
  copyGameState(&g_res, &g_exp);

  /* Attempt buy */
  buyCard(province, &g_res);

  /* Validate game state has not changed with unsuccessful buy*/
  if(!gameStatesEqual(&g_res, &g_exp)){
    testPassed = 0;
    print_testFailed("Purchase with no buys should not change game state");
  }
  else {
    print_testPassed("Purchase with no buys didn't change game state");
  }

  return testPassed;
}

int test_noSupplies() {
  int testPassed = 1;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Ensure that supply of card is zero*/
  g_res.supplyCount[province] = 0;

  /* Copy game state */
  copyGameState(&g_res, &g_exp);

  /* Attempt buy */
  buyCard(province, &g_res);

  /* Validate game state has not changed without supplies*/
  if(!gameStatesEqual(&g_res, &g_exp)){
    testPassed = 0;
    print_testFailed("Purchase with no supply of card should not change game state");
  }
  else {
    print_testPassed("Purchase with no supply of card didn't change game state");
  }

  return testPassed;
}

int test_notEnoughCoins() {
  int testPassed = 1;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Ensure that coins < cost of card*/
  g_res.coins = 2;

  /* Copy game state */
  copyGameState(&g_res, &g_exp);

  /* Attempt buy */
  buyCard(mine, &g_res); //mine costs 5 which is greater than 2 coins

  /* Validate game state has not changed without supplies*/
  if(!gameStatesEqual(&g_res, &g_exp)){
    testPassed = 0;
    print_testFailed("Purchase with less coins than cost of card should not change game state");
  }
  else {
    print_testPassed("Purchase with less coins than cost of card didn't change game state");
  }

  return testPassed;
}

int test_buyCard() {
  int testPassed = 1;
  int player;
  struct gameState g_res,g_exp;
  initializeGame(MAX_PLAYERS, k, rand() % 100,  &g_res);

  /* Ensure at least one buy, one supply, and enough coins */
  g_res.whoseTurn = (rand() % MAX_PLAYERS);
  player = g_res.whoseTurn;
  g_res.numBuys = (rand() % 5) + 1;
  g_res.supplyCount[gold] = (rand() % 5) + 1; // Costs 6
  g_res.coins = (rand() % 6) + 6;
  g_res.discardCount[player] = 5;
  g_res.discard[player][g_res.discardCount[player] - 1] = province; // Last Card before buy


  /* Copy game state */
  copyGameState(&g_res, &g_exp);

  /* Attempt buy */
  buyCard(gold, &g_res);

  /* Validate discard count incremented*/
  if (g_res.discardCount[player] != g_exp.discardCount[player] + 1) {
    testPassed = 0;
    print_testFailed("Player does not have additional card in discard pile");
  }
  else {
    /* Validate card is in discard */
    if (g_res.discard[player][g_res.discardCount[player] - 1] == gold) {
      print_testPassed("Player received card in discard pile");
    }
    else {
      testPassed = 0;
      print_testFailed("Player does not have purchased card in discard pile");
    }
  }

  /* Validate supply of gold card was reduced */
  g_exp.supplyCount[gold]--;
  if (g_res.supplyCount[gold] != (g_exp.supplyCount[gold])) {
    testPassed = 0;
    print_testFailed("Supply of bought card not reduced by one");
  }
  else {
    print_testPassed("Supply of bought card reduced by one");
  }

  /* Validate total coins decreased by bought card cost */
  g_exp.coins = g_exp.coins - 6; // Cost of Gold
  if (g_res.coins != g_exp.coins) {
    testPassed = 0;
    print_testFailed("Total coins did not decrease with purchase");
  }
  else {
    print_testPassed("Total coins decreased with purchase");
  }

  return testPassed;
}

int main() {
  srand(time(0));

  int testsPassed = 1;

  printf("***************************************\n");
  printf("*         Testing: buyCard()   \n");
  printf("***************************************\n\n");

  if (!test_noBuys()) {
    testsPassed = 0;
  }

  if (!test_noSupplies()) {
    testsPassed = 0;
  }

  if (!test_notEnoughCoins()) {
    testsPassed = 0;
  }

  if (!test_buyCard()) {
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
