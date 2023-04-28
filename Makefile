.PHONY: s21_matrix_oop.a

all:gcov

run:
	mkdir build
	cd build && cmake ..
	cd build && make
	cd build && ./CPP1_s21_matrixplus-1
	
clean:
	rm -rf build

rebuild: clean run

test:
	mkdir build
	cd build && cmake ..
	cd build && make
	cd build && ./tests

s21_matrix_oop.a:
	g++ -std=c++17 main.cpp -c -o s21_matrix_oop.o
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	runlib s21_matrix_oop.a

gcov: clean test
	cd build && make coverage
	open build/coverage.html
	
