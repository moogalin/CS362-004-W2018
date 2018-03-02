#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#define MAX_PLAYERS 4
#define NUM_SUPPLYCARDS 27


void printGameState(struct gameState * g, char s[]);

int gameStatesEqual(struct gameState * g_original, struct gameState * g_copy);

void print_testName(char s[]);

void print_testPassed(char s[]);

void print_testFailed(char s[]);

void copyGameState(struct gameState * g_original, struct gameState * g_copy);

int rand_int(int a, int b);


#endif
