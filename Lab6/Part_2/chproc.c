/*
 * File:    chproc.c
 * Course:  CENG411
 * Author:  Peter Jones
 * Date:    Wednesday 26 March, 2014
 * Purpose: This program creates a child process when SIGINT is sent and measures the time that
 *          the child process used
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>

/* This handler signals that a SIGCHLD interrupt has been catched */
void childInt(int signum)
{
	fprintf(stdout, "SIGCHILD Interrupt \n");
}

/* This handler creates the child and calculates the time */
void h(int signum)
{
	struct tms start, end;
	struct timeval time;
	long clockTicksPerSecond = sysconf(_SC_CLK_TCK);

	/* Start measuring time for process just before it happens */
	times(&start);
	system("last | sort -r | wc > /dev/null");
	/* Send SIGCHLD signal AFTER the process has been created */
	signal(SIGCHLD, childInt);
	times(&end);

	/* Display the time the process took */
	fprintf(stdout, "Time used by user child: %8.4lf seconds.\n", (end.tms_cutime - start.tms_cutime) / (double) clockTicksPerSecond);
	fprintf(stdout, "Time used by system child: %8.5lf seconds.\n", (end.tms_cstime - start.tms_cstime) / (double) clockTicksPerSecond);
  
}

/* Start of main program */
int main(int argc, char **argv)
{
	/* Declare handler */
	void h(int);
	int i;
  
	fprintf(stdout, "Process id: %d\nParent process id: %d\n\n", getpid(), getppid());

	/* Send signal to create children */
	signal(SIGINT, h);
	signal(SIGINT, h);
 
	return 0;
}
