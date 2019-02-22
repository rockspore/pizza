CFLAG = -std=c++11 -O3 -fPIC
INCL = -I include/

test_1: include/Pizza.h src/Pizza.cpp src/judge.cpp
	g++ -o test_1 test/test_1.cpp src/Pizza.cpp src/judge.cpp ${CFLAG} ${INCL}

test_2: include/Pizza.h src/Pizza.cpp include/BMP.h src/BMP.cpp
	g++ -o test_2 test/test_2.cpp src/Pizza.cpp src/BMP.cpp ${CFLAG} ${INCL}

test_brute: include/Pizza.h include/BMP.h src/Pizza.cpp src/judge.cpp src/BMP.cpp
	g++ -o brute test/test_brute.cpp src/Pizza.cpp src/judge.cpp src/BMP.cpp ${CFLAG} ${INCL}

test_annealing: include/Pizza.h include/BMP.h src/Pizza.cpp src/judge.cpp src/BMP.cpp src/annealing.cpp
	g++ -o brute_annealing test/test_annealing.cpp src/Pizza.cpp src/judge.cpp src/annealing.cpp src/BMP.cpp ${CFLAG} ${INCL}

test_BMP: include/BMP.h src/BMP.cpp test/test_BMP.cpp
	g++ -o test_BMP include/BMP.h src/BMP.cpp test/test_BMP.cpp ${CFLAG} ${INCL}

run_annealing: brute_annealing
	./brute_annealing data/d_big.in d_1.out d_2.out 20 5 0.1 330 > d_data_2019-02-22.log
