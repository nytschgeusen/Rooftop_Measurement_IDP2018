#define trigPin 10
#define echoPin 11
#include <dht.h>
#define DHT11_PIN 7
dht DHT;

int led = 13; // the number of the LED pin
int Lswitch = 2; 
int counter = 0;
int currentState = 0;
int previousState = 0;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Lswitch, INPUT);
  pinMode(13, OUTPUT);
}

void loop() 
{
 // Display the temperature and the humidity on the screen 
int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(100);
  
 // calculate the number of people by ultrasonic sensor
 //Declares the variables duration and distance.
  float duration, distance;
  
 // Clears the trigPin // Sends a 2 µs LOW signal to the trigPin to make sure it’s turned off at the beginning of the program loop.
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);

 // Sets the trigPin on HIGH state for 10 micro seconds // Sends a 10 µs HIGH signal to the trigPin to initiate the sequence of eight 40 KHz ultrasonic pulses sent from the transmitting transducer.
 //Defines the duration variable as the length (in µs) of any HIGH input signal detected at the echoPin. The Echo pin output is equal to the time it takes the emitted ultrasonic pulse to travel to the object and back to the sensor.

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Defines the distance variable as the duration (time in d = s x t) multiplied by the speed of sound converted from meters per second to centimeters per µs (0.0344 cm/µs). 

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;

  //If the distance is greater than or equal to 400 cm, or less than or equal to 2 cm, display “Distance = Out of range” on the serial monitor.

    if (distance >= 400 )
  {
    Serial.print("Distance = ");
    Serial.println("Out of range");
    currentState = 1;
  }

  if ( distance <= 50 )
  {
    //If the distance measurement is not out of range, display the distance calculated in line 20 on the serial monitor for 500 ms.
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);
   currentState = 1;
 }       
 else {
 currentState = 0;
 }
 delay(100);
 if(currentState != previousState)
 {
  if(currentState == 1){
 }
 counter = counter + 1;
 Serial.print("Number of people= ");
 Serial.println(counter);
 }
  delay(300);

// Limit switch as counter of people leaving from the room

if (digitalRead(Lswitch) == HIGH)
  {
    currentState = 1;
    delay(50);
  }

else {
 currentState = 0;
 }
 delay(100);
 if(currentState != previousState)
 {
  if(currentState == 1){
 }
 counter = counter - 1;
}
delay (500);
}
