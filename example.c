#include <errno.h>
#include <stdio.h>
#include "R2hmc5883l.h"

HMC5883L compass; //HMC5883l object
double heading_d;
char heading[20];

int main ()
{
	if (wiringPiSetup () == -1)
	{
		fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
		return 1 ;
	}

      heading_d = getCurrentHeading(compass); //get compass heading

	return 0 ;
}

