#include <LiquidCrystal.h>

// Initialize the LCD with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// PIR sensor pin
const int pirPin = 2;

// Buzzer pin
const int buzzerPin = 3;

// Variables for animation
unsigned long previousMillis = 0;
const long interval = 300;
int animationState = 0;

// Variable to store PIR state
volatile bool motionDetectedFlag = false;

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);

  // Set PIR sensor pin as input
  pinMode(pirPin, INPUT);

  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Attach interrupt to PIR sensor pin
  attachInterrupt(digitalPinToInterrupt(pirPin), motionDetected, RISING);
}

void loop() {
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if it's time to update the animation
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Update the animation state
    animationState = (animationState + 1) % 3;

    // Clear the LCD and display the current animation state
    lcd.clear();
    if (animationState == 0) {
      lcd.print("Armed.");
    } else if (animationState == 1) {
      lcd.print("Armed..");
    } else {
      lcd.print("Armed...");
    }
  }

  // Check if motion was detected
  if (motionDetectedFlag) {
    handleMotionDetected();
  }
}

void motionDetected() {
  motionDetectedFlag = true;
}

void handleMotionDetected() {
  // Disable interrupt to avoid multiple triggers
  detachInterrupt(digitalPinToInterrupt(pirPin));

  // Update the LCD display
  lcd.clear();
  lcd.print("INTRUDER!!!");
  

  // Turn on the buzzer
  digitalWrite(buzzerPin, HIGH);

  // Wait for 5 seconds using millis for non-blocking delay
  unsigned long startMillis = millis();
  while (millis() - startMillis < 5000) {
    // You can update the LCD animation here if needed
    // Get the current time
    unsigned long currentMillis = millis();

    // Check if it's time to update the animation
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      // Update the animation state
      animationState = (animationState + 1) % 3;

      // Clear the LCD and display the current animation state
      lcd.clear();
      if (animationState == 0) {
        lcd.print("Armed.");
      } else if (animationState == 1) {
        lcd.print("Armed..");
      } else {
        lcd.print("Armed...");
      }
    }
  }

  // Turn off the buzzer
  digitalWrite(buzzerPin, LOW);

  // Clear the LCD and display the monitoring message
  motionDetectedFlag = false;
  attachInterrupt(digitalPinToInterrupt(pirPin), motionDetected, RISING);
}
