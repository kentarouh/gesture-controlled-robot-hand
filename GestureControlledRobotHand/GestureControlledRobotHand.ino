//Kentarou Howard 2022

#include <Servo.h>

const int sensorNumSamples = 25;
int sampleCount;

//Pins on Arduino
const int servoPins[5] = {3,5,6,9,10};
const int sensorPins[5] = {0,1,2,3,4};

//Servo position min max limits
const int minPositions[5] = {4,6,6,6,6};
const int maxPositions[5] = {140,143,160,146,135};

int sensorValues[5];
int totalSensorValues[5];

Servo thumbServo; 
Servo indexServo; 
Servo middleServo; 
Servo ringServo; 
Servo pinkyServo; 

void setup() {
  //Attach servos to respective pins
  thumbServo.attach(servoPins[0]);
  indexServo.attach(servoPins[1]);
  middleServo.attach(servoPins[2]);
  ringServo.attach(servoPins[3]);
  pinkyServo.attach(servoPins[4]);
}

void loop() {
  if(sampleCount < sensorNumSamples){
    readSensors();
  } else {
    sampleCount = 0;
    averageSensorValues();
    driveServos();
  }
}

int getSensorValue(int pin){
  return analogRead(pin);
}

void readSensors(){
  sampleCount++;

  //Read sensor values from glove
  sensorValues[0] = getSensorValue(sensorPins[0]);
  sensorValues[1] = getSensorValue(sensorPins[1]);
  sensorValues[2] = getSensorValue(sensorPins[2]);
  sensorValues[3] = getSensorValue(sensorPins[3]);
  sensorValues[4] = getSensorValue(sensorPins[4]);

  //Adding values to a total to average later
  totalSensorValues[0] += sensorValues[0];
  totalSensorValues[1] += sensorValues[1];
  totalSensorValues[2] += sensorValues[2];
  totalSensorValues[3] += sensorValues[3];
  totalSensorValues[4] += sensorValues[4];
}

void averageSensorValues(){
  //Averaging total values by number of samples taken to smooth out voltage spikes from sensors
  sensorValues[0] = totalSensorValues[0] / sensorNumSamples;
  sensorValues[1] = totalSensorValues[1] / sensorNumSamples;
  sensorValues[2] = totalSensorValues[2] / sensorNumSamples;
  sensorValues[3] = totalSensorValues[3] / sensorNumSamples;
  sensorValues[4] = totalSensorValues[4] / sensorNumSamples;
}

void driveServos(){
  //Write sensor values mapped to servo limits to servos
  thumbServo.write(map(sensorValues[0], 0, 1023, minPositions[0], maxPositions[0]));
  indexServo.write(map(sensorValues[1], 0, 1023, minPositions[1], maxPositions[1]));
  middleServo.write(map(sensorValues[2], 0, 1023, minPositions[2], maxPositions[2]));
  ringServo.write(map(sensorValues[3], 0, 1023, minPositions[3], maxPositions[3]));
  pinkyServo.write(map(sensorValues[4], 0, 1023, minPositions[4], maxPositions[4]));
}
