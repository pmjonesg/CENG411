/*
   File: flight.h
   Course: CENG411
   Author: Leon King,J230,x4200
   Date: Monday Jan 02, 2012   12:32 PM
   Purpose: declares the data type FLIGHT
*/
 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

struct FLIGHT
{
    short flightNo;
    char  airline[11];
    bool  onTime;
    time_t  departureTime;
    char  destination[7];
    int   capacity;
    double fuelLevel;
};

void displayFlight(int recordNo,struct FLIGHT departure)
{
  fprintf(stdout,"recordNo: %d Flight No: %d. Airline: %-10s onTime: %c "
                 "leaving: %s     destination: %s passengers: %d fuel: %g\n",
             recordNo, departure.flightNo, departure.airline, departure.onTime ? 'Y' : 'N',
             ctime(&departure.departureTime),
             departure.destination,departure.capacity,departure.fuelLevel);
}
