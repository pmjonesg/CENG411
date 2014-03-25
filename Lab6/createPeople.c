/*
   File: createPeople.c
   Course: CENG411
   Author: Leon King,J230,x4200
   Date: Monday January 29, 2007
   */

#include <stdio.h>
#include <stdlib.h> //For the rand() function
#include <time.h>
#include <string.h>
#include "person.h"

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

//Function using random numbers to generate a person
void makePerson(struct PERSON *p)
{
  strcpy(p->firstName,names[rand()%sizeof(names)/sizeof(names[0])]);
  strcpy(p->lastName,lastNames[rand()%sizeof(lastNames)/sizeof(lastNames[0])]);
  strcpy(p->position,role[rand()%sizeof(role)/sizeof(role[0])]);
  p->age =  rand()%106;
  p->sex = (rand()%2) ? 'M' : 'F';
  }


int main(int argc, char * argv[])
{
  struct PERSON sample;
  long recSize, recNo,nRecords;
  int i;

  if(argc<2) {fprintf(stdout,"Usage:  createPeople nPeople mode\n");
               exit(1); }

  FILE *mydb=fopen("myDB",argc>2 ? argv[2] : "w"); 
  
  srand(time(NULL));
  fprintf(stdout,"Usage:  %s  nRecords fileMode\n",argv[0]);
  fprintf(stdout,"Each record will be %d bytes\n",sizeof(sample));
  
  if(!mydb) { perror("Failure to open myDB"); exit(1);}
 
  //Determine how many records to create
  if(argc==1) nRecords=10;
    else nRecords=atoi(argv[1]);

  fprintf(stdout,"Creating a database of %ld entries\n",nRecords);
  for(i=0;i<nRecords;i++)
  {
     makePerson(&sample);
     sample.recordNo=i;
     displayPerson(sample);
     //fprintf(stdout,"%s,%s,%d,%c,%s\n", sample.firstName, 
     //      sample.lastName,sample.age,sample.sex,sample.position);
     fwrite(&sample, sizeof(sample),1, mydb);
    }
  fclose(mydb);
  return 0;
}
