CC = clang
OPTS = -Wall

all: driver.e

board.o: board.c board.h
	$(CC) $(OPTS) -c board.c

helper.o: helper.c helper.h board.o
	$(CC) $(OPTS) -c helper.c

driver.e: driver.c board.o helper.o
	$(CC) $(OPTS) -o driver.e driver.c board.o helper.o

clean:
	rm *.o; rm *.e
