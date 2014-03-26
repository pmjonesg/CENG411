#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>

void childInt(int signum)
{
	fprintf(stdout, "SIGCHILD Interrupt \n");
}

void h(int signum)
{
  struct tms start, end;
  struct timeval time;
	long clockTicksPerSecond = sysconf(_SC_CLK_TCK);

	times(&start);
  system("last | sort -r | wc > /dev/null");
	signal(SIGCHLD, childInt);
	times(&end);

	fprintf(stdout, "Time used by user child: %8.4lf seconds.\n", (end.tms_cutime - start.tms_cutime) / (double) clockTicksPerSecond);
	fprintf(stdout, "Time used by system child: %8.5lf seconds.\n", (end.tms_cstime - start.tms_cstime) / (double) clockTicksPerSecond);
  
}

int main(int argc, char **argv)
{
  void h(int);
  int i;
  
  fprintf(stdout, "Process id: %d\nParent process id: %d\n\n", getpid(), getppid());

  signal(SIGINT, h);
  signal(SIGINT, h);
 
  return 0;
}
