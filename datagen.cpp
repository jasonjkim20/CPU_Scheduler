#include "cpuSched.h"
        
using namespace std;

int main()

{
  Scheduler sched;
  int   hist[10];
  int   index;
  int   i;

  int   max_CPU_burst, min_CPU_burst;
  int   this_CPU_burst_length;
  int   this_priority;
  int   ave_interarr_time;
  int last_arrival_time = 0;
  long this_arrival_time;
  int temp;

  cout << "Maximum CPU Burst: ";
  cin >>   max_CPU_burst;
  cout << "Minimum CPU Burst: ";
  cin >>   min_CPU_burst;
  cout << "Average Interarrival Time: ";
  cin >>   ave_interarr_time;
  cout << "\n";

  ofstream outfile;
  outfile.open ("datagen.txt");  // generate a text file 

// Assuming that there are 10000 processes 
  // cout << "Index " << "Arrival time  "<< "CPU Burst Length " << "  Priority" << endl;

  // save the random generated burst time and arrival time  of each process into the text file
    for ( i=1; i<=10000; i++ )
	{
      sched.parameters(ave_interarr_time, last_arrival_time, max_CPU_burst, min_CPU_burst, &this_priority, &this_arrival_time, &this_CPU_burst_length);
      outfile << i << " " << this_arrival_time << " " << this_CPU_burst_length << " " << this_priority << endl;
      last_arrival_time = this_arrival_time;
    }

  outfile.close();  
  sched.fileReader();
  sched.selectSched();

  return 0;
} // function main
