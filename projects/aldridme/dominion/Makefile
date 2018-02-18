CFLAGS = -Wall -fpic -coverage -lm
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

test_helpers.o: test_helpers.h dominion.c rngs.o
	gcc -c test_helpers.c -g

randomtestcard1: randomtestcard1.c test_helpers.o dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c test_helpers.o dominion.o rngs.o $(CFLAGS)

runrandomtests: randomtestcard1
	./randomtestcard1 &>> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtest.out: randomtestcard1
	./randomtestcard1 &>> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

clean:
	rm -f *.o randomtestcard1 *.gcov *.gcda *.gcno *.so *.out
