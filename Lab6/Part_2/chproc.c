#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

void h(int signum)
{
  fprintf(stdout, "CHLD Interrupt");
}

int main(int argc, char **argv)
{
 // struct tms cur_time;
  struct timeval time;

  void h(int);
  int i;
  
  fprintf(stdout, "Process id: %d\nParent process id: %d\n\n", getpid(), getppid());

  system("last | sort -r | wc > /dev/null");
  
  signal(SIGCHLD, h);

  for(i=0;i<10;i++)
  { 
    fprintf(stdout, "%d", i);
    sleep(5);
  }


  
 
  return 0;
}
