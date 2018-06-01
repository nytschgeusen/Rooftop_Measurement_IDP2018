// defines pins numbers
const int trigPin = 2; // ESP32-DevKit (Geekworm Easy Kit ESP32)
const int echoPin = 5; // ESP32-DevKit (Geekworm Easy Kit ESP32)
const int LEDpin = 3; // pin to connect LED

// defines variables
long tempAir = 30.0; // Air temperature in degree Celsius
long vAir; // sonic speed in m/s
long duration; // sound wave travel time in microseconds
int distance;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH); //

// Calculating the distance
vAir = 331.5 + (0.6 * tempAir); // in m/s
distance = duration / 1e4 * vAir/2.0;

// Prints the distance on the Serial Monitor
Serial.print("Distance in cm: ");
Serial.println(distance);
delayMicroseconds(250000);
}
