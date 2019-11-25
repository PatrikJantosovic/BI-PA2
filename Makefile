CXX=g++
LD=g++
CFLAGS= -std=c++11 -Wall -pedantic -Wextra -g -Wno-long-long -O0 -ggdb
NAME=jantopat

default_target: all

src/CCalculator.o: src/CCalculator.cpp src/CCalculator.hpp src/AMatrix.hpp src/CData.hpp
	$(CXX) $< $(CFLAGS) -c -o $@

src/AMatrix.o: src/AMatrix.cpp src/AMatrix.hpp src/CData.hpp
	$(CXX) $< $(CFLAGS) -c -o $@

src/CData.o: src/CData.cpp src/CData.hpp src/AMatrix.hpp src/CDense.hpp src/CSparse.hpp
	$(CXX) $< $(CFLAGS) -c -o $@

src/CDense.o: src/CDense.cpp src/CDense.hpp src/AMatrix.hpp
	$(CXX) $< $(CFLAGS) -c -o $@

src/CSparse.o: src/CSparse.cpp src/CDense.hpp src/AMatrix.hpp
	$(CXX) $< $(CFLAGS) -c -o $@

src/main.o: src/main.cpp src/CCalculator.hpp
	$(CXX) $< $(CFLAGS) -c -o $@

matrixcalculator: src/main.o src/CCalculator.o src/AMatrix.o src/CData.o src/CDense.o src/CSparse.o
	$(LD) -o ./$(NAME) $^

compile: matrixcalculator

run: compile
	./${NAME}

doc: src/main.cpp src/AMatrix.hpp src/CCalculator.hpp src/CData.hpp src/CDense.hpp src/CSparse.hpp
	doxygen config

all: compile doc

clean: 
	rm -r ./${NAME} ./src/*.o ./doc 2>/dev/null