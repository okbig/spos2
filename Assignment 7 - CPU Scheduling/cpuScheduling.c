//SCHEDULING ALGORITHM SIMULATION ...FCFS, SJF, SRTN

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 5

struct proc
{
	int proc, at, bt,wt, tat,flag, ft, start_time;
};

void sort();
void displayResult();
void fcfs();
void sjf_p();
void sjf_np();
void rr();
void acceptProcessData(int);
int isarrived(int);

float tot_wt=0.0, avg_wt=0.0;

struct proc p[MAX];

int n, sum, temp[MAX];

#include "queue_ADT.c"

void acceptProcessData(int c) {
	 for(int i=0;i<n;i++) 
	{
		 printf("\nEnter process no : ");
		 scanf("%d",&p[i].proc);

		 printf("\nEnter arrival time : ");
		 scanf("%d",&p[i].at);

		 printf("\nEnter service time : ");
		 scanf("%d",&p[i].bt);
	
		sum += p[i].bt; //sjf, sjf_p, rr
			
		if(c==1)  temp[i] = p[i].bt; //For SJF Preemptive and RR
		 printf("\n-----------------------------\n");
	 }//for ends
}//accept function

void fcfs()
{
	int temp, time;
	acceptProcessData(0);//run time
	sort();
	time=0;

	for(int i=0;i<n;i++)
	{
		p[i].start_time = time;
		p[i].wt = p[i].start_time-p[i].at; //WT = START TIME - ARRIVAL TIME
		tot_wt += p[i].wt;
		time    += p[i].bt;
		p[i].ft = time;
	
		p[i].tat=p[i].ft-p[i].at;   //TURNAROUND T = FINISH T + ARRIVAL T
	}//for ends
	displayResult();
}//fcfs

//DEFINITION OF SORT FUNCTION
void sort()
{
	 int i,j;
	 struct proc temp;

	 for(i=0;i<n-1;i++)  {
		 for(j=0;j<n-1;j++) {
			 if(p[j].at >= p[j+1].at) {
				  temp=p[j];
				  p[j]=p[j+1];
				  p[j+1]=temp;
			 }//if
		 }//for
	 }//for

}//END OF SORT FUNCTION

void displayResult()
{
	 printf("\n\nRESULT IS :\n");

	 printf("\nPROCESS\t ARRIVAL TIME \t SERVICE TIME\t   FINISH T\t   WAITNG T\t   TURNAROUND T\n------------------------------------------------------------------------------------\n");

	 for(int i=0;i<n;i++)
	 {
		 printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].proc,p[i].at,p[i].bt,p[i].ft,p[i].wt,p[i].tat);
	 }
	
	printf("\nTotal weight time: %f", tot_wt);
	printf("\n Average waiting time: %f \n" , tot_wt/n);

}

void sjf_np() //SJF Non-Preemptive
{
	int i,j=0,smallest,id,time = 0;
	acceptProcessData(0);	
	while(time<sum) {
		smallest=9999;
		for(i=0;i<n;i++) {
			if(p[i].flag==0) {
				if((p[i].at <=time) && (p[i].bt < smallest)) {
					id=i;
					smallest=p[i].bt;
				}//inner if
			}//outer if
		 }//for

		 if(p[id].flag!=1) {

			p[id].start_time = time;
			
			p[id].wt = p[id].start_time - p[id].at; //WT = START TIME - ARRIVAL TIME
			tot_wt += p[id].wt;
			p[id].flag=1;

			time += p[id].bt;
			p[id].ft = time;
			p[id].tat=p[id].ft - p[id].at;   //TURNAROUND T = FINISH T + ARRIVAL T
		}//if
	}//while
	displayResult();
 }//sjf_np

void sjf_p() //SJF Preemptive
{
	int i,j=0,smallest,id,time = 0;
	acceptProcessData(1);	

	while(time<sum) {
		smallest=9999;
		for(i=0;i<n;i++) {
			if(p[i].flag==0) {
				if((p[i].at <=time) && (p[i].bt < smallest)) {
						id=i;
						smallest=p[i].bt;
					}//inner if
				}//outer if
		}//for

		p[id].bt--;
		time++;
		if(p[id].bt == 0)
		{
			p[id].ft = time;
			p[id].bt = temp[id]; //Copy the original burst time
			p[id].wt = time - p[id].at - temp[id];
			tot_wt += p[id].wt;
			p[id].flag=1;
			p[id].tat = p[id].ft - p[id].at; //Finish time - arrival time
		}		
	}//while    
	displayResult();  
}//sjf_p

void rr() //Round robin
{
	int i, time=0, timeq=0, temp_tq;
	acceptProcessData(1);	
	printf("\n\nEnter time Quantum : ");
	scanf("%d",&timeq);

	//insert first process in the Queue
	InsertQ(time);

	while(time<sum) {
		i = DeleteQ();   //Dequeue a process

		temp_tq = timeq;    //time quantum

		while( temp_tq != 0 && p[i].bt != 0 )
		{
			temp_tq--;
			p[i].bt--;
			time++;

			 //Enqueue arrived processes
			if(isarrived(time))
				InsertQ(time);
		} //inner while

		
		//if current process is over
		if(p[i].bt == 0 && p[i].flag==0)
		{
			p[i].ft = time;
			p[i].bt = temp[i]; //Copy the original burst time
			p[i].wt = time - (p[i].at + temp[i]);
			p[i].tat = p[i].wt + temp[i];
			tot_wt += p[i].wt;
			p[i].flag=1;
		}
		else //insert current process in the Queue
			InsertCP(i);		
	}//while    
	displayResult();  
}//RR

