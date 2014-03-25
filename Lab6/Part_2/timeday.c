#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/time.h>
#include <stdlib.h>

void h(int signum)
{
  struct timeval currtime;
  struct tm* current;
  char time_string[40];

  gettimeofday(&currtime, NULL);
  current = localtime(&currtime.tv_sec);

  strftime(time_string, sizeof(time_string), "%H:%M:%S", current);
  fprintf(stdout, "Current time of day: %s\n", time_string);
  exit(7);
}

int main(int argc, char **argv)
{
  void h(int);
  int i;

  fprintf(stdout, "Current process: %d\n Parent process id: %d\n", getpid(), getppid());

  signal(SIGINT, h);

  for(i=0;i<10;i++) { 
  fprintf(stdout, "Interrupt: %d\n", i);
  sleep(7);
  }

  return 0;
}
