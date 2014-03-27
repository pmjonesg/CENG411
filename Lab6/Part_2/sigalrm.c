/*
 * File:    sigalrm.c
 * Course:  CENG411
 * Author:  Peter Jones
 * Date:    Wednesday 26 March, 2014
 * Purpose: This program sets a timer at 3.5 seconds for a SIGSTP signal, and just before the
 *          signal is raised another timer gets set to send a SIGCONT at 2.33 seconds after 
 *          the program stops
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/times.h>
#include <time.h>

/* This handler sets the restart timer and stops the process */
void shutdown(int signum)
{
	void restart(int);
	struct itimerval restartAlarm;
	int restartTime = ITIMER_REAL;
	struct timeval current;
	struct tm* current_Time;
	char timeStr[40];

	/* Get time when the timer went of (before shut down) */
	gettimeofday(&current, NULL);
	current_Time = localtime(&current.tv_sec);
	strftime(timeStr, sizeof(timeStr), "%H:%M:%S", current_Time);
	fprintf(stdout, "The timer went off at: %s", timeStr);

	/* Create a child process to restart the program */
	pid_t childPID = fork();

	/* Detect the child process and set timer accordingly */ 
	if(childPID >= 0)
	{
		if(childPID == 0)
		{
	    signal(SIGALRM, restart);
	    getitimer(restartTime, &restartAlarm);
	    restartAlarm.it_value.tv_sec=2;
	    restartAlarm.it_value.tv_usec=33333;
	    setitimer(restartTime, &restartAlarm, NULL);
	  }
		else
		{
			/* Once the timer has been set stop the parent */
	    kill(getpid(), SIGTSTP);
		}
	}
}

/* This handler restarts the parent process */
void restart(int signum)
{
	struct timeval currentRestart;
	struct tm* currentRestart_Time;
	char timeStr2[40];
 
	/* Get time when the process restarted */
	gettimeofday(&currentRestart, NULL);
	currentRestart_Time = localtime(&currentRestart.tv_sec);
	strftime(timeStr2, sizeof(timeStr2), "%H:%M:%S", currentRestart_Time);
	fprintf(stdout, "Program restarted at %s", timeStr2);
	
  /* Send signal to resume the process */
	raise(SIGCONT);
}

/* Start of main program */
int main(int argc, char **argv)
{
 /* Declare interrupt */
 void shutdown(int);
	struct itimerval nextAlarm;
	int timerType = ITIMER_REAL;
	int i;

	/* Set first alarm and call interrupt */
	signal(SIGALRM, shutdown);
	getitimer(timerType, &nextAlarm);
	nextAlarm.it_value.tv_sec=3;
	nextAlarm.it_value.tv_usec=500000;
	setitimer(timerType, &nextAlarm, NULL);

	fprintf(stdout, "Current process: %d\nParent process id: %d\n\n", getpid(), getppid());

	/* Spend time looping to detect changes */
	for(i = 0; i < 10; i++) 
	{
    fprintf(stdout, "Loop: %d\n", i);
		sleep(1);
	}

	return 0;
}
