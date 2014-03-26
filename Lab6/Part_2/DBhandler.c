#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "person.h"
#include "findPerson.c"

static int offset = 60;
static FILE *myDB;

void firstInterrupt(int signum)
{
 findPerson(0);
}

void secondInterrupt(int signum)
{
  findPerson(offset);
	offset += 60;
}

void thirdInterrupt(int signum)
{
  static int previous = 60;
	findPerson(offset - previous);
	if(offset != 60)
	  previous += 60;
	else ;
}

int main(int argc, char **argv)
{
	void firstInterrupt(int);
	void secondInterrupt(int);
  FILE *myDB = fopen("myDB", "r");

  signal(SIGINT, firstInterrupt);
	kill(getpid(), SIGINT);

	signal(SIGINT, secondInterrupt);
	raise(SIGINT);

	signal(SIGINT, thirdInterrupt);
	raise(SIGINT);

  fclose(myDB);

	for(;;) sleep(1);

  return 0;
}
