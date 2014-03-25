#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct FLAGS
   {
     char * num;		//-n flag
     char * file;		//-f flag
     bool suppress;	//-R flag
     bool hostname;	//-a flag
     bool nlocal;	//-d flag
     bool udomain;	//-w flag
     };

int main(int argc, char * argv[], char * envp[])
{
	struct FLAGS flags = {" ", " ", false, false, false, false}; //Set defaults

	int flag, flag_used = 0, total_arguments = 0, arguments = 0;
	
	while((flag = getopt(argc, argv, "Rawdn:f:")) != -1)

	{
	//	fprintf(stdout,"Processing cmd line arg #%d with flag %c.\n", optind - 1, flag);
		switch(flag)
		{
			case 'n':
				flags.num = strdup(optarg);
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
			default:
				perror("Bad flag!");
				fprintf(stderr,"flag: %c opterr: %d optopt %c\n", flag, opterr, optopt);
		}
	}

	//Verification - necessary for testing the getopt loop
        fprintf(stdout,"The flag -n is set to: %s\n", flags.num);
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
