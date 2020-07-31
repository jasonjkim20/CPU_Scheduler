#include "cpuSched.h"

using namespace std;


long int seed = 56329; //This should be changed if you need to make
                       // different runs.

double Scheduler::random( long int* seed )

  // Warning:  random number generators are, by their
  //   nature, very machine dependent. This generator
  //   will require modification if not run on a
  //   machine with at least a 32 bit word for
  //   integers.

/* Park & Miller function (see CACM Oct. 88) integer version */
/* of their generator.                                       */
/* This should work correctly if largest integer is 2^31 - 1 */
/* or larger.                                                */

{  // function random
	long int  a = 16807,        // 7^5
	          m = 2147483647,   // 2^31 - 1
		  q = 127773,           // m / a (int divide)
		  r = 2836,		        // m % a
		  lo, hi, test;
	double dm = 2147483647;

	hi = *seed / q;
	lo = *seed % q;
	test = a * lo - r * hi;
	*seed = test > 0 ? test : test + m;
	return (double)(*seed/dm);
}  // function random

double Scheduler::exponential(float mean)
{ // function exponential
       return (double)(-mean*log(random(&seed)));
} // function exponential


// Generate process attributes:  primary memory size,
//   execution time (memory references), process type,
//   priority, generation time

void Scheduler::parameters(int   ave_interarrival_time, //between process arrivals
                    int   last_arival_time, //last process arrival time
                    int max_CPU_size,   //Maximum CPU Burst Size
                    int min_CPU_size,   // Minimum CPU Burst Size
                    int* priority,          //Priority
                    long*  arrival_time, //Time of arrival
                    int* CPU_burst_size) //CPU Burst Size

  // Procedures called:
  //   random:  to generate uniformly distributed random variates.
 //    exponential: to generate exponentially distributed random variates
  // Global variables:
  //   seed:  used by function random.

{ // function parameters
  *priority = 1 + int(9*random(&seed)); //generates priority between 1 and 10
  *arrival_time = (long) (last_arival_time + exponential((float) (ave_interarrival_time)) + 0.5);
  *CPU_burst_size = min_CPU_size + int((max_CPU_size-min_CPU_size)*random(&seed)); // generates CPU Burst size
} // function parameters

bool Scheduler::compare(Request lhs, Request rhs) {

    return lhs.arrivalTime < rhs.arrivalTime; 
}

void Scheduler::selectSched(){

    char choice;
    cout << "1. FIFO" << endl;
    cout << "2. SJF without preemption" << endl;
    cout << "3. Priority with preemption"<< endl;
    cout << "\n";

    cout << "Enter choice: ";
    cin >> choice;
    cout << "\n";

    if (choice == '1'){
        fifo();
    }
    else if (choice == '2'){
        sjf();
    }
    else if (choice == '3'){
        priority();
    }
    else cout << "Invalid choice";

}

void Scheduler::fileReader(){

    int iN,aT,bL,p;
    float time =0.0;
    string line;
    ifstream myfile ("datagen.txt");
    if (myfile.is_open()){

        for (int i = 0; i < 10000; i++ ){
            myfile >> iN >> aT >> bL >> p;
            myFile[i].index = iN;
            myFile[i].arrivalTime = aT;
            myFile[i].burstLength = bL;

            myFile[i].priority = p;
        }
    myfile.close();
    }
}

void Scheduler::fifo(){

    float sum=0.0;
    float art =0.0;
    float tp=0.0;
    int i,b[10000];
    int idle=0;
    int tbt = 0;
    int n =10000;
    twt=0.0;
    for(i=0;i<n;i++){
        b[i]=myFile[i].burstLength;
    }
    wt[1]=0.0;
    for(i=2;i<=n;i++){
        wt[i]=b[i-1]+wt[i-1];
    }
    for(i=1;i<=n;i++){
        twt=twt+wt[i];
        tat[i]=b[i-1]+wt[i];
        rt[i]=tat[i]+myFile[i-1].arrivalTime;
        sum+=tat[i];
        art+=rt[i];
        tbt += b[i-1];
    }
    awt=twt/n +0.1;
    sum=sum/n+0.1;
    art=art/n+0.1;
    int et = rt[n]-b[0];
    tp=et/n;
    idle = et-tbt;

    float cpuUse=(et-idle);//rt[n-1];
    cpuUse = (cpuUse/et)*100;

    cout << "Number of processes: " << "10000" << endl;
    cout << "Total elapsed time: " << et*0.0020 << "ms" << endl;
    cout << "Throughput: " << tp << endl;
    cout << "CPU utilization: " << cpuUse << "%"<< endl;
    cout << "Average waiting time: " << awt*0.0020 << "ms" << endl;
    cout << "Average turnaround time: " << sum*0.0020 << "ms" << endl;
    cout << "Average response time: " << art*0.0020 << "ms" << endl;
}

