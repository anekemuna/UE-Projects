// Name: Munachimso Aneke
// Title: Process Management


#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstring> //stoi
#include <cstdlib>
#include <string>

using namespace std;

// Define qualities of  a Process

struct process
{
   int pid;
   int parent_id;
   vector <int> children_id;
   int burst_time;
   int quantum_time;
   int event_id;
};

// Function Prototypes

vector <string> parser(string s, char delimit); // parsing commands
void create_process(int n, int b);
void destroy_process(int n);
void timer_interrupt(int n);
void wait(int e);
void event(int e);
void exit_program();
void print_queue(queue <process> q);


// Global Variables
queue <process> ready_queue; // ready queue
queue <process> wait_queue;  // wait queue
int quant_time;              // quantum time
process curr;                // current running process
process init;                // process ID = 0
ofstream output_file;        // output file



int main(int argc, char * argv[])
{
   // 1. Check for arguments
   if (argc != 4)
   {
      cerr << "Usage: " << argv[0] << "inputfile outputfile quantum_no" << endl;
      exit(1);
   }

   // 2. Intialize arguments and Check files
   ifstream input_file (argv[1]); // input file

   if(!input_file)
   {
      cerr << "Error: Cannot open input file " << argv[1] << endl;
      exit(1);
   }

   // ofstream output_file (argv[2]);  // output file /*might change*/
    output_file.open(argv[2]);

   if (!output_file)
   {
      cerr << "Error: Cannot open output file " << argv[2] << endl;
      exit(1);
   }

   quant_time = stoi(argv[3]); // quantum

   // 3. Initialize initial process
   init.pid = 0;

   output_file << "PID 0 running" << endl
	       << "Ready Queue:" << endl
	       << "Wait Queue:" << endl;
   

   // 4. Create necessary variables

   int n, // process ID
       b;  // burst time
   char command; // command from input file
   //vector <string> v; // parsed commands

   // 5. Loop to read and execute
   
   while(!input_file.eof())
   {
      input_file >> command;

      if (command == 'C')
      {
	 input_file >> n; 
	 input_file >> b;
	 output_file << command << " " << n << " " << b << endl;
	 create_process(n, b);
      }
      else if (command == 'D')
      {
	 input_file >> n;
	 output_file << command << " " << n << endl;
	 destroy_process(n);
	 timer_interrupt(0);
      }
      else if (command == 'I')
      {
	 output_file << command << endl;
	 timer_interrupt(0);
      }
      else if (command == 'W')
      {
	 input_file >> n;
	 output_file << command << " " << n << endl;
	 wait(n);
      }
      else if (command == 'E')
      {
	 input_file >> n;
	 output_file << command << " " << n << endl;
	 timer_interrupt(n);
      }
      else if (command == 'X')
      {
	 output_file << command << endl;
	 exit_program();
	 break;
      }
   }
   // Close files
   input_file.close();
   output_file.close();
   
   return 0;
}



void create_process (int n, int b)
{
   // create new process and intialize elements
   process p;

   p.pid = n; 
   p.burst_time = b;
   p.parent_id = curr.pid;
   p.quantum_time =  quant_time;
   p.event_id = 0;
   // initialize event and children??
   //p.event 

   // set up children for current process
   curr.children_id.push_back(p.pid);

   // put process in ready queue
   if(curr.pid == 0)
   {
      curr = p; // if current process is initial process, change current to new process
   }
   else
   {
      ready_queue.push(p);
   }
   
   output_file << "PID " << n << " " << b << " placed on Ready Queue" << endl;

   timer_interrupt(0);
}

void destroy_process (int n) // test function again
{
   
   if(curr.pid != 0)
   {
      // if the current process should be destroyed
      if(curr.pid == n)
      {
	 output_file << "PID " << curr.pid << " " << curr.burst_time
		     << " terminated" << endl;
	 // destroy children
	 if(!curr.children_id.empty())
	 {
	    for(int i = 0; i < curr.children_id.size(); i++)
	    {
	       destroy_process(curr.children_id[i]);
	    }
	 }

	 //set current
	 if(!ready_queue.empty())
	 {
	    curr = ready_queue.front();
	    ready_queue.pop();
	 }
	 else
	 {
	    curr = init;
	 }
      }
      else
      {
	 // create temp
	 queue <process> temq;
	 process temp;
	 process temp2;
	 bool flag = false;

	 // check ready queue

	 if(!ready_queue.empty() && flag == false)
	 {
	    // create empty queue
	    queue <process> empty;
	    
	    while(!ready_queue.empty())
	    {
	       temp = ready_queue.front();
	       
	       // check event id
	       if(temp.pid == n && flag == false)
	       {
		  temp2 = temp;
		  
		  output_file << "PID " << temp.pid << " " << temp.burst_time
			      << " terminated" << endl;
		  ready_queue.pop();
		  flag = true;
	       }
	       else
	       {
		  temq.push(temp);
		  ready_queue.pop();
	       }
	    }
	    // swap queues
	    temq.swap(ready_queue);
	    empty.swap(temq); // clear temp queue
	 }
	 
	 // check wait queue
	 if(!wait_queue.empty() && flag == false)
	 {
	    // create empty queue
	    queue <process> empty;
	    
	    while(!wait_queue.empty())
	    {
	       temp = wait_queue.front();
	       
	       // check event id
	       if(temp.pid == n && flag == false)
	       {
		  temp2 = temp;
		  output_file << "PID " << temp.pid << " " << temp.burst_time
			      << " terminated" << endl;
		  wait_queue.pop();
		  flag = true;
	       }
	       else
	       {
		  temq.push(temp);
		  wait_queue.pop();
	       }
	    }
	    // swap queues
	    temq.swap(wait_queue);
	    empty.swap(temq); // clear temp queue
	 }
	       
	 // destroy children
	 if(!temp2.children_id.empty())
	 {
	    for(int i = 0; i < temp2.children_id.size(); i++)
	    {
	       destroy_process(temp2.children_id[i]);
	    }
	 }
	    
      }
   }
	   
   //timer_interrupt();
}


