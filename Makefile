CFLAG = -std=c++11 -O3 -fPIC
INCL = -I include/

test_1: include/Pizza.h src/Pizza.cpp src/judge.cpp
	g++ -o test_1 test/test_1.cpp src/Pizza.cpp src/judge.cpp ${CFLAG} ${INCL}