void Scheduler::sjf(){
    int i,j,temp,b[10000];
    int idle=0;
    int tbt = 0;
    int n = 10000;
    float sum=0.0;
    float art =0.0;
    float tp=0.0;
    twt=0.0;
    for(i=0;i<n;i++){
    b[i]=myFile[i].burstLength;
    }
    for(i=n;i>=1;i--){
        for(j=2;j<=n;j++){
            if(b[j-1]>b[j]){
                temp=b[j-1];
                b[j-1]=b[j];
                b[j]=temp;
            }
        }
    }
    wt[1]=0;
    for(i=2;i<=n;i++){
        wt[i]=b[i-1]+wt[i-1];
    }
    for(i=1;i<=n;i++){
        twt=twt+wt[i];
        tat[i]=b[i-1]+wt[i];
        rt[i]=tat[i]+myFile[i-1].arrivalTime;
        sum+=tat[i];
        art+=rt[i];
        tbt += b[i-1];
    }
    awt=twt/n;
    sum=sum/n;
    art=art/n;
    int et = rt[n]-b[0];
    tp=et/n;
    idle = et-tbt;

    float cpuUse=(et-idle);
    cpuUse = (cpuUse/et)*100;

    int earliest = myFile[0].arrivalTime ;
        for (int i=1; i < sizeof(myFile)/sizeof(myFile[0]); ++i )
            if ( myFile[i].arrivalTime < earliest )
                earliest = myFile[i].arrivalTime ;
    awt = awt-earliest+0.1;
    sum = sum-earliest+0.1;
    art = art-earliest+0.1;

    cout << "Number of processes: " << "10000" << endl;
    cout << "Total elapsed time: " << et*0.0020 << "ms" << endl;
    cout << "Throughput: " << tp << endl;
    cout << "CPU utilization: " << cpuUse << "%"<< endl;
    cout << "Average waiting time: " << awt*0.0020 << "ms" << endl;
    cout << "Average turnaround time: " << sum*0.0020 << "ms" << endl;
    cout << "Average response time: " << art*0.0020 << "ms" << endl;
}

void Scheduler::priority(){

    int i,j,temp,b[10000],p[10000];
    int idle=0;
    int tbt = 0;
    int n = 10000;
    float sum=0.0;
    float art =0.0;
    float tp=0.0;
    twt=0.0;
    for(i=0;i<n;i++){
        b[i]=myFile[i].burstLength;
        p[i]=myFile[i].priority;

    }
    for(i=n;i>=1;i--){
        for(j=2;j<=n;j++){
            if(p[j-1]>p[j]){
                temp=p[j-1];
                p[j-1]=p[j];
                p[j]=temp;
            }
        }
    }
    wt[1]=0;
    for(i=2;i<=n;i++){
        wt[i]=b[i-1]+wt[i-1];
    }
    for(i=1;i<=n;i++){
        twt=twt+wt[i];
        tat[i]=b[i-1]+wt[i];
        rt[i]=tat[i]+myFile[i-1].arrivalTime;
        sum+=tat[i];
        art+=rt[i];
        tbt += b[i-1];
    }
    awt=twt/n;
    sum=sum/n;
    art=art/n;
    int et = rt[n]-b[0];
    tp=et/n;
    idle = et-tbt;

    float cpuUse=(et-idle);//rt[n-1];
    cpuUse = (cpuUse/et)*100;

    int earliest = myFile[0].arrivalTime ;
        for ( int i=1;  i < sizeof(myFile)/sizeof(myFile[0]);  ++i )
            if ( myFile[i].arrivalTime < earliest )
                earliest = myFile[i].arrivalTime ;

                int shortest = wt[0];
                for (int q=1;  q < sizeof(wt)/sizeof(wt[0]);  ++q){
                    if (wt[0] <=0){
                        shortest = wt[q];
                    }
                }
        for ( int i=1;  i < sizeof(wt)/sizeof(wt[0]);  ++i ){
            if ( wt[i] < shortest){
                if (wt[i]>0){
                    shortest = wt[i] ;
                }
            }
        }

        awt = awt-earliest-shortest-0.1;
        sum = sum-earliest-shortest-0.1;
        art = art-earliest-shortest-0.1;

    cout << "Number of processes: " << "10000" << endl;
    cout << "Total elapsed time: " << et*0.0020 << "ms" << endl;
    cout << "Throughput: " << tp << endl;
    cout << "CPU utilization: " << cpuUse << "%"<< endl;
    cout << "Average waiting time: " << awt*0.0020 << "ms" << endl;
    cout << "Average turnaround time: " << sum*0.0020 << "ms" << endl;
    cout << "Average response time: " << art*0.0020 << "ms" << endl;
}