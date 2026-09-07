/* 
Interfacing Flame Sensor with Arduino UNO using Analog input pin of Arduino and 
displaying fire detected on  on I2C LCD. There is one buzzer which turns ON and OFF
when there is fire. There is one averaging filter which checks for false alarm by 
averaging the input counts by www.playwithcircuit.com
*/

#include <LiquidCrystal_I2C.h>  // Library to Run I2C LCD

// Buzzer pin
#define BUZZER_PIN 11
// Minimum counts to detect the flame
#define FLAME_DETECT_COUNTS 300
// define the size of filter array
#define FILTER_SIZE 30

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the analog input pin, for the flame sensor's analog output
const int FlameSensorAnalogPin = A0;

// Variable to store the Analog count from Flame sensor
int FlameCounts;
// Variable to store the Filtered Analog count from Flame sensor
int filteredFlameCounts;

// Analog Value filter
int Filter(int sensorValue);

void setup() {
  // initialize the lcd
  lcd.init();
  // Turn on the Backlight
  lcd.backlight();
  // Clear the display buffer
  lcd.clear();

  // Make buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);

  // Turn Off buzzer pin
  digitalWrite(BUZZER_PIN, LOW);

  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Initializing");

  // Print a message to the LCD
  lcd.setCursor(0, 1);
  lcd.print("Please Wait...");

  // flush out the first 100 values give time to flame sensor counts to be stable
  for (int i = 0; i < 100; i++) {
    // Read the value from the Flame sensor
    FlameCounts = analogRead(FlameSensorAnalogPin);
    // Filter the input counts
    filteredFlameCounts = Filter(FlameCounts);
    delay(10);
  }
  // Clear the display buffer
  lcd.clear();

  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Fire Detected:  ");

  // Print a message to the LCD
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void loop() {
  // Read the value from the Flame sensor
  FlameCounts = analogRead(FlameSensorAnalogPin);

  // Filter the input counts
  filteredFlameCounts = Filter(FlameCounts);

  // if the counts are less than flam detect counts the fire the buzzer
  // for this sensor when the flame the Analog counts decreases
  if (filteredFlameCounts < FLAME_DETECT_COUNTS) {
    lcd.setCursor(0, 1);
    lcd.print("YES");
    digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
    delay(100);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("NO ");
    // Turn Off buzzer pin
    digitalWrite(BUZZER_PIN, LOW);
    // Wait for 10 ms before the next loop
    delay(10);
  }
}

// Averaging filter to filter Analog Values
int Filter(int sensorValue) {
  static int analogArray[FILTER_SIZE] = { 0 };
  unsigned long int filteredValue = 0;
  int i;
  // Shift the Elemnent removing the oldest value stored at index 0
  for (i = 0; i < (FILTER_SIZE - 1); i++) {
    analogArray[i] = analogArray[i + 1];
  }
  // Put the current value in the last element of Array i.e at index FILTER_SIZE-1
  analogArray[FILTER_SIZE - 1] = sensorValue;
  for (i = 0; i < FILTER_SIZE; i++) {
    filteredValue += analogArray[i];
  }
  // Return Filtered Analog Value
  return (filteredValue / FILTER_SIZE);
}
