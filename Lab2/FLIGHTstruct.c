#include <stdio.h>
#include "flight.h"

struct PERSON 
{
   char name[10];
   int age;
   char sex;
};

int main(int argc, char * argv[],char * envp[])
{
  int offset = 0;
  struct PERSON person;
  struct FLIGHT flight;
  struct FLIGHT flights[]={{83,"Air Canada",'Y', 1389800000,"LAX",180,4.233e+5},
                            {214,"Air France",'Y',1389801200,"CDG",314,6.089e+5},
                            {177,"Quantas",0, 1389804400,"LHR",295,5.88e+5}};
  fprintf(stdout,"flightNo:             %d bytes\nOffset at: %d\n",sizeof(flight.flightNo), offset);
  offset += sizeof(flight.flightNo);
  fprintf(stdout,"airline:              %d bytes\nOffset at: %d\n",sizeof(flight.airline), offset);
  offset += sizeof(flight.airline);
  fprintf(stdout,"onTime:               %d bytes\nOffset at: %d\n",sizeof(flight.onTime), offset);
  offset += sizeof(flight.onTime);
  fprintf(stdout,"departureTime:        %d bytes\nOffset at: %d\n",sizeof(flight.departureTime), offset);
  offset += sizeof(flight.departureTime);
  fprintf(stdout,"destination:          %d bytes\nOffset at: %d\n",sizeof(flight.destination), offset);
  offset += sizeof(flight.destination);
  fprintf(stdout,"capacity:             %d bytes\nOffset at: %d\n",sizeof(flight.capacity), offset);
  offset += sizeof(flight.capacity);
  fprintf(stdout,"fuelLevel:            %d bytes\nOffset at: %d\n",sizeof(flight.fuelLevel), offset);
  offset += sizeof(flight.fuelLevel);
  fprintf(stdout,"Total size of FLIGHT: %d bytes\nOffset at: %d\n",sizeof(flight), offset);
  fprintf(stdout,"Total size of PERSON: %d bytes\n",sizeof(person));
  fprintf(stdout,"Array Size:           %d bytes\n",sizeof(person.name));
  
  return 0;
  }

