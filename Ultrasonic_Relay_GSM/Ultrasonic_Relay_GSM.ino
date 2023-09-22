//-------For GSM-----------------
#include <SoftwareSerial.h>
SoftwareSerial SIM900A(10,11);

// Buzzer
int RelayPin = 4;

//--------For Ultrasonic----------
#include <NewPing.h>

//Define Ultrasonic pin
#define trigPin 2
#define echoPin 3
#define stop_distance 200

// Danger Water Level
#define MIN_DISTANCE 5  // Minimum distance in centimeters
#define MAX_DISTANCE 25  // Maximum distance in centimeters

unsigned long eventInterval = 1000;
unsigned long previousTime1 = 0;
unsigned long previousTime2 = 0;

NewPing sonar(trigPin, echoPin, stop_distance);
int distance;
long duration;

void setup(void)
{
  // Setting the baud rate of GSM Module  
  SIM900A.begin(9600);   
  
  // Start serial communication for debugging purposes
  Serial.begin(9600);
      
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

  if (distance == 0){
    digitalWrite(RelayPin, LOW);
    Serial.println("No Echo received");
    }
  else if (distance >=MIN_DISTANCE && distance <= MAX_DISTANCE){
    Serial.println("Alert: Maximum Distance Exceeded!");
    digitalWrite(RelayPin, HIGH);
    SendMessage();
    delay(500);
    }

  else
  {
   digitalWrite(RelayPin, LOW);
  }
}

 void SendMessage()
{
  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+60193609872\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println("EMERGENCY ALERT:Dangerous water levels detected in your area. Please evacuate to higher ground NOW. Your safety is our priority. Keep your loved ones informed");// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent ->SMS Sent");
}
