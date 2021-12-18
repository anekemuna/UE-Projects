# Munachimso Aneke
#Makefile for thread synchronization project

thread : thread_synchronization_project.o
	gcc -Wall -o thread thread_synchronization_project.o -lpthread

thread_synchronization_project.o: thread_synchronization_project.c buffer.h
	gcc -Wall -c thread_synchronization_project.c -lpthread

clean:
	rm thread  *.o *~
