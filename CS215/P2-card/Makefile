# File: Makefile
# Class: CS215			   Instructor:    Dr. Deborah Hwang
# Assignment: Project2-Card	   Date assigned:  February 12 2020 
# Programmer: Munachimso Aneke     Date completed: February 14 2020


carddriver: card.o carddriver.o
	clang++ card.o carddriver.o -o carddriver -Wall -std=c++11

# Targets for the object files
card.o: card.cpp card.h
	clang++ -c card.cpp -Wall -std=c++11

carddriver.o: carddriver.cpp card.h
	clang++ -c carddriver.cpp -Wall -std=c++11

# Dummy targets - targets that are created
clean:
	rm -f carddriver *.o *~ *.gch



