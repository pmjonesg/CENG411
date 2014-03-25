#include <string.h>   
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>  //Added in C99


const char *progName;
//external variables related to getopt
//These are declared for us in getopt.h - we don't have to declare them
extern char * optarg;   //string.  Argument of the flag
extern int optind;      //index in argv[] of the next entry to parse
extern int optopt;      //If getopt returns '?' (invalid option) or ':'
extern int opterr;
//(missing argument) then optopt is the flag

int main(int argc,char * argv[])
{
    //A bundle of variables to remember the flags on the
    //command line
    struct Flags
    {
      bool suppress;
      bool hostname;
      char * num;
      bool nlocal;
      char * file;
      bool  udomain;
     } getOptFlags = {false,false,NULL,false,NULL,false};

    char * shortOptions=":Rn:dwf:"; 
    struct option  options[]= { //{flag,has_arg,ignore,returnCode} 
                       {"suppress", 0, NULL, 'R'}, 
                       {"num", 1, NULL, 'n'}, 
                       {"nlocal",0,NULL,'d'},
                       {"file",1,NULL,'f'},
                       {"udomain",0,NULL,'w'},
                        {NULL,0,NULL,'\0' }};

    //Use these variables to record the command line options
    int flag;
    int indexVal;
    int i,last=1;

	while( (flag=getopt_long(argc,argv,shortOptions,options,&indexVal))!=-1)
	{
	    fprintf(stdout,"flag: %c   Argument: %s Position: %d OptOpt: %c\n",
		    flag, optarg, optind, optopt);
	} 

	while( (flag=getopt_long(argc,argv,shortOptions,options,&indexVal))!=-1)
	{
            last=optind;
	    switch(flag)
	    {
		case 'd':  
			   getOptFlags.nlocal=true;
			   break;

		case 'R':  
                           getOptFlags.suppress=true;
			   break;

		case 'w':  //Convert optarg from string to int
                           getOptFlags.udomain=true;
			   break;

		case 'n': 
			   //getOptFlags.inFileName=strcpy(malloc(strlen(optarg)+1),optarg);
			   getOptFlags.num=optarg;
			   break;
		case 'f':  
			   getOptFlags.file=strcpy(malloc(strlen(optarg)+1),optarg);
			   break;
		
		case 'a':
			   getOptFlags.hostname = true;
			   break;
		case '?':  fprintf(stderr,"CENG411: Invalid Flag: %c\n", optopt);
			   break;

		case ':':   fprintf(stderr,"CENG411: Missing command line argument for flag %c\n",optopt);
			    break;

	    }
	}

    //Having parsed the flags, demonstrate that we remember them
    fprintf(stdout,"\n\nProgram Summary: ");
    if(getOptFlags.suppress)
               fprintf(stdout,"-R or --help flag was processed\n");

    if(getOptFlags.nlocal) 
               fprintf(stdout,"-d or --release flag was processed\n");

    if(getOptFlags.num) fprintf(stdout,"input file %s specified\n",
                       getOptFlags.num);

    if(getOptFlags.file)
            fprintf(stdout,"email request to %s specified\n",
                       getOptFlags.file);

    if(getOptFlags.udomain) 
          fprintf(stdout,"-w has been set\n");

    fprintf(stdout,"\n\nThe remaining command line args are: \n");
    for(i=optind;i<argc;i++)
        fprintf(stdout,"argv[%d] is %s\n",i,argv[i]);


    return 0;
}

