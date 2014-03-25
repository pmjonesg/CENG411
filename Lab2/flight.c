#include <stdio.h>

#include "flight.h"
int main(int argc, char * argv[],char * envp[])
{
  struct FLIGHT flight;
  struct FLIGHT flights[]={{83,"Air Canada",'Y', 1389800000,"LAX",180,4.233e+5},
                            {214,"Air France",'Y',1389801200,"CDG",314,6.089e+5},
                            {177,"Quantas",0, 1389804400,"LHR",295,5.88e+5}};

  displayFlight(0,flights[0]);
  displayFlight(1,flights[1]);
  displayFlight(2,flights[2]); 
  fprintf(stdout,"\n\nEnter a new airline for flight #2: " );
  fflush(stdout);
  fgets(flights[2].airline, 11, stdin);
  fprintf(stdout,"Enter a new airport for flight #2: " );
  fflush(stdout);
  fgets(flights[2].destination, 8, stdin);
  fprintf(stdout,"\n\nModified flight: ");
  displayFlight(2,flights[2]);
  
  FILE * dumpFile=fopen("airline.dump","wb");
  fwrite(flights,sizeof flight,sizeof flights/sizeof flight,dumpFile);
  

  return 0;
  }
