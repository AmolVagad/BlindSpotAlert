#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
//Define constants
// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);
const int trigPin = 12;
const int echoPin = 11;

//Define variables
long duration;
double distance;

//Declare functions
void DisplaySafe();
void DisplayAlert();

void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.setFont(&FreeSansBold9pt7b);
}

void loop() 
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.00034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delayMicroseconds(10);
  //Alert if object is very close (Distance of 0.5 metres is considered to be a warning distance here)

  if (distance <= 0.5)  
  {
    DisplayAlert();
    Serial.print("Object in Blind Spot");
    
  }
  else
  {
    DisplaySafe();
    Serial.print("SAFE");
  }  
}



//Function to Display Warning
void DisplayAlert()
{
  display.clearDisplay();
  display.display();
  // display a line of text
  display.setTextSize(1.95);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.print("ALERT!");

  // update display with all of the above graphics
  display.display();
    
}


//Function to display Safe Conditions 
void DisplaySafe()
{
  display.clearDisplay();
  // display a line of text
  display.setTextSize(2.8);
  display.setTextColor(WHITE);
  display.setCursor(0,30);
  display.print("SAFE");

  // update display with all of the above graphics
  display.display();
    
}
