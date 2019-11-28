CC = clang
OPTS = -Wall

all: driver

board.o: board.c board.h
	$(CC) $(OPTS) -c board.c

helper.o: helper.c helper.h board.o
	$(CC) $(OPTS) -c helper.c board.o

driver: driver.c board.o helper.o
	$(CC) $(OPTS) -o driver driver.c helper.o board.o

clean:
	rm *.o; rm driver
