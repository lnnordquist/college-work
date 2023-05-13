OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
CC=clang

all: student_test_homework1 test_homework1

student_test_homework1: homework1.c student_test_homework1.c

test_homework1: test_homework1.c homework1.c

clean:
	rm -f results.json results.log
	rm -f student_test_homework1 test_homework1 my_echo
	rm -rf *.dSYM *~ \#*
	rm -f test-*.txt
