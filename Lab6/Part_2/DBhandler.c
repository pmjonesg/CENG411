/*
 *  File:    DBhandler.c
 *  Course:  CENG411
 *  Author:  Peter Jones
 *  Date:    Wednesday 26 March, 2014
 *  Purpose: This program open myDB and prints the current record for the first signal given,
 *           advances to the next record given a second signal, and goes back one record given
 *           a third signal
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "person.h"
#include "findPerson.c"

/* Static variables to keep track of offset and file */
static int offset = 60;
static int previous = 60;
static FILE *myDB;

/* This handler reads in the first record */
void firstInterrupt(int signum)
{
	findPerson(0);
}

/* This handler advances one record */
void secondInterrupt(int signum)
{
	findPerson(offset);
	offset += 60;
}

/* This handler goes back to the previous record */
void thirdInterrupt(int signum)
{

	/* Check for first record */
	if(offset != 60)
	{
		previous += 60;
		findPerson(offset - previous);
	}
	else
		findPerson(0);

	/* Terminate program after printing a previous record */
	raise(SIGKILL);
}

/* Start of main program */
int main(int argc, char **argv)
{
	/* Declare interrupts */
	void firstInterrupt(int);
	void secondInterrupt(int);
	void thirdInterrupt(int);
	
	/* Open file to be read */
	FILE *myDB = fopen("myDB", "r");

	/* Show initial record */
	signal(SIGILL, firstInterrupt);
	kill(getpid(), SIGILL);

	/* Advance 2 records */
	signal(SIGSEGV, secondInterrupt);
	raise(SIGSEGV);

	signal(SIGSEGV, secondInterrupt);
	raise(SIGSEGV);

	/* Go back one record */
	signal(SIGTERM, thirdInterrupt);
	raise(SIGTERM);

	/* Close file */
	fclose(myDB);

	for(;;) sleep(1);

	return 0;
}
