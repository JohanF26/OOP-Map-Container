Everything in my program works properly
This was my output after an optimized timed run of test-scaling.cpp:

************************************
	Ascending insert for cs540::Map<int, int>
************************************

Inserting 1,000 elements in aescending order took 0.325375 milliseconds
Inserting 10,000 elements in aescending order took 2.9055 milliseconds
Inserting 100,000 elements in aescending order took 32.2157 milliseconds
Inserting 1,000,000 elements in aescending order took 332.876 milliseconds
Inserting 10,000,000 elements in aescending order took 3,446.26 milliseconds


************************************
	Ascending insert for cs540::StdMapWrapper<int, int>
************************************

Inserting 1,000 elements in aescending order took 0.074481 milliseconds
Inserting 10,000 elements in aescending order took 0.779633 milliseconds
Inserting 100,000 elements in aescending order took 9.40707 milliseconds
Inserting 1,000,000 elements in aescending order took 120.875 milliseconds
Inserting 10,000,000 elements in aescending order took 1,631.34 milliseconds


************************************
	Descending insert for cs540::Map<int, int>
************************************

Inserting 1,000 elements in descending order took 0.266477 milliseconds
Inserting 10,000 elements in descending order took 1.35469 milliseconds
Inserting 100,000 elements in descending order took 14.5781 milliseconds
Inserting 1,000,000 elements in descending order took 150.86 milliseconds
Inserting 10,000,000 elements in descending order took 1,526.13 milliseconds


************************************
	Descending insert for cs540::StdMapWrapper<int, int>
************************************

Inserting 1,000 elements in descending order took 0.070996 milliseconds
Inserting 10,000 elements in descending order took 0.747919 milliseconds
Inserting 100,000 elements in descending order took 9.17742 milliseconds
Inserting 1,000,000 elements in descending order took 115.713 milliseconds
Inserting 10,000,000 elements in descending order took 1,500.16 milliseconds


************************************
	Delete test for cs540::Map<int, int>
************************************

deleting 10000 elements from a map of size 10000 took 1.42233 milliseconds
deleting 10000 elements from a map of size 100000 took 8.08387 milliseconds
deleting 10000 elements from a map of size 1000000 took 18.8736 milliseconds
deleting 10000 elements from a map of size 10000000 took 33.8621 milliseconds


************************************
	Delete test for cs540::StdMapWrapper<int, int>
************************************

deleting 10000 elements from a map of size 10000 took 0.901939 milliseconds
deleting 10000 elements from a map of size 100000 took 4.5204 milliseconds
deleting 10000 elements from a map of size 1000000 took 10.3612 milliseconds
deleting 10000 elements from a map of size 10000000 took 19.0794 milliseconds


************************************
	Find test for cs540::Map<int, int>
************************************

Finding 10000 elements from a map of size 10,000 took 5.18408 milliseconds
Finding 10000 elements from a map of size 100,000 took 22.5129 milliseconds
Finding 10000 elements from a map of size 1,000,000 took 40.3728 milliseconds
Finding 10000 elements from a map of size 10,000,000 took 65.7736 milliseconds


************************************
	Find test for cs540::StdMapWrapper<int, int>
************************************

Finding 10000 elements from a map of size 10,000 took 244.234 milliseconds
Finding 10000 elements from a map of size 100,000 took 9.26207 milliseconds
Finding 10000 elements from a map of size 1,000,000 took 16.4419 milliseconds
Finding 10000 elements from a map of size 10,000,000 took 25.4531 milliseconds


************************************
	Iteration test for cs540::Map<int, int>
************************************

