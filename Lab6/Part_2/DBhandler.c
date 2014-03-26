#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "person.h"
#include "createPeople.c"

static FILE *myDB;

void firstInterrupt(int signum)
{
  struct PERSON firstRec;

	fread(&firstRec, sizeof(firstRec), 1, myDB);
	displayPerson(firstRec);
}

int main(int argc, char **argv)
{
	void firstInterrupt(int);
  FILE *myDB = fopen("myDB", "r");

  signal(SIGINT, firstInterrupt);
	raise(SIGINT);

  fclose(myDB);

	for(;;) sleep(1);

  return 0;
}
