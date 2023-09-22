
// Buzzer
int RelayPin = 4;

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
      
  // Relay
  pinMode(RelayPin, OUTPUT);
}

void loop(){ 
   read_distance();
}

void read_distance()
{
  distance = sonar.ping_cm();
  Serial.println(distance);
  delay(50);                    // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  if (distance < 10)
  {
  digitalWrite(RelayPin, HIGH);
  delay(500);
  }

  else
  {
   digitalWrite(RelayPin, LOW);
  }
}
