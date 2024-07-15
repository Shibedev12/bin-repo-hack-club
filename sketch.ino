#include <LiquidCrystal.h>
// Tells the pi whats up with the lcd.
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// motion sensor pin
const int pirPin = 2;

// speaker pin
const int buzzerPin = 3;

// Variable to store PIR state
int pirState = LOW;

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Arming......");
  delay(2000);

  // Set PIR sensor pin as input
  pinMode(pirPin, INPUT);

  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Attach interrupt to PIR sensor pin
  attachInterrupt(digitalPinToInterrupt(pirPin), motionDetected, RISING);

  // clear screen to say the waiting message
  lcd.clear();
  lcd.print("Armed...");
}

void loop() {
// Animation for "Armed..."
  lcd.clear();
  lcd.print("Armed.");
  delay(300);
  lcd.clear();
  lcd.print("Armed..");
  delay(300);
  lcd.clear();
  lcd.print("Armed...");
  delay(300);}

void motionDetected() {
  // Updates faster than Windows 10
  lcd.clear();
  lcd.print("INTRUDER!!!");

  // Turn on the buzzer
  digitalWrite(buzzerPin, HIGH);

  // Wait for 5 seconds
  delay(5000);

  // Turn off the buzzer
  digitalWrite(buzzerPin, LOW);

  // Clear the LCD and display the monitoring message
  lcd.clear();
  lcd.print("System Armed...");
}
