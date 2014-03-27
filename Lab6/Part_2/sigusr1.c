/*
 * File:    sigusr1.c
 * Course:  CENG411
 * Author:  Peter Jones
 * Date:    Wednesday 26, 2014
 *
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>


void h(int signum)
{
  char * cmd = "ps | wc -l";
  char buffer[100];
  FILE *log, *process;
  time_t when=0L;
  
  /*  Output interrupt to screen */
  if((process = popen(cmd, "r")) != NULL)
  {
    while(fgets(buffer, 100, process) != NULL)
      fprintf(stdout, "Number of processes is: %s", buffer);
    pclose(process);
  }

  /* Write date and # of processes to log.txt */
  log = fopen("log.txt", "a+");
  fprintf(log, "Time: %sProcess Id: %s\n\n", ctime(&when), buffer);
  fclose(log);
}

/* Start main program */
int main(int argc, char **argv)
{
  /* Declare handler */
  void handler(int);
  int i;

  /* Print # of process */
  fprintf(stdout, "The current process id is: %d " "parent is: %d\n", getpid(), getppid());
  
  /* Catch signal SIGUSR1 */
  signal(SIGUSR1, h);

  /* Loop to handle interrupts */
  for(i = 0; i < 10; i++)
  { 
    fprintf(stdout, "Id: %d\n", i);
    sleep(6);
  }

  return 0;
}
