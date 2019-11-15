/*
Implement following programs to exhibit UNIX Process Control 
Parent process 	- sorts array elements in ascending order 
				- Count number of vowels in the given sentence

Child process 	- sorts array elements in descending order 
				- Count number of words in the given sentence
Demonstrate ORPHAN state; where parent process terminates before child process
*/
  
#include <stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX 20
#include "defined_function.h"

int main()
{
	char str[20];
	int arr[MAX], *status=NULL;
	pid_t cpid;
	
	fflush(stdout);	

	accept_str(str);
	accept_nos(arr);

					

	cpid = fork();

	if( cpid == 0 ) //CHILD PROCESS
	{
		sleep(20);
		printf("\n*************** This is child process ***************\n ");
		printf("\n\t My process id is : %d", getpid());
		printf("\n\t My Parent process id is : %d (Parent process has terminated; 				hence child process is ORPHAN", getppid());
		
 		sort_desc(arr);
		cnt_vowels(str);
		printf("\n*************** Child process terminates *************\n");			
	}
	else
	{
		printf("\nChild process forked & sleeping!\nMeanwhile, parent continues 				execution & terminates...\n\n");	
	
	}//end of if-else

	return 0;	
}//end of main

/*OUTPUT------------------
Enter the statement for calculating number of vowels and words :Enter the statement for calculating number of vowels and words

	Enter the number of elements:5

	 Enter the elements:

	 Element 1 :1

	 Element 2 :45

	 Element 3 :78

	 Element 4 :90

	 Element 5 :100

Child process forked & sleeping!
Meanwhile, parent continues 				execution & terminates...
*************** This is child process ***************
 
	 My process id is : 4189
	 My Parent process id is : 1316 (Parent process has terminated; 				hence child process is ORPHAN

	The Numbers In Descending Order Are:
	 100 90 78 45 1  
	 Number of vowels in the given string is: 18

*************** Child process terminates *************
*/


