#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * reverse(char *s);

int main(int argc, char * argv[])
{
   char myString[] = {"This is a string"};
   fprintf(stdout, "%s\n", reverse(myString));	
   fprintf(stdout, "%s\n", myString);

   return 0;
}


char * reverse(char *s)
{
  char *begin;
  begin = malloc((1 * sizeof(s)) + 1);
  char *str = s;
  while(*str != '\0')
  {
  *begin = *str++;
  begin++;
  }
  begin = begin - strlen(s);
  char *end = begin + strlen(begin) - 1;
  
  while(end > begin)
  {
     char temp = *end;
     *end-- = *begin;
     *begin++  = temp;
  } 
  begin = begin - (strlen(s)/2);
  return begin;
}
