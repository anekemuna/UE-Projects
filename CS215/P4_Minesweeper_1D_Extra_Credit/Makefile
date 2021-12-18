# File:  Makefile
# Class: CS 215                          Instructor:  Dr. Deborah Hwang
# Assignment: Project 4- Minesweeper     Date assigned: March 2, 2020
# Programmer: Munachimso Aneke           Date completed: March 19, 2020


sweeper: sweepercell.o sweepergrid.o sweeper.o
	clang++ sweepercell.o sweepergrid.o sweeper.o -o sweeper -Wall -std=c++11

sweeper.o: sweeper.cpp sweepergrid.h sweepercell.h
	clang++ -c sweeper.cpp -Wall -std=c++11

sweepergrid.o: sweepergrid.cpp sweepergrid.h
	clang++ -c sweepergrid.cpp -Wall -std=c++11

sweepercell.o: sweepercell.cpp sweepercell.h
	clang++ -c sweepercell.cpp -Wall -std=c++11

clean:
	rm sweeper *.o *~ *.gch
