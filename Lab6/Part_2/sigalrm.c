#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/times.h>

void shutdown(int signum)
{
	void restart(int);
	struct itimerval restartAlarm;
	int restartTime = ITIMER_REAL;

	fprintf(stdout, "The timer went off at: ");


	signal(SIGALRM, restart);
	//signal(SIGTSTP, SIG_DFL);
	raise(SIGSTOP);

	getitimer(restartTime, &restartAlarm);
	restartAlarm.it_value.tv_sec=2;
	restartAlarm.it_value.tv_usec=33333;
	setitimer(restartTime, &restartAlarm, NULL);


}

void restart(int signum)
{

	fprintf(stdout, "Program restarted at ");
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

	signal(SIGALRM, restart);
/*
	getitimer(restartTime, &restartAlarm);
	restartAlarm.it_value.tv_sec=2;
	restartAlarm.it_value.tv_usec=33333;
	setitimer(restartTime, &restartAlarm, NULL);
*/	
	fprintf(stdout, "Current process: %d\nParent process id: %d\n\n", getpid(), getppid());

	for(i = 0; i < 10; i++)
	{
		fprintf(stdout, "Interrupt: %d\n", i);
		sleep(2);
	}

	return 0;
}
