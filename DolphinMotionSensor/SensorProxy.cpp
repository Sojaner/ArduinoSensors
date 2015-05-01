#include "SensorProxy.h"

SensorProxy::SensorProxy()
{
  marg = new LSM9DS0(MODE_I2C, LSM9DS0_G, LSM9DS0_XM);

  inited = marg->begin() == 0x49D4;

  if (inited)
  {
    marg->setAccelScale(marg->A_SCALE_2G);
    marg->setAccelODR(marg->A_ODR_100);
    marg->setAccelABW(marg->A_ABW_50);

    marg->setGyroScale(marg->G_SCALE_245DPS);
    marg->setGyroODR(marg->G_ODR_190_BW_125);

    marg->setMagScale(marg->M_SCALE_2GS);
    marg->setMagODR(marg->M_ODR_125);
  }
}

void SensorProxy::readSensor()
{
  if (inited)
  {
    marg->readAccel();
    ax = marg->calcAccel(marg->ax);
    ay = marg->calcAccel(marg->ay);
    az = marg->calcAccel(marg->az);

    marg->readGyro();
    gx = marg->calcGyro(marg->gx);
    gy = marg->calcGyro(marg->gy);
    gz = marg->calcGyro(marg->gz);

    marg->readMag();
    mx = marg->calcMag(marg->mx);
    my = marg->calcMag(marg->my);
    mz = marg->calcMag(marg->mz);

    marg->readTemp();
    temperature = 21.0f + (float)marg->temperature / 8.0f;
  }
}
