OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
CC=clang

all: student_test_homework3 test_homework3

student_test_homework3: homework3.c student_test_homework3.c

test_homework3: test_homework3.c homework3.c

clean:
	rm -f results.json results.log
	rm -f student_test_homework3 test_homework3
	rm -rf *.dSYM *~ \#*
	rm -f test-*.txt
