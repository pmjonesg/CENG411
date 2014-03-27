/*
 *  File:    timeday.c
 *  Course:  CENG411
 *  Author:  Peter Jones
 *  Date:    Wednesday 26 March, 2014
 *  Purpose: This program displays the current time of day then exits with a code of 7
 *
 */

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/time.h>
#include <stdlib.h>

void h()
{
	struct timeval currtime;
	struct tm* current;
	char time_string[40];

	/* Get time of day */
	gettimeofday(&currtime, NULL);
	current = localtime(&currtime.tv_sec);

	/* Format time */
	strftime(time_string, sizeof(time_string), "%H:%M:%S", current);
	fprintf(stdout, "Current time of day: %s\n", time_string);

}

/* Start of main program */
int main(int argc, char **argv)
{
	int i;
	fprintf(stdout, "Current process: %d\n Parent process id: %d\n", getpid(), getppid());

	/* Declare handler */
	atexit(h);

	for(i = 0; i < 5; i++)
	{
		fprintf(stdout, "Loop %d\n", i);
		sleep(1);
	}

/* Exit to call interrupt */
	exit(7);

}
