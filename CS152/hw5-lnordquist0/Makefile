OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
CC=clang

all: student_test_homework5 test_homework5

student_test_homework5: homework5.c student_test_homework5.c

test_homework5: test_homework5.c homework5.c

clean:
	rm -f results.json results.log
	rm -f student_test_homework5 test_homework5
	rm -rf *.dSYM *~ \#*
	rm -f test-*.txt
