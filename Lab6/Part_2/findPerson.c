/*
ourse: CENG411
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

						void findPerson(long cursor)
{
				  struct PERSON person;

						  FILE *myDB=fopen("myDB","r");
																										    fseek(myDB, cursor, SEEK_SET);
																												    fprintf(stdout,"\nPosition in file before reading it: %ld\n", ftell(myDB));
																														    fread(&person,sizeof person,1,myDB);
																																    displayPerson(person);
																																		    fprintf(stdout,"Position in file after reading it: %ld\n\n", ftell(myDB));
																																				    
									  fclose(myDB);  
											  }
