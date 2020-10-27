#include <VL53L1X.h> 
#include <pitches.h>
#include <Wire.h>
VL53L1X sensor_A; //센서 오브젝트 생성
VL53L1X sensor_B; //센서 오브젝트 생성
int startTime = millis(); //타이밍 루프
int mInterval = 100; //리프레시 10hz
 
#define XSHUT_A 9
#define XSHUT_B 10
 
#define M_INTERVAL 50

void setup() {
 
    Serial.begin(115200);
    
    Wire.begin(); // I2C 
    Wire.setClock(400000); // 400khz I2c
 
    // 핀모드를 output으로
    pinMode(XSHUT_A ,OUTPUT);
    pinMode(XSHUT_B ,OUTPUT);

    //모든 tof를 끔
    digitalWrite(XSHUT_A, LOW);
    digitalWrite(XSHUT_B, LOW);
 
    //-----------------------------------------------------------------
    //FIRST WE WILL CONFIGURE AND SETUP SENSOR_A
    //-----------------------------------------------------------------
    delay(50);
    digitalWrite(XSHUT_A, HIGH); //센서 A 켬
    delay(50);
    
    sensor_A.setTimeout(500); //센서 타임아웃 세팅
    
    if (!sensor_A.init())//센서 초기화 try 
    {
        //센서가 시간 내에 응답하지 않음
        Serial.println("Sensor_A is not responding, check your wiring");
    }
    else
    {
        sensor_A.setAddress(42); //센서 I2C 주소 세팅
        sensor_A.setDistanceMode(VL53L1X::Long); //Set the sensor to maximum range of 4 meters
        sensor_A.setMeasurementTimingBudget(40000); //Set its timing budget in microseconds longer timing budgets will give more accurate measurements
        sensor_A.startContinuous(M_INTERVAL); //Sets the interval where a measurement can be requested in milliseconds
    }   
 
    //-----------------------------------------------------------------
    //NOW CONFIGURE AND SETUP SENSOR_B
    //-----------------------------------------------------------------
    delay(50);
    digitalWrite(XSHUT_B, HIGH); //Turn sensor_A on
    delay(50);
    
    sensor_B.setTimeout(500); //Set the sensors timeout
    
    if (!sensor_B.init())//try to initilise the sensor
    {
        //Sensor does not respond within the timeout time
        Serial.println("Sensor_A is not responding, check your wiring");
    }
    else
    {
        sensor_B.setAddress(43); //Set the sensors I2C address
        sensor_B.setDistanceMode(VL53L1X::Long); //Set the sensor to maximum range of 4 meters
        sensor_B.setMeasurementTimingBudget(40000); //Set its timing budget in microseconds longer timing budgets will give more accurate measurements
        sensor_B.startContinuous(M_INTERVAL); //Sets the interval where a measurement can be requested in milliseconds
    }
 
}
 
char buf[40];
 
word M;
int B; //Beat

void loop() {
    //We have to be careful here. If we request a measurement before the measurement has been taken your
    //code will be blovked until the measurement is complete. In order to stop this from happening we
    //must ensure that time between measurement requests is greater than the timing budget and the argument 
    //given in the startContinuous() function. In our case our measurement time must be greater than 50mS.
 
    if((millis()- startTime) > mInterval)
    {
        sprintf(buf, "%4d,%4d",sensor_A.read(),sensor_B.read());
        Serial.println(buf); //Get a reading in millimeters
        startTime = millis();
    }
    
if(sensor_B.read() < 1000 && sensor_B.read() < sensor_A.read()){
  M = NOTE_C3;
  B = 32;
}
if(sensor_B.read() < 1000 && sensor_A.read() < 1000){
  M = NOTE_C4;
  B = 32;
}
if(sensor_A.read() < 1000 && sensor_A.read() < sensor_B.read()){
  M = NOTE_C5;
  B = 32;
}


if(1000 < sensor_B.read() < 2000 && sensor_B.read() < sensor_A.read()){
  M = NOTE_C3;
  B = 16;
}
if(1000 < sensor_B.read() < 2000 && 1000 < sensor_A.read() < 2000){
  M = NOTE_C4;
  B = 16;
}
if(1000 < sensor_A.read() && sensor_A.read() < 2000 && sensor_A.read() < sensor_B.read()){
  M = NOTE_C5;
  B = 16;
}


if(2000 < sensor_B.read() && sensor_B.read() < 3000 && sensor_B.read() < sensor_A.read()){
  M = NOTE_C3;
  B = 8;
}
if(2000 < sensor_B.read() && sensor_B.read() < 3000 && 2000 < sensor_A.read() < 3000){
  M = NOTE_C4;
  B = 8;
}
if(2000 < sensor_A.read() && sensor_A.read() < 3000 && sensor_A.read() < sensor_B.read()){
  M = NOTE_C5;
  B = 8;
}


if(3000 < sensor_B.read() && sensor_B.read() < 3800 && sensor_B.read() < sensor_A.read()){
  M = NOTE_C3;
  B = 4;
}
if(3000 < sensor_B.read() && sensor_B.read() < 3800 && 3000 < sensor_A.read() < 3800){
  M = NOTE_C4;
  B = 4;
}
if(3000 < sensor_A.read() && sensor_A.read() < 3800 && sensor_A.read() < sensor_B.read()){
  M = NOTE_C5;
  B = 4;
}


// iterate over the notes of the melody:
// notes in the melody:
int melody[] = {
  M, 0
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  B, B
};

  for (int thisNote = 0; thisNote < 2; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / B;

    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(8);

}
}
