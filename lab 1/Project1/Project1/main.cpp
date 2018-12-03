#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	pid_t pid;
	pid = fork();
	if (pid<0)
	{
		fprintf(stderr, "Fork Failed");
		exit(-1);
	}
	else if (pid == 0)
	{

	}
	else
	{
		exit(0);
	}
	return 0;
}