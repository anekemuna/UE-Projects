# File: Makefile
# Class: CS215                          Instructor: Dr. Deborah Hwang
# Assignment: Project 6- Huffman        Date assigned: April 15, 2020
# Programmer: Munachimso Aneke          Date completed: April 27, 2020


coder: huffman.o coder.o
	clang++ huffman.o coder.o -o coder -Wall

coder.o: huffman.h coder.cpp
	clang++ -c coder.cpp -Wall -std=c++11

huffman.o: huffman.cpp huffman.h
	clang++ -c huffman.cpp -Wall -std=c++11

clean:
	rm coder *.o *~ *.gch
