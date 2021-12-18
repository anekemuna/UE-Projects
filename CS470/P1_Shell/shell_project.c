// Name:  Munachimso Aneke
// Class: CS 470

#include <stdio.h>
#include <unistd.h>     // fork(), execlp()
#include <sys/wait.h>   // wait()
#include <sys/types.h>  // pid_t
#include <string.h>     // strtok
#include <stdlib.h>

#define MAX_LINE 80 /* maximum length command */

struct h_store {
   char *h_arr[1000]; // change this to dynamic array later
   int pos;
} history; 

void execute_program(char *args[], int flag);
void add_history(char * command);
void display_history(int flag, int n);
int  extra_command (char * args[]);

int main()
{
   char *args[MAX_LINE/2 + 1]; /* command line arguments */
   int should_run = 1; /* flag to determine when to exit program */
   history.pos = 0;
   char str[MAX_LINE];
   char * str1;
   pid_t pid;
   int count;
   
   while (should_run) {
      count = 0;
      printf("osh> ");
      fflush(stdout);

      /* Read in command */
      fgets(str, MAX_LINE,stdin);

      /* store command in args array*/
      int j = 0;
      str1 = strtok(str, " ");
      
      while(str1 != NULL) {

      	 args[j] = str1;
	 str1 = strtok(NULL, " ");
	 j++;
	 count++;
       }
      args[j] = NULL;
       
      printf("\n%d %d\n", j, count);
      
      int flag = 0; // checking for ampersand
      int hflag = extra_command(args); // checking for history command

      if(hflag == 0)
      {
	 add_history(*args);
      }
      
      /* if args is exit*/
      if(strstr(args[0], "exit"))
      {
	 printf("Bye!!!\n"); // delete later
	 should_run = 0;   
      }
      else if(strstr(args[j-1], "&"))
      {
	 flag = 1;
	 args[j-1] = NULL; // last args[]
	 printf("flag turned on\n");
	 
      }

      if(should_run == 1 && hflag == 0)
      {
	 execute_program(args, flag);	 
      }
      
   }
   
   return 0;
}


void execute_program(char *args[], int flag)
{
   pid_t pid;
   pid = fork();
   
   if (pid < 0)
   {
      fprintf(stderr, "Fork Failed\n");
      return;
   }
   else if (pid == 0) // child process
   {
      printf("I am the child %d\n",pid);
      
      if(flag == 1)
      {
	 pid = fork();
	 
	 if (pid < 0)
	 {
	    fprintf(stderr, "Fork Failed");
	    return;
	 }
	 else if (pid == 0)
	 {
	    if (execvp(args[0], args) == -1)  
	    {
	       printf("Command does not exist\n");
	    }
	    exit(1);
	 }
      }
     
      else if (execvp(args[0], args) == -1)  
      {
	 printf("Command does not exist\n");
      }
      
      printf("Child Complete\n");
      exit(1);
   }
   else // parent process
   {
      printf("I am the parent %d\n",pid);  /* added */
      wait(NULL);

   }
}

void add_history(char * command)
{
   //if position is more than 1000
   int temp = history.pos;
   history.h_arr[temp] = command;
   history.pos++;
}


void display_history(int flag, int n)
{
   char *temp;
   // if statement to check if history empty
   if(history.pos == 0)
   {
      printf("No history\n");
      return;
   }
   // if history
   else if(flag == 0)
   {
      printf("Command History: \n");
      int j = 0;
      while(j != 10)
      {
	 temp = history.h_arr[j];
	 printf("%d  %s\n", j, temp);
	 j++;
      }
   }
   else if(flag == 1) // if histroy !!
   {
       printf("Command History: \n");
       printf("%s\n", history.h_arr[history.pos -1]);
   }
   else if(flag == 2) // if history ! n
   {
      if(n >= history.pos)
      {
	 printf("Not up to %d command(s) in history!\n", n);
	 return;
      }
      
      printf("Command History: \n");
      temp = history.h_arr[n-1];
      printf(" %s\n", temp);
   }
   else
   {
      printf("Invalid history command!");
   }

   
}

int  extra_command (char * args[])
{
   int result = 0;
   
   if(strstr(args[0], "history"))
   {
      if(args[1] == NULL)
      {
	 display_history(0, 0);
      }
      result = 1;
   }
   else if(strcmp(args[0], "!!") == 0)
   {
      display_history(1, 0);
      result = 1;
   }
   else if(strcmp(args[0], "!") == 0)
   {
      display_history(2, atoi(args[1]));
      result = 1;
   }

   return result;
}



// don't forget
/* 1. to change exit so that it changes should run to 0
   2. to delete unncessary comments
   3. Break program into functions
   4. execute_program should return an int, to be read in by should run
*/


// History desisgn
/*
  1. create a function called for extra commands (might include exit)
     a. should also process ! nth, !! calss for history
  2. create a static array to store  (should it be static, what's the max?)
     b. does c have vectors? please do :(
  3. function to add history
  4. function to return history
  5. code for when add-history reaches a counter of 10
*/
