#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "person.h"
#include "findPerson.c"

static FILE *myDB;

void firstInterrupt(int signum)
{
 findPerson();

}

int main(int argc, char **argv)
{
	void firstInterrupt(int);
  FILE *myDB = fopen("myDB", "r");

  signal(SIGINT, firstInterrupt);

	kill(getpid(), SIGINT);
  fclose(myDB);

	for(;;) sleep(1);

  return 0;
}
