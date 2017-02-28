#include <unistd.h>
#include <stdint.h>

//refer HMC5883L Datasheet for Register Mapping

#define HMC5883L_ADDRESS (0x1e)

#define HCM5883L_REG_CONFIG_A (0x00)
#define HCM5883L_REG_CONFIG_B (0x01)
#define HMC5883L_REG_MODE     (0x02)
#define HMC5883L_REG_MSB_X    (0x03)
#define HMC5883L_REG_LSB_X    (0x04)
#define HMC5883L_REG_MSB_Z    (0x05)
#define HMC5883L_REG_LSB_Z    (0x06)
#define HMC5883L_REG_MSB_Y    (0x07)
#define HMC5883L_REG_LSB_Y    (0x08)
#define HMC5883L_REG_STATUS   (0x09)
#define HMC5883L_REG_ID_A     (0x0a)
#define HMC5883L_REG_ID_B     (0x0b)
#define HMC5883L_REG_ID_C     (0x0c)

#define HMC5883L_MODE_CONTINUOUS (0x00)
#define HMC5883L_MODE_SINGLE     (0x01)


#define PI 3.14159265


typedef struct mag* HMC5883L;
typedef double (*getHeading)(struct mag *);
typedef int (*initialize)(struct mag *);
double getCurrentHeading(struct mag *);

//define struture for magnetometer data
struct mag
{
    double heading;
    uint8_t msb,lsb;
    short x,y,z;
    int fd;
    getHeading compassHeading;
    initialize compassInit;
};



void checkFD(int, char*);
int initialize_compass(struct mag*);
double heading_compass(struct mag*);
double getCurrentHeading(HMC5883L);













