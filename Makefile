# Make
test_1: src/Pizza.h src/Pizza.cpp src/judge.cpp
	g++ -o test_1 test/test_1.cpp src/Pizza.cpp src/judge.cpp -std=c++11 -O3 -fPIC
