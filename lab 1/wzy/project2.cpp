#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	pid_t pid1,pid2;
	pid1=fork();
	if(pid1<0)
	{
		fprintf(stderr,"Fork Failed");
		exit(-1);
	}
	else if(pid1==0)
	{
		//child process
		printf("child1 has been called\n");
		pid2=fork();
		if(pid2<0)
		{
			fprintf(stderr,"Fork Failed");
			exit(-1);
		}
		if(pid2==0)
		{
			printf("child2 has been called\n");
		}
		else
		{
			printf("parent has been called\n");
		}
	}
	return 0;
} 
