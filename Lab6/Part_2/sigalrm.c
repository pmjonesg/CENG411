#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/times.h>
#include <time.h>

void shutdown(int signum)
{
	void restart(int);
	struct itimerval restartAlarm;
	int restartTime = ITIMER_REAL;
	struct timeval current;
	struct tm* current_Time;
	char timeStr[40];

	gettimeofday(&current, NULL);
	current_Time = localtime(&current.tv_sec);
	strftime(timeStr, sizeof(timeStr), "%H:%M:%S", current_Time);
	fprintf(stdout, "The timer went off at: %s", timeStr);

	pid_t childPID = fork();

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
	    kill(getpid(), SIGTSTP);
		}
	}
}

void restart(int signum)
{
	struct timeval currentRestart;
	struct tm* currentRestart_Time;
	char timeStr2[40];

	gettimeofday(&currentRestart, NULL);
	currentRestart_Time = localtime(&currentRestart.tv_sec);
	strftime(timeStr2, sizeof(timeStr2), "%H:%M:%S", currentRestart_Time);
	fprintf(stdout, "Program restarted at %s", timeStr2);

	raise(SIGCONT);
}

int main(int argc, char **argv)
{
	void restart(int);
	struct itimerval restartAlarm;
	int restartTime = ITIMER_REAL;
  void shutdown(int);
	int i;
	struct itimerval nextAlarm;
	int timerType = ITIMER_REAL;

	signal(SIGALRM, shutdown);
	getitimer(timerType, &nextAlarm);
	nextAlarm.it_value.tv_sec=3;
	nextAlarm.it_value.tv_usec=500000;
	setitimer(timerType, &nextAlarm, NULL);


	fprintf(stdout, "Current process: %d\nParent process id: %d\n\n", getpid(), getppid());

	for(i = 0; i < 10; i++)
	{
		fprintf(stdout, "Interrupt: %d\n", i);
		sleep(2);
	}

	return 0;
}
