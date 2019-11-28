CC = clang
OPTS = -Wall

all: driver.e

board.o: board.c board.h
	$(CC) $(OPTS) -c board.c

helper.o: helper.c helper.h board.o
	$(CC) $(OPTS) -c helper.c board.o

driver.e: driver.c board.o helper.o
	$(CC) $(OPTS) -o driver.e driver.c helper.o board.o

clean:
	rm *.o; rm driver
