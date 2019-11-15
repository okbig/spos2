#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#include "defined_function.h"
int main()
{
	pid_t pid;
	int arr[10];
	char * argv_list[] = {"ls","-lart","/home",NULL}; 
	pid=fork();    

	if(pid==0)
	{
		accept_nos(arr);
		execv("/bin/ls",argv_list);
		printf("\n This is child \n");
	}
	else
	{
		sleep(50);  
		printf("\n This is parent\n");
	}
}

/* OUTPUT-------------------------------------

	Enter the number of elements:5

	 Enter the elements:

	 Element 1 :3

	 Element 2 :5

	 Element 3 :9

	 Element 4 :2

	 Element 5 :7
total 12
drwxr-xr-x  3 root    root    4096 Nov  4 11:51 .
drwxr-xr-x 24 root    root    4096 Nov  7 12:22 ..
drwxr-xr-x 23 eyantra eyantra 4096 Nov  8 09:04 eyantra

 This is parent

*/
