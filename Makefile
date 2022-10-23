compile:
	cd src && g++ -o main main.cpp InputFile.cpp TSPSolution.cpp VND.cpp

run:
	cd src && ./main ../testCases/berlin52.tsp

all:
	cd src && g++ -o main main.cpp InputFile.cpp TSPSolution.cpp VND.cpp && ./main ../testCases/berlin52.tsp