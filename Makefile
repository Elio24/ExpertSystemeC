CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
OBJ = main.o listes.o expert.o
EXEC = expert_system

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c expert.h listes.h
	$(CC) $(CFLAGS) -c main.c

expert.o: expert.c expert.h listes.h
	$(CC) $(CFLAGS) -c expert.c

listes.o: listes.c listes.h
	$(CC) $(CFLAGS) -c listes.c

clean:
	rm -f *.o $(EXEC)

re: clean all