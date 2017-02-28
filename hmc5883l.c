#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "hmc5883l.h"



void checkFD(int fd, char *text)
{
    if (fd < 0) {
        printf("Error: %s - %d\n", text, fd);
        exit(-1);
    }
}


//mag is a structure defined in 'hmc5883l.h' 
int initialize_compass(struct mag *obj)
{
    obj->fd = wiringPiI2CSetup(HMC5883L_ADDRESS);
    checkFD(obj->fd, "wiringPiI2CSetup");
    wiringPiI2CWriteReg8(obj->fd, HMC5883L_REG_MODE, HMC5883L_MODE_CONTINUOUS);
}

/*
This was something new that I did a year ago.
Reading from a sensor register using wiringPII2C library.
HMC5883l has 8bit read and write address and 8 bit locations.
Therefore we use wiringPiI2CReadReg8() function.
The register mappings is defined as macros in 'hmc5883l.h'
*/
double heading_compass(struct mag *obj)
{
    //reading from register 0x03 which stores X axis MSB
    obj->msb = wiringPiI2CReadReg8(obj->fd, HMC5883L_REG_MSB_X);
    
    //reading from register 0x03 which stores X axis LSB
    obj->lsb = wiringPiI2CReadReg8(obj->fd, HMC5883L_REG_LSB_X);
    
    //Leftshift 8 MSB and Bitwise OR wtith LSB
    //Basically, cncatinating LSB to MSB 
    obj->x = obj->msb << 8 | obj->lsb;

    obj->msb = wiringPiI2CReadReg8(obj->fd, HMC5883L_REG_MSB_Y);
    obj->lsb = wiringPiI2CReadReg8(obj->fd, HMC5883L_REG_LSB_Y);
    obj->y = obj->msb << 8 | obj->lsb;
    
    /*
    // not required for calculation.
    obj->msb = wiringPiI2CReadReg8(obj->fd, HMC5883L_REG_MSB_Z);
    obj->lsb = wiringPiI2CReadReg8(obj->fd, HMC5883L_REG_LSB_Z);
    obj->z = obj->msb << 8 | obj->lsb;
    */
    
    //Calculate heading in radians.
    obj->heading = atan2((double)obj->y, (double)obj->x);

    /*if the calculated heading is less than 0, then map it from 	0 to 360. i.e. simply add 180 to the negative heading.
    */
    if(obj->heading<0)
        obj->heading +=2*PI; 


    //convert into degrees.
    obj->heading=obj->heading*(180/PI);

    return obj->heading;
}


/*This function can be called whever you need to ping the compass.
*/
double getCurrentHeading(HMC5883L compass)
{
    compass = (struct mag *) malloc(sizeof(struct mag));
    compass->compassInit=initialize_compass;
    compass->compassHeading=heading_compass;
    compass->compassInit(compass);
    double heading = compass->compassHeading(compass);
    free(compass);
    return heading;
}
