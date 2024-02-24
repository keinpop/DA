CC = g++
FLAGS = -w -pipe -O3 -Wextra -Werror -Wall -Wno-sign-compare -pedantic -lm

all: a.out

a.out: main.o
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -f *.o a.out