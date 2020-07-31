Problem 1: CPU Scheduling
This part of the projects simulates a CPU scheduler. Since it is a simulation, there are no
real processes/threads to be scheduled. Instead, you simulate the arrival of new processes
and threads. Whenever a new process/thread arrives (in simulation) into the ready queue,
the CPU scheduler is invoked. Each simulated process (or thread) has the following
parameters: <Process ID, Arrival time, Priority, CPU burst units>. Each of these is an
integer parameter. One CPU burst unit is equivalent to CPU time needed to execute the

following loop:

for (int i=0, int temp =0; i < 10000; i++)
 if (i mod 2 ==0) temp= i/2 + 1;
 else temp=2*i;}
 
For example, if a process <5, 100, 2, 20> is read by your simulator, it means a new
process P arrived into the system at simulation time 100, with priority 2. It executes the
above loop 20 times before finishing and leaving the system. At the time of invocation of
the scheduler, the user indicates the type of scheduling to be enforced. You are required
to implement the following scheduling types:
1. FIFO
2. SJF without preemption
3. Priority with preemption
Each run will handle scheduling of 10,000 (simulated) processes. In other words, as soon
as the number of processes that have completed CPU execution reaches 10,000, you can
stop running the program and print the following statistics. Vary the CPU burst between
2 and 30, priority between 1 and 10, and interarrival time between 1 and 100 (in CPU
units). Since this is a simulation, you must maintain a logical clock within your program
to keep track of current time. All times are expressed in terms of CPU burst units. So they
are not actual elapsed time (in msec) but simulate dtimes.
Statistics for the Run
Number of processes: 10,000
Total elapsed time (for the scheduler):
Throughput (Number of processes executed in one unit of CPU burst time):
CPU utilization:
Average waiting time (in CPU burst times):
Average turnaround time (in CPU burst times):
Average response time (in CPU burst times): 
NOTE: It is not absolutely necessary to include the 3-line loop in your simulation
representing 1 CPU cycle time. It is only to make the program more realistic for you. The
project is more like your scheduling homework where you were given a table of
processes and asked to schedule.
Hint1: Since the processes to be scheduled are not real but simulated, you need a
generator to generate the process requests to the CPU scheduler. The generator generates
and stores the process requests in a file. Your scheduler program reads the file and
simulates real process arrives. In order to control the process arrivals and the CPU burst
time for each process, your generator requires two inputs: Average number of process
arrivals per unit time and average number of burst units. You need to vary these two
parameters and run different cases. A sample generator function is made available to you:
datagen.cpp. You can pick your own parameters to the program.
Hint 2: Since there are only 10,000 processes, it may be easy to generate all 10,000
processes first along with their attributes and save them in a file. The file can be read by
your scheduling simulator, store all the 10,000 records in a queue, and then process them.
This is an easy way to do it. But you can choose any method you like.