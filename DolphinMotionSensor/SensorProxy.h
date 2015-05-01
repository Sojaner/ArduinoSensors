#include <SFE_LSM9DS0.h>
#include "Arduino.h"

#define LSM9DS0_XM  0x1D
#define LSM9DS0_G   0x6B

class SensorProxy
{
  public:
    SensorProxy();
    float ax, ay, az, gx, gy, gz, mx, my, mz, temperature;
    bool inited;
    void readSensor();

  private:
    LSM9DS0* initializeMarg();

    LSM9DS0* marg;
};
