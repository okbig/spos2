/*
Implement following programs to exhibit UNIX Process Control 
Parent process 	- sorts array elements in ascending order 

Child process 	- sorts array elements in descending order 
Demonstrate ZOMBIE state; where child process terminates and waits for parent process to collect its exit status */
  
#include <stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX 20
#include "defined_function.h"

int main()
{
	int arr[MAX], *status=NULL;
	pid_t cpid;
	
	fflush(stdout);	

	accept_nos(arr);

	printf("\n\tThis is the parent process. PID: %d",getpid());
	
	sort_asc(arr);

	cpid = fork();

	if( cpid == 0 ) //CHILD PROCESS
	{
		sleep(5);
		printf("\n*************** This is child process ***************\n ");
		printf("\n\t My process id is : %d", getpid());
		printf("\n\t My Parent process id is : %d", getppid());
		
 		sort_desc(arr);
		printf("\n*************** Child process terminates *************\n");			
	}
	else
	{
		printf("\n\tParent process sleeping!\n");
		sleep(25);
	 	printf("\n\nSleep time complete!\n");
	 	printf("\nWait returns: (cleanup zombie process from process table)");	
	}//end of if-else

	return 0;	
}//end of main

/*
Output

	Enter the number of elements:4

	 Enter the elements:

	 Element 1 :243

	 Element 2 :54234

	 Element 3 :234

	 Element 4 :654

	This is the parent process. PID: 2754

	The Numbers In Ascending Order Are:
	 234 243 654 54234 
	Parent process sleeping!
	 234 243 654 54234 
*************** This is child process ***************
 
	 My process id is : 2755
	 My Parent process id is : 2754

	The Numbers In Descending Order Are:
	 54234 654 243 234 
*************** Child process terminates *************


Sleep time complete!

Wait returns: (cleanup zombie process from process table)
*/
