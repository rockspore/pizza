CFLAG = -std=c++11 -O3 -fPIC
INCL = -I include/

test_1: include/Pizza.h src/Pizza.cpp src/judge.cpp
	g++ -o test_1 test/test_1.cpp src/Pizza.cpp src/judge.cpp ${CFLAG} ${INCL}

test_2: include/Pizza.h src/Pizza.cpp include/BMP.h src/BMP.cpp
	g++ -o test_2 test/test_2.cpp src/Pizza.cpp src/BMP.cpp ${CFLAG} ${INCL}

test_brute: include/Pizza.h include/BMP.h src/Pizza.cpp src/judge.cpp src/BMP.cpp
	g++ -o brute test/test_brute.cpp src/Pizza.cpp src/judge.cpp src/BMP.cpp ${CFLAG} ${INCL}

test_BMP: include/BMP.h src/BMP.cpp test/test_BMP.cpp
	g++ -o test_BMP include/BMP.h src/BMP.cpp test/test_BMP.cpp ${CFLAG} ${INCL}
