#include <errno.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>

//This struct is composed of all the flags
struct GetFlags
  {
    bool all;
    bool inode;
    bool dereference;
    bool size;
    bool setclassify;
    char * classify;
    char * permissions;
    int minSize;
    bool setminSize;
    int maxSize;
    bool setmaxSize;
    char * time;
    bool decimal;
    bool group;
    bool userid;
    bool author;
    bool hlinks;
  };
//Function prototype for flag implementation
void process_Files(char *file, struct GetFlags flags);

int main(int argc, char * argv[])
{
  struct GetFlags getFlags = {false, false, false, false, false, NULL, NULL, 0, false, 0, false, NULL, false, false, false, false, false};
  struct stat fileInfo;
  DIR * dirp;
  struct dirent *dirent;
   
  char * shortOpt = ":auF:inse:Lx:gP:";
  struct option options[] = {
		{"all", 0, NULL, 'a'},        	//flag -a --all
		{"size", 0, NULL, 's'},			//flag -s --size
		{"classify", 1, NULL, 'F'},		//flag -F --classify
		{"minSize", 1, NULL, 'e'},		//flag --minSize $#
		{"maxSize", 1, NULL, 'x'},		//flag --maxSize $#
	  	{"time", 1, NULL, 't'},			//flag --time (takes 3 arguments)
		{"group", 0, NULL, 'o'},		//flag --group
	   	{"author", 0, NULL, 'h'},		//flag --author
		{NULL, 0, NULL, '\0'}};
 
  int flag;
  int indexVal;

  //This loop sets the flags accordingly
  while((flag = getopt_long(argc,argv,shortOpt, options, &indexVal)) != -1)
  {
    switch(flag)
    {
       	case 'a':
		  getFlags.all = true;
		  break;
       	case 'i':
		  getFlags.inode = true;
		  break;
       	case 'L':
		  getFlags.dereference = true;
		  break;
       	case 's':
		  getFlags.size = true;
		  break;
	case 'g':
		  getFlags.decimal = true;
		  break;
	case 'u':
		  getFlags.userid = true;
		  break;
	case 'n':
		  getFlags.hlinks = true;
		  break;
	case 'h':
		  getFlags.author = true;
		  break;
	case 'o':
		  getFlags.group = true;
		  break;
	case 'F':
	          getFlags.setclassify = true;
		  getFlags.classify = optarg;
                  break;
	case 'e':
                  getFlags.setminSize = true;
		  getFlags.minSize = atoi(optarg);
		  break;
	case 'x':
                  getFlags.setmaxSize = true;
		  getFlags.maxSize = atoi(optarg);
                  break;
	case 't':
		  getFlags.time = optarg;
		  break;
	case 'P':
		  if(strcmp(optarg, "octal") == 0 || strcmp(optarg, "symbolic") == 0)
		  { 
		    getFlags.permissions = optarg;
		    break;
                         }
		  else {
		    getFlags.permissions = "Argument not valid\n";
		    break;
		  }
	case ':':
		  fprintf(stdout, "Missing arguments\n");
     		  break;
	case '?':
		  fprintf(stdout, "Unrecognized command\n");
		  break;
    }
  }
  //Flags test
  //fprintf(stdout, "Flag -a has been set to %s\n", getFlags.all ? "true" : "false");
  //fprintf(stdout, "Flag -i has been set to %s\n", getFlags.inode ? "true" : "false");
  //fprintf(stdout, "Flag -L has been set to %s\n", getFlags.dereference ? "true" : "false");
  //fprintf(stdout, "Flag -s has been set to %s\n", getFlags.size ? "true" : "false");
  //fprintf(stdout, "Flag -g has been set to %s\n", getFlags.decimal ? "true" : "false");
  //fprintf(stdout, "Flag -u has been set to %s\n", getFlags.userid ? "true" : "false");
  //fprintf(stdout, "Flag -n has been set to %s\n", getFlags.hlinks ? "true" : "false");
  //fprintf(stdout, "Flag -h has been set to %s\n", getFlags.author ? "true" : "false");
  //fprintf(stdout, "Flag --group has been set to %s\n", getFlags.group ? "true" : "false");
  
  //fprintf(stdout, "Flag -P has been set to %s\n", getFlags.permissions);
  //fprintf(stdout, "Flag -F has been set to %s\n", getFlags.classify);
  //fprintf(stdout, "Flag --time has been set to %s\n", getFlags.time);
  //fprintf(stdout, "Flag --maxSize has been set to %d\n", getFlags.maxSize);
  //fprintf(stdout, "Flag --minSize has been set to %d\n", getFlags.minSize);
  //fprintf(stdout, "Flag --author has been set to %d\n", getFlags.author);

  dirp = opendir(".");			//This section changes de directory to the current one and reads it
  //this loop executes the functionality of the program, according to flags set
  while(dirent = readdir(dirp))
  {
     process_Files(dirent -> d_name, getFlags);
  }
  fprintf(stdout, "\n");
  closedir(dirp);

  return 0;
}

