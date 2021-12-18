# File: Makefile
# Class: CS 215                    Instructor: Dr. Deborah Hwang
# Assignment: Project 3- Editor    Date assigned: February 21, 2020
# Programmer: Munachimso Aneke     Date completed: March 1, 2020

editor: document.o editor.o
	clang++ document.o editor.o -o editor -Wall -std=c++11

editor.o: editor.cpp document.h
	clang++ -c editor.cpp -Wall -std=c++11

document.o: document.cpp document.h
	clang++ -c document.cpp -Wall -std=c++11

clean:
	rm editor *.o *~ *.gch

