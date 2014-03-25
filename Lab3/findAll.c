#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findAll(char *string, char *letter);

int main(int argc, char * argv[])
{
  int n = findAll("Once upon in your mom", "o"); 
  fprintf(stdout, "Repeated %d time(s)\n", n);

  return 0;
}

int findAll(char *string, char *letter)
{ 
  
  int *locations = (int *)malloc(4 *sizeof(strlen(string)));
  int times = 0, count = 0;

  while(*string)
  { 
    if(*string == *letter || *string == *letter + 32 || *string == *letter - 32)
    {  
      ++times;
      *locations = count;
      locations++; 
    }
    count++;
    string++;
  }
  int *initp = locations = locations - times;
  for(locations; locations <= initp + times - 1; locations++)
  	fprintf(stdout, "%d\n", *locations);

  return times;
}