Iterating across 10,000 elements in a map of size 10,000 took 0.192175 milliseconds time per iteration was 19.2175 nanoseconds
Iterating across 20,000 elements in a map of size 20,000 took 0.389979 milliseconds time per iteration was 19.499 nanoseconds
Iterating across 40,000 elements in a map of size 40,000 took 0.747506 milliseconds time per iteration was 18.6877 nanoseconds
Iterating across 80,000 elements in a map of size 80,000 took 4.30069 milliseconds time per iteration was 53.7587 nanoseconds
Iterating across 160,000 elements in a map of size 160,000 took 8.06805 milliseconds time per iteration was 50.4253 nanoseconds
Iterating across 320,000 elements in a map of size 320,000 took 16.4161 milliseconds time per iteration was 51.3002 nanoseconds
Iterating across 640,000 elements in a map of size 640,000 took 32.8182 milliseconds time per iteration was 51.2784 nanoseconds
Iterating across 1,280,000 elements in a map of size 1,280,000 took 71.9014 milliseconds time per iteration was 56.1729 nanoseconds
Iterating across 2,560,000 elements in a map of size 2,560,000 took 130.602 milliseconds time per iteration was 51.0163 nanoseconds
Iterating across 5,120,000 elements in a map of size 5,120,000 took 254.264 milliseconds time per iteration was 49.661 nanoseconds


************************************
	Iteration test for cs540::StdMapWrapper<int, int>
************************************

Iterating across 10,000 elements in a map of size 10,000 took 0.170913 milliseconds time per iteration was 17.0913 nanoseconds
Iterating across 20,000 elements in a map of size 20,000 took 0.306976 milliseconds time per iteration was 15.3488 nanoseconds
Iterating across 40,000 elements in a map of size 40,000 took 0.61374 milliseconds time per iteration was 15.3435 nanoseconds
Iterating across 80,000 elements in a map of size 80,000 took 1.27641 milliseconds time per iteration was 15.9551 nanoseconds
Iterating across 160,000 elements in a map of size 160,000 took 7.46713 milliseconds time per iteration was 46.6695 nanoseconds
Iterating across 320,000 elements in a map of size 320,000 took 15.3329 milliseconds time per iteration was 47.9153 nanoseconds
Iterating across 640,000 elements in a map of size 640,000 took 31.6861 milliseconds time per iteration was 49.5095 nanoseconds
Iterating across 1,280,000 elements in a map of size 1,280,000 took 62.657 milliseconds time per iteration was 48.9508 nanoseconds
Iterating across 5,120,000 elements in a map of size 5,120,000 took 259.462 milliseconds time per iteration was 50.6761 nanoseconds


************************************
	Copy test for cs540::Map<int, int>
************************************

Copy construction of a map of size 10,000 took 2.21729 milliseconds
Copy construction of a map of size 100,000 took 26.0619 milliseconds
Copy construction of a map of size 1,000,000 took 307.467 milliseconds
Copy construction of a map of size 10,000,000 took 3,734.99 milliseconds


************************************
	Copy test for cs540::StdMapWrapper<int, int>
************************************

Copy construction of a map of size 10,000 took 0.254267 milliseconds
Copy construction of a map of size 100,000 took 4.2122 milliseconds
Copy construction of a map of size 1,000,000 took 50.7266 milliseconds
Copy construction of a map of size 10,000,000 took 503.593 milliseconds

real	0m47.987s
user	0m46.816s
sys	0m1.168s

____________________________________________________________________

MAKE COMMAND DESCRIPTIONS

* all: creates executables for all of the testing cpp files.

* test, minimal, morseex, test-kec, & test-scaling: create executables
for their corresponding cpp files.

* Map.o, test.o, minimal.o, morseex.o, test-kec.o, & test-scaling.o: create
the object files for their corresponding cpp files.

* run: executes the file produced by test.cpp.

* timeRun: measures how long it takes to execute the file created by
compiling test-scaling.cpp with the -O (optimize) flag.

* exec: compiles test-scaling.cpp with -O

* runMinimal, runMorseex, runTestKec, runTestScaling: executes their
respective files.

* checkmem, checkMinimal, checkMoreseex, checkTestKec, checkTestScaling:
runs their respective files through Valgrind to check for memory leaks.

* clean: removes all object files and executables
