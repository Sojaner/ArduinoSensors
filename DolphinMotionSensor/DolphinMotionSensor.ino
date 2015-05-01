#include <SPI.h>
#include <Wire.h>
#include <SFE_LSM9DS0.h>
#include "SensorProxy.h"
#include "MotionDataStructure.h"

SensorProxy* sensor;

void setup() {
  Serial.begin(9600);

  sensor = new SensorProxy();
}

void loop() {

  if (Serial.available() > 0) {

    String command = Serial.readStringUntil('\n');

    if (command == "Hello, Is this Arduino?")
    {
      if (sensor->inited)
      {
        Serial.println("Hi, Yes I'm at your service.");
      }
      else
      {
        Serial.println("Hi, Yes but Sensor didn't get initialized.");
      }
    }
    else if (sensor->inited && command == "Arduino, Motion Sensor's data please.")
    {
      sendMotionSensorData();
    }
  }
}

void sendMotionSensorData()
{
  sensor->readSensor();

  MotionData motionData = {
    floatToLong(sensor->ax),
    floatToLong(sensor->ay),
    floatToLong(sensor->az),
    floatToLong(sensor->mx),
    floatToLong(sensor->my),
    floatToLong(sensor->mz),
    floatToLong(sensor->gx),
    floatToLong(sensor->gy),
    floatToLong(sensor->gz),
    floatToLong(sensor->temperature)
  };
  
  writeDataToSerial(motionData);
}

void writeDataToSerial(MotionData motionData)
{
  short dataLength = sizeof(motionData);

  byte *lengthBytes = (byte *) &dataLength;

  Serial.write(lengthBytes, sizeof(lengthBytes));

  byte *data = (byte *) &motionData;

  Serial.write(data, dataLength);
}

long floatToLong(float value)
{
  byte data[sizeof(float)];

  float f = value;

  memcpy(data, &f, sizeof(f));

  long l;

  memcpy(&l, data, sizeof(l));

  return l;
}
