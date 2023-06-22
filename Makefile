main: build/main.o build/utils.o
	c++ -std=c++17 build/main.o build/utils.o -o execute_project

build/main.o: src/main.cpp
	mkdir -p build
	c++ -std=c++17 -c src/main.cpp -o build/main.o

build/utils.o: src/utils.h src/utils.cpp
	mkdir -p build
	c++ -std=c++17 -c src/utils.cpp -o build/utils.o