CFLAGS = -Wall -fpic -coverage -lm
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

test_helpers.o: test_helpers.h dominion.c rngs.o
	gcc -c test_helpers.c -g

randomtestcard1: randomtestcard1.c test_helpers.o dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c test_helpers.o dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c test_helpers.o dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c test_helpers.o dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c test_helpers.o dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c test_helpers.o dominion.o rngs.o $(CFLAGS)

runrandomtests: randomtestcard1 randomtestcard2 randomtestcard3
	./randomtestcard1 &>> randomtestcard1.out
	./randomtestcard2 &>> randomtestcard2.out
	./randomtestadventurer &>> randomtestadventurer.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

clean:
	rm -f *.o randomtestcard1 randomtestcard2 randomtestcard3 randomtestadventurer *.gcov *.gcda *.gcno *.so *.out
