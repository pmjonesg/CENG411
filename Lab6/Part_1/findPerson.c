/*
*  File: findPerson.c
* Course: CENG411
*  Author: Peter Jones
*  Date: Wednesday 26, March 2014
*
*  Program will create a random person then read the record straigt away.
* It demonstrates that when opening a file in a+ mode you can write as well
* as read (writing at the end of the file and reading at the beginning)
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include "person.h"
#include <string.h>

/* Declaration of names for random generation */
char names[][10]={ "George","Ann","Renata","Betty","Sam","Vince",
                 "Stephane","Ringo","Helen","Elmer","Steve",
                 "Aaron","Kim","George","Paul","John","Jean Luc","Colm" };
char lastNames[][10]= {"Smith","Kline","Chin","Arnold","Saxby","Jones",
                      "Stivic","Michaud","Crompton","Ogilvy","Singh",
                      "Picard","Ngo"};
char role[][25]={"Captain","Ensign","Red Shirt","Red Shirt","Red Shirt",
                 "Crew","Medical Officer","Science Officer","Crew",
                 "Crew","Transporter Chief","Morale Officer","Crew",
                 "Crew","Navigator","Engineer"};

/* This function generates a random person from the arrays listed above */
void makePerson(struct PERSON *p)
{
   strcpy(p->firstName,names[rand()%sizeof(names)/sizeof(names[0])]);
   strcpy(p->lastName,lastNames[rand()%sizeof(lastNames)/sizeof(lastNames[0])]);
   strcpy(p->position,role[rand()%sizeof(role)/sizeof(role[0])]);
   p->age =  rand()%106;
   p->sex = (rand()%2) ? 'M' : 'F';
   }

/* Start main program */
int main(int argc, char * argv[],char * envp[])
{
  struct PERSON person;
  char response[512];

	/* Open file which already contains data */
  FILE *myDB=fopen("myDB","a+");

	/* Create a random person (will always create the same person as the first time) */
  makePerson(&person);
  fwrite(&person, sizeof(person),1, myDB);

  /* Get position of cursor */
	long sz = ftell(myDB);
	//fprintf(stdout, "Size of myDB is: %ld\n", sz);
	person.recordNo = (int) (sz/ sizeof(person));
	fprintf(stdout, "Person created\n");
  displayPerson(person);

	/* Print firt record read (should be the first one */
	fprintf(stdout, "\nRecord read");
  fseek(myDB, sz, SEEK_SET);
  fprintf(stdout,"\nPosition in file before reading it: %ld\n", ftell(myDB));
  fread(&person,sizeof person,1,myDB);
  displayPerson(person);
  fprintf(stdout,"Position in file after reading it: %ld\n\n", ftell(myDB));
    
	/* Close file and end program */
  fclose(myDB);  

  return 0;
}
