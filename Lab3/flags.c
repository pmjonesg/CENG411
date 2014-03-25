#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	int flag, flag_used = 0, total_arguments = 0, arguments = 0;
	
	struct FLAGS
	{
	     char * number;		//-n flag
	     char * file;		//-f flag
	     bool suppress;	//-R flag
	     bool hostname;	//-a flag
	     bool nlocal;	//-d flag
	     bool udomain;	//-w flag
	} getflags = {NULL, NULL, false, false, false, false}; //Set defaults

	char * shortOptions = ":Rawf:dn:";
	struct option options[] = {
	     {"num", 1, NULL, 'n'},
	     {"file", 1, NULL, 'f'},
	     {"suppress", 0, NULL, 'R'},
	     {"hostname", 0, NULL, 'a'},
	     {"non-local", 0, NULL, 'd'},
	     {"domain", 0, NULL, 'w'},
	     {NULL, 0, NULL, '\0'}};
	int indexVal;	

	while((flag=getopt_long(argc,argv,shortOptions,options,&indexVal)) != -1)
	{
		switch(flag)
		{
			case 'n':
				flags.number = optarg;
				flag_used++;
				if(argv[0] != '\0') arguments++;
				break;
			case 'f':
				flags.file = strdup(optarg);
				if(argv[0] != '\0') arguments++;
				flag_used++;
				break;	
			case 'R':
				flags.suppress = true;
				flag_used++;
				break;
			case 'a':
				flags.hostname = true;
				flag_used++;
				break;
			case 'd':
				flags.nlocal = true;
				flag_used++;
				break;
			case 'w':
				flags.udomain = true;
				flag_used++;
				break;
			case ':':
				fprintf(stderr, "Missing command line argument for flag %c\n", optopt);
			//	fprintf(stdout, "Optopt: %c\nOpterr: %c\nOptarg: %c\n", optopt, opterr, optarg);
				break;
			case '?':
				fprintf(stderr, "Invalid flag: %c\n", optopt);
			//	fprintf(stdout, "Optopt: %c\nOpterr: %c\nOptarg: %c\n", optopt, opterr, optarg);
				break;
		}
	}

	//Verification - necessary for testing the getopt loop
        fprintf(stdout,"The flag -n is set to: %s\n", flags.number);
        fprintf(stdout,"The flag -f is set to: %s\n", flags.file);
        fprintf(stdout,"The flag -R is set to: %s\n", flags.suppress ? "true" : "false");
        fprintf(stdout,"The flag -a is set to: %s\n", flags.hostname ? "true" : "false");
        fprintf(stdout,"The flag -d is set to: %s\n", flags.nlocal ? "true" : "false");
        fprintf(stdout,"The flag -w is set to: %s\n", flags.udomain ? "true" : "false");
	
	int i;
	for(i = 1; i<argc; i++) {
	   fputs(argv[i], stdout);
           if (i<argc-1) putchar(' '); 
	   total_arguments++;
	}

	fprintf(stdout, "\nThere are %d non-flag arguments", (total_arguments - flag_used - arguments));
	fprintf(stdout, "\n");	
	return 0;
}
