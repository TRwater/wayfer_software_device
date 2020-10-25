#include <Wire.h>
#include <VL53L1X.h>
#include <SoftwareSerial.h>
#define BT_RXD 8
#define BT_TXD 7

SoftwareSerial BtSerial(BT_RXD, BT_TXD);

VL53L1X sensor;

unsigned long time_previous, time_current;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  sensor.setTimeout(500);
  BtSerial.begin(115200);
  time_previous = millis();
 
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);
}

void loop()
{
  time_current = millis();
  double cm = sensor.read();
 
  Serial.print(sensor.read());

  if(time_current - time_previous >= 1000){
     BtSerial.print(cm);
     BtSerial.println();
     }
}
