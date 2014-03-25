/*
   File: stringDemo5.c
   Course: CENG411
   Author: Leon D. King,J230,x4200
   Date: Sunday Jan 13, 2013   22:29 PM
   Purpose: To demonstrate how to write string functions without arrays
   
   If you used this you had an even student #
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Loop until  the string terminator is found
size_t strlen(const char *string)
{
  int count=0;

  while(*string++)  count++;

  return count;
 }

//Loop until there is a difference between the two strings
int strcmp(const char *s1,const char *s2)
{
  int i;
  while(*s1 && *s1==*s2) s1++, s2++;
  return *s1-*s2;
  }

int stricmp(const char *s1,const char *s2)
{
  while(*s1  && toupper(*s1)==toupper(*s2)) s1++, s2++;
  return toupper(*s2)-toupper(*s2);
 }

//Copy s2 after s1 until you reach a terminating null 
char * strcat(char *s1,const char *s2)
{
  char *temp=s1;
  s1+=strlen(s1);
  do 
  {
     *s1++=*s2;
  }
  while(*s2++);
  return  temp;  
 }


char * strdup(const char * s1)
{
   fprintf(stdout,"replaced strdup\n"); 
   char *result=calloc(strlen(s1)+1,1);
   if(result) return strcat(result,s1);
   else perror("Failure to allocate memory in strdup");
   return NULL;
  }


