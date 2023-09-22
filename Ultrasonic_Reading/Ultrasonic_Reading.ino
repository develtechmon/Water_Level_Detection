
// Buzzer
#define buzzer 6

//--------For Ultrasonic----------
#include <NewPing.h>

//Define Ultrasonic pin
#define trigPin 2
#define echoPin 3
#define stop_distance 200

unsigned long eventInterval = 1000;
unsigned long previousTime1 = 0;
unsigned long previousTime2 = 0;

NewPing sonar(trigPin, echoPin, stop_distance);
int distance;
long duration;

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(115200);
      
  // Buzzer
  pinMode(buzzer, OUTPUT);
}

void loop(void){ 
   read_distance();
}

void read_distance()
{
  distance = sonar.ping_cm();
  Serial.println(distance);
//  if (distance < 10)
//  {
//  digitalWrite(buzzer, HIGH);
//  delay(500);
//  digitalWrite(buzzer, LOW);
//  delay(200);
//  }
}
