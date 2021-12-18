# File: Makefile
# Class: CS 215                   Instructor: Dr. Deborah Hwang
# Assignment: Project 5- Editor2  Date assigned: March 30, 2020
# Programmer: Munachimso Aneke    Date completed: April 15, 2020

editor2: document2.o editor2.o
	clang++ document2.o editor2.o -o editor2 -Wall

editor2.o: editor2.cpp document2.h
	clang++ -c editor2.cpp -Wall -std=c++11

document2.o: document2.cpp document2.h
	clang++ -c document2.cpp -Wall -std=c++11

clean:
	rm editor2 *.o *~ *.gch
