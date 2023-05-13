OBJECTS = 
CFLAGS = -g -Wall -O3 --std=c11
LDLIBS= -l criterion -lm
CC=clang

all: student_test_homework4 test_homework4

student_test_homework4: homework4.c student_test_homework4.c

test_homework4: test_homework4.c homework4.c

clean:
	rm -f results.json results.log
	rm -f student_test_homework4 test_homework4
	rm -rf *.dSYM *~ \#*
	rm -f test-*.txt
