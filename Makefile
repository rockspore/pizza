CFLAG = -std=c++11 -O3 -fPIC
INCL = -I include/

test_1: include/Pizza.h src/Pizza.cpp src/judge.cpp
	g++ -o test_1 test/test_1.cpp src/Pizza.cpp src/judge.cpp ${CFLAG} ${INCL}

test_brute: include/Pizza.h src/Pizza.cpp src/judge.cpp
	g++ -o brute test/test_brute.cpp src/Pizza.cpp src/judge.cpp ${CFLAG} ${INCL}