void timer_interrupt(int n)
{
   // always make sure curr pid != 0
   // if burst time = 0
   if(curr.pid != 0 && curr.burst_time == 0)
   {
      destroy_process(curr.pid);
   }
   
   // if quantum time = 0
   if(curr.pid != 0 && curr.quantum_time == 0)
   {
      curr.quantum_time = quant_time;
      ready_queue.push(curr);
      output_file << "PID " << curr.pid << " " << curr.burst_time
		  << " placed on Ready Queue" << endl;

      // set new curr
      if(!ready_queue.empty())
      {
	 curr = ready_queue.front();
	 ready_queue.pop();
      }
      else
      {
	 curr = init;
      }
   }
   if(n != 0)
   {
      event(n);
   }
   
   // running process
   if (curr.pid != 0)
   {
      output_file << "PID " << curr.pid << " " << curr.burst_time
		  << " running with " << curr.quantum_time << " left" << endl;
   }
   else
   {
      output_file << "PID 0 running" << endl;
   }
   
   // decrease burst and quantum time
   if(curr.pid != 0)
   {
      curr.burst_time--;
      curr.quantum_time--;
   }
   
   // print queues
   output_file << "Ready Queue: ";
   print_queue(ready_queue);
   output_file << "Wait Queue: ";
   print_queue(wait_queue);
   
}

void wait(int e)
{
   
   if(curr.pid != 0)
   {
      // set event_id and reset q time
      curr.event_id = e;
      curr.quantum_time = quant_time;
      
      // add to wait queue
      wait_queue.push( curr);
      
      output_file << "PID " << curr.pid << " " << curr.burst_time
		  << " placed on Wait Queue" << endl;
      
      // set new current process
      if(!ready_queue.empty())
      {
	 curr = ready_queue.front();
      ready_queue.pop();
      }
      else
      {
	 curr = init;
      }
   }
   // else ignore
   timer_interrupt(0);
}

void event(int e)
{
   // make temp
   queue <process> temp_q;
   process temp_p;
   bool flag = false;

   //iterate through original queue unitil event is found
   if(!wait_queue.empty())
   {
      while(!wait_queue.empty())
      {
	 temp_p = wait_queue.front();
	 
	 // check event id
	 if(temp_p.event_id == e && flag == false)
	 {
	    temp_p.event_id = 0;
	    ready_queue.push(temp_p);
	    
	    output_file << "PID " << temp_p.pid << " " << temp_p.burst_time
			<< " placed on Ready Queue" << endl;
	    wait_queue.pop();
	    flag = true;
	 }
	 else
	 {
	    temp_q.push(temp_p);
	    wait_queue.pop();
	 }
      }
      // swap queues
      
      temp_q.swap(wait_queue);
   }
   // else ignore command
   //timer_interrupt();
   
}

void exit_program()
{
   output_file << "Current state of simulation:" << endl;
   
   if(curr.pid == 0)
   {
      output_file << "PID 0 running" << endl;
   }
   else
   {
      output_file << "PID " << curr.pid << " " << curr.burst_time
		  << " running with " << curr.quantum_time << " left" << endl;
   }
   output_file << "Ready Queue: ";
   print_queue(ready_queue);
   
   output_file << "Wait Queue: ";
   print_queue(wait_queue);
}

void print_queue(queue <process> q)
{
   process p;
   
   while(!q.empty())
   {
      p = q.front();
      
      output_file << "PID " << p.pid << " " << p.burst_time << " ";

      if(p.event_id != 0)
      {
	 output_file << p.event_id << " ";
      }

      q.pop();
   }
   output_file << endl;
}


// Questions
// 1. Should I use classes or struct? Are we worried about private members?
// 2. A better way to parse command
// 3. Should the output file be a global variable?
   /*yeah, because the other functions print to the output stream*/
// 4. Is it possible for a wrong command to be entered


//Remember
// 1. to take care of newline character
// 2. event should be run in timer_interrupt?? how do I do that
//        interrupt takes an int, or set to 0

  
