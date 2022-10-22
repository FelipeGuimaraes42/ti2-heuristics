compile:
	cd src && g++ -o main main.cpp InputFile.cpp NearestNeighborsSearch.cpp

run:
	cd src && ./main ../testCases/berlin52.tsp

all:
	cd src && g++ -o main main.cpp InputFile.cpp NearestNeighborsSearch.cpp && ./main ../testCases/berlin52.tsp