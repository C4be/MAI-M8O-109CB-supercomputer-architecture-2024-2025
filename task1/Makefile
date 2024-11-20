build:
	g++ ./src/task-1.cpp ./src/help.cpp -o sort.out
	mpicxx ./src/task-1-parallel.cpp ./src/help.cpp -o sort-parallel.out

rebuild: clean build

run-sort:
	./sort.out

run-sort-parallel:
	mpirun --allow-run-as-root -np 4 ./sort-parallel.out

run: run-sort run-sort-parallel

clean:
	rm -rf *.out

all: rebuild run