int isarrived(int time)
{
	int i;

	for(i=0;i<n;i++)
	{
		if(p[i].at == time)
			return 1;
	}
	return 0;
}//End

//Main begins
int  main()
{
	int ch;
	 printf("\n\nEnter total number of processes : ");
	 scanf("%d",&n);

	printf("\n ***********Menu ****************\n");
	printf("\n 1 - FCFS");
	printf("\n 2 - SJF-NonPreemptive");
	printf("\n 3 - SJF-Preemptive");
	printf("\n 4 - Round Robin");
	printf("\n Enter your option : ");
	scanf("%d", &ch);
	switch(ch){
		case 1: fcfs();
				break;
		case 2: sjf_np();
				break;
		case 3: sjf_p();
				break;
		case 4: rr();
				break;
	}//switch
}//main ends

/* Output

---------FCFS------------
Enter total number of processes : 5

 ***********Menu ****************

 1 - FCFS
 2 - SJF-NonPreemptive
 3 - SJF-Preemptive
 4 - Round Robin
 Enter your option : 1

Enter process no : 1

Enter arrival time : 0

Enter service time : 1

-----------------------------

Enter process no : 2

Enter arrival time : 3

Enter service time : 4

-----------------------------

Enter process no : 3

Enter arrival time : 1

Enter service time : 4

-----------------------------

Enter process no : 4

Enter arrival time : 0

Enter service time : 1

-----------------------------

Enter process no : 5

Enter arrival time : 5

Enter service time : 5

-----------------------------


RESULT IS :

PROCESS	 ARRIVAL TIME 	 SERVICE TIME	   FINISH T	   WAITNG T	   TURNAROUND T
------------------------------------------------------------------------------------
1		0		1		1		0		1
4		0		1		2		1		2
3		1		4		6		1		5
2		3		4		10		3		7
5		5		5		15		5		10

Total weight time: 10.000000
 Average waiting time: 2.000000 



--------------SJF-NonPreemptive------------------
eyantra@eyantra-OptiPlex-7050:~/Downloads/Programs/Assignment 7 - CPU Scheduling$ ./a.out


Enter total number of processes : 4

 ***********Menu ****************

 1 - FCFS
 2 - SJF-NonPreemptive
 3 - SJF-Preemptive
 4 - Round Robin
 Enter your option : 2

Enter process no : 1

Enter arrival time : 0

Enter service time : 7

-----------------------------

Enter process no : 2

Enter arrival time : 2

Enter service time : 4

-----------------------------

Enter process no : 3

Enter arrival time : 4

Enter service time : 2

-----------------------------

Enter process no : 4

Enter arrival time : 7

Enter service time : 1

-----------------------------


RESULT IS :

PROCESS	 ARRIVAL TIME 	 SERVICE TIME	   FINISH T	   WAITNG T	   TURNAROUND T
------------------------------------------------------------------------------------
1		0		7		7		0		7
2		2		4		14		8		12
3		4		2		10		4		6
4		7		1		8		0		1

Total weight time: 12.000000
 Average waiting time: 3.000000  

--------------SJF-Preemptive---------------------
Enter total number of processes : 4

 ***********Menu ****************

 1 - FCFS
 2 - SJF-NonPreemptive
 3 - SJF-Preemptive
 4 - Round Robin
 Enter your option : 3

Enter process no : 1

Enter arrival time : 0

Enter service time : 7

-----------------------------

Enter process no : 2

Enter arrival time : 2

Enter service time : 4

-----------------------------

Enter process no : 3

Enter arrival time : 4

Enter service time : 2

-----------------------------

Enter process no : 4

Enter arrival time : 7

Enter service time : 1

-----------------------------


RESULT IS :

PROCESS	 ARRIVAL TIME 	 SERVICE TIME	   FINISH T	   WAITNG T	   TURNAROUND T
------------------------------------------------------------------------------------
1		0		7		14		7		14
2		2		4		6		0		4
3		4		2		8		2		4
4		7		1		9		1		2

Total weight time: 10.000000
 Average waiting time: 2.500000 

------------------ROUND ROBIN------------------------------
eyantra@eyantra-OptiPlex-7050:~/Downloads/Programs/Assignment 7 - CPU Scheduling$ ./a.out


Enter total number of processes : 4

 ***********Menu ****************

 1 - FCFS
 2 - SJF-NonPreemptive
 3 - SJF-Preemptive
 4 - Round Robin
 Enter your option : 4

Enter process no : 1

Enter arrival time : 0

Enter service time : 5

-----------------------------

Enter process no : 2

Enter arrival time : 0

Enter service time : 4

-----------------------------

Enter process no : 3

Enter arrival time : 0

Enter service time : 2

-----------------------------

Enter process no : 4

Enter arrival time : 0

Enter service time : 3

-----------------------------


Enter time Quantum : 2


RESULT IS :

PROCESS	 ARRIVAL TIME 	 SERVICE TIME	   FINISH T	   WAITNG T	   TURNAROUND T
------------------------------------------------------------------------------------
1		0		5		14		9		14
2		0		4		12		8		12
3		0		2		6		4		6
4		0		3		13		10		13

Total weight time: 31.000000
 Average waiting time: 7.750000 



*/
