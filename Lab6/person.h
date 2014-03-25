/*
   File: person.h
   Course: CENG411
   Author: Leon King,J230,x4200
   Date: Thursday Feb 07, 2008   08:31 AM
*/
#ifndef _person_h
#define  _person_h 
struct PERSON
    { char firstName[10];
      char lastName[10];
      char sex;
      int  age;
      char position[25];
      int recordNo;
     }  ;

void displayPerson(struct PERSON p)
{
  fprintf(stdout,"Record No: %d. Name: %-10s %-10s age: %3d  sex: %c position: %s\n",
            p.recordNo,p.firstName,p.lastName,p.age,p.sex,p.position);
  }

struct PERSON joe={"Joseph","Smith",'M',64,"Computer Engineer",1};
#endif 
