OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
CC=clang

all: student_test_homework2 test_homework2

student_test_homework2: homework2.c student_test_homework2.c

test_homework2: test_homework2.c homework2.c

clean:
	rm -f results.json results.log
	rm -f student_test_homework2 test_homework2
	rm -rf *.dSYM *~ \#*
	rm -f test-*.txt
