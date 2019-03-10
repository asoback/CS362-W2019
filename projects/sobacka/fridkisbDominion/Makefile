CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

cardEffects.o: cardEffects.h cardEffects.c
	gcc -c cardEffects.c -g  $(CFLAGS)	

dominion.o: dominion.h dominion.c rngs.o cardEffects.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults: dominion.o rngs.o cardEffects.o
	gcc -ftest-coverage -fprofile-arcs -o unittest1 unittest1.c -lm dominion.o rngs.o
	gcc -ftest-coverage -fprofile-arcs -o unittest2 unittest2.c -lm dominion.o rngs.o
	gcc -ftest-coverage -fprofile-arcs -o unittest3 unittest3.c -lm dominion.o rngs.o
	gcc -ftest-coverage -fprofile-arcs -o unittest4 unittest4.c -lm dominion.o rngs.o
	gcc -ftest-coverage -fprofile-arcs -o cardtest1 cardtest1.c -lm dominion.o rngs.o
	gcc -ftest-coverage -fprofile-arcs -o cardtest2 cardtest2.c -lm dominion.o rngs.o
	gcc -ftest-coverage -fprofile-arcs -o cardtest3 cardtest3.c -lm dominion.o rngs.o
	gcc -ftest-coverage -fprofile-arcs -o cardtest4 cardtest4.c -lm dominion.o rngs.o
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov cardEffects.c >> unittestresults.out
	gcov dominion.c >> unittestresults.out

randomtest: dominion.o rngs.o cardEffects.o
	gcc -ftest-coverage -fprofile-arcs -o randomtestcard1 randomtestcard1.c -lm dominion.o rngs.o
	gcc -ftest-coverage -fprofile-arcs -o randomtestcard2 randomtestcard2.c -lm dominion.o rngs.o
	gcc -ftest-coverage -fprofile-arcs -o randomtestadventurer randomtestadventurer.c -lm dominion.o rngs.o
	./randomtestcard1 > randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	rm dominion.c.gcov
	./randomtestcard2 > randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	rm dominion.c.gcov
	./randomtestadventurer > randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
