CPPFLAGS= -Wall -Wextra -pedantic -g -std=c++11

all:	minimal morseex test-kec test-scaling test
	# Insert command to compile the code and generate executable

test:		test.o
			g++ $(CPPFLAGS) test.o -o Test

minimal:	minimal.o
			g++ $(CPPFLAGS) minimal.o -o Minimal

morseex:	morseex.o
			g++ $(CPPFLAGS) morseex.o -o Morseex

test-kec:	test-kec.o
			g++ $(CPPFLAGS) test-kec.o -o Test-kec

test-scaling:	test-scaling.o
			g++ $(CPPFLAGS) test-scaling.o -o Test-scaling

test.o:		test.cpp
			g++ -c $(CPPFLAGS) test.cpp

minimal.o:	minimal.cpp
			g++ -c $(CPPFLAGS) minimal.cpp

morseex.o:	morseex.cpp
			g++ -c $(CPPFLAGS) morseex.cpp

test-kec.o:	test-kec.cpp
			g++ -c $(CPPFLAGS) test-kec.cpp

test-scaling.o:	test-scaling.cpp
			g++ -c $(CPPFLAGS) test-scaling.cpp

run:
	# Insert command to run the executable
			./Test

timeRun:	exec
			time ./exec

exec:		test-scaling.cpp
			g++ $(CPPFLAGS) -O test-scaling.cpp -o exec

runMinimal:	minimal
			./Minimal

runMorseex: morseex
			./Morseex

runTestKec:	test-kec
			./Test-kec

runTestScaling:	test-scaling
			./Test-scaling

checkmem:	test
	# Insert command to run the executable with valgrind
			valgrind ./Test

checkMinimal:	minimal
			valgrind ./Minimal

checkMorseex:	morseex
			valgrind ./Morseex

checkTestKec:	test-kec
			valgrind ./Test-kec

checkTestScaling:	test-scaling
			valgrind ./Test-scaling

clean:
	# Insert command to clean object files, executables
			rm -f *.o Test Minimal Morseex Test-kec exec Test-scaling