void process_Files(char *file, struct GetFlags flags)
{
  int count = 0;
  struct stat fileInfo;
  struct dirent *dirent;

  if (lstat(file, &fileInfo) == -1)	//If file cannot be opened then an error message will be displayed
  {
    perror(file);
    exit(1);
  }

  if(flags.all)	//--all flag
  {
    fprintf(stdout, "%s  ", file);
  }

  if(strncmp(file, ".",1) != 0) //Print file if name does not start with .
  {
    if(flags.inode)	//-i flag
    {
      fprintf(stdout, "%ld %s  ", fileInfo.st_ino, file);
      return;
    }
    
    if(flags.dereference)	//-L flag
    {
      if(S_ISREG(fileInfo.st_mode))
        fprintf(stdout, "%s  ", file);
      if(S_ISDIR(fileInfo.st_mode))
        fprintf(stdout, "%s  ", file);
      return;
    }
    
    if(flags.size)	//-s or --s flag
    {
      fprintf(stdout, "%ld %s  ", fileInfo.st_size, file); 
      count++;
    }     

    if(flags.setclassify)	//-F flag
    {
      if(strcmp(file, flags.classify) == 0 || flags.classify == NULL)
      {
        if(S_ISREG(fileInfo.st_mode))
        {
          if(stat(file, &fileInfo) == 0 && fileInfo.st_mode & S_IXUSR)
            fprintf(stdout, "%s*  ", file);
          else if(stat(file, &fileInfo) == 0 && fileInfo.st_mode & S_IRUSR)
            fprintf(stdout, "%s  ", file);
        }
        if(S_ISDIR(fileInfo.st_mode))
           fprintf(stdout, "%s/  ", file);
      }
      return;
    }
    
    if(flags.permissions != NULL)
    {
    if(strcmp("octal", flags.permissions) == 0)    
    {  
      if(count > 0) fprintf(stdout, "\n");

      fprintf(stdout, (S_ISDIR(fileInfo.st_mode)) ? "d" : "-");
      //Display user
      if(fileInfo.st_mode & S_IRUSR && fileInfo.st_mode & S_IWUSR && fileInfo.st_mode & S_IXUSR) fprintf(stdout, "700");
      else if(fileInfo.st_mode & S_IRUSR && fileInfo.st_mode & S_IWUSR) fprintf(stdout, "300");
      else if(fileInfo.st_mode & S_IRUSR && fileInfo.st_mode & S_IXUSR) fprintf(stdout, "500");
      else if(fileInfo.st_mode & S_IWUSR && fileInfo.st_mode & S_IXUSR) fprintf(stdout, "600");
      else if(fileInfo.st_mode & S_IRUSR) fprintf(stdout, "100");
      else if(fileInfo.st_mode & S_IWUSR) fprintf(stdout, "200");
      else if(fileInfo.st_mode & S_IXUSR) fprintf(stdout, "400");
      //Display group
      if(fileInfo.st_mode & S_IRGRP && fileInfo.st_mode & S_IWGRP && fileInfo.st_mode & S_IXGRP) fprintf(stdout, "070");
      else if(fileInfo.st_mode & S_IRGRP && fileInfo.st_mode & S_IWGRP) fprintf(stdout, "030");
      else if(fileInfo.st_mode & S_IRGRP && fileInfo.st_mode & S_IXGRP) fprintf(stdout, "050");
      else if(fileInfo.st_mode & S_IWGRP && fileInfo.st_mode & S_IXGRP) fprintf(stdout, "060");
      else if(fileInfo.st_mode & S_IRGRP) fprintf(stdout, "010");
      else if(fileInfo.st_mode & S_IWGRP) fprintf(stdout, "020");
      else if(fileInfo.st_mode & S_IXGRP) fprintf(stdout, "040");
      //Display others
      if(fileInfo.st_mode & S_IROTH && fileInfo.st_mode & S_IWOTH && fileInfo.st_mode & S_IXOTH) fprintf(stdout, "007");
      else if(fileInfo.st_mode & S_IROTH && fileInfo.st_mode & S_IWOTH) fprintf(stdout, "003");
      else if(fileInfo.st_mode & S_IROTH && fileInfo.st_mode & S_IXOTH) fprintf(stdout, "005");
      else if(fileInfo.st_mode & S_IWOTH && fileInfo.st_mode & S_IXOTH) fprintf(stdout, "006");
      else if(fileInfo.st_mode & S_IROTH) fprintf(stdout, "001");
      else if(fileInfo.st_mode & S_IWOTH) fprintf(stdout, "002");
      else if(fileInfo.st_mode & S_IXOTH) fprintf(stdout, "004");
      fprintf(stdout, "  %s\n", file);
      count++;
    }
   
    if(strcmp("symbolic", flags.permissions) == 0)
    {
      if(count > 0) fprintf(stdout, "\n");

      fprintf(stdout, (S_ISDIR(fileInfo.st_mode)) ? "d" : "-");
      fprintf(stdout, (fileInfo.st_mode & S_IRUSR) ? "r" : "-");
      fprintf(stdout, (fileInfo.st_mode & S_IWUSR) ? "w" : "-");
      fprintf(stdout, (fileInfo.st_mode & S_IXUSR) ? "x" : "-");
      fprintf(stdout, (fileInfo.st_mode & S_IRGRP) ? "r" : "-");
      fprintf(stdout, (fileInfo.st_mode & S_IWGRP) ? "w" : "-");
      fprintf(stdout, (fileInfo.st_mode & S_IXGRP) ? "x" : "-");
      fprintf(stdout, (fileInfo.st_mode & S_IROTH) ? "r" : "-");
      fprintf(stdout, (fileInfo.st_mode & S_IWOTH) ? "w" : "-");
      fprintf(stdout, (fileInfo.st_mode & S_IXOTH) ? "x" : "-");
      fprintf(stdout, "  %s\n", file);
      count++;
    }
    }
    if(flags.setminSize)
    {
      if(fileInfo.st_size <= flags.minSize)
      { 
        fprintf(stdout, "%u %s  ", (unsigned int)fileInfo.st_size, file);
        return;
      } else return;
    }

    if(flags.setmaxSize)
    {
      if(fileInfo.st_size >= flags.maxSize)
      {
        fprintf(stdout, "%u %s  ", (unsigned int)fileInfo.st_size, file);
        count++;
      } else ;
    }    
     
    if (count > 0) return;
    fprintf(stdout, "%s  ", file);
  }
}
