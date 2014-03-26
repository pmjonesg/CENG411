/*
   File: findPerson.c
	 Course: CENG411
   Author: Leon King,J230,x4200
   Date: Wednesday Feb 03, 2010   21:32 PM
 
   Program will prompt you for a record number
   Using random access it will retrieve the specified record
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include "person.h"
#include <string.h>

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

void makePerson(struct PERSON *p)
{
   strcpy(p->firstName,names[rand()%sizeof(names)/sizeof(names[0])]);
   strcpy(p->lastName,lastNames[rand()%sizeof(lastNames)/sizeof(lastNames[0])]);
   strcpy(p->position,role[rand()%sizeof(role)/sizeof(role[0])]);
   p->age =  rand()%106;
   p->sex = (rand()%2) ? 'M' : 'F';
   }

int main(int argc, char * argv[],char * envp[])
{
  struct PERSON person;
  char response[512];

  FILE *myDB=fopen("myDB","a+");
  makePerson(&person);
  fwrite(&person, sizeof(person),1, myDB);
	fseek(myDB, 0L, SEEK_END);
	int sz = ftell(myDB);
	fprintf(stdout, "Size of myDB is: %d\n", sz);
	person.recordNo = (int) (sz/60);
  displayPerson(person);
  sprintf(response, "%d", sz/60);

  fprintf(stdout,"The size of an PERSON is: %lu\n\n",sizeof person);
  while(true)
  {
    fprintf(stdout,"Enter a record number. (-1 exits): ");
    fflush(stdout);
    fgets(response,10,stdin);
		if(atoi(response)<0) break;
    fseek(myDB, atoi(response)*sizeof person, SEEK_SET);
    fprintf(stdout,"\nPosition in file before reading it: %ld\n", ftell(myDB));
    fread(&person,sizeof person,1,myDB);
    displayPerson(person);
    fprintf(stdout,"Position in file after reading it: %ld\n\n", ftell(myDB));
    
   }
  fclose(myDB);  
  return 0;
  }

