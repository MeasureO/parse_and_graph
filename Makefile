CC=gcc
FLAGS= -Wall -Werror -Wextra
all: 
	$(CC) $(FLAGS) graph.c stack.c 
check:
	clang-format -n *.c *.h
	clang-format -i *.c *.h
clean:
	rm -rf *.o *.a *.so
	
