/* 
Interfacing Flame Sensor with Arduino UNO using Digital input pin of Arduino and 
displaying fire detected on  on I2C LCD. There is one buzzer which turns ON and OFF
when there is fire. There is one averaging filter which checks for false alarm by 
averaging the input counts by www.playwithcircuit.com
*/

#include <LiquidCrystal_I2C.h>  // Library to Run I2C LCD

// Buzzer pin
#define BUZZER_PIN 11
// define the size of filter array
#define FILTER_SIZE 30

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the digital input pin, for the flame sensor's digital output
const int FlameSensorDigitalPin = 10;


void setup() {
  // initialize the lcd
  lcd.init();
  // Turn on the Backlight
  lcd.backlight();
  // Clear the display buffer
  lcd.clear();


  // Make digital pin of Sensor as Input
  pinMode(FlameSensorDigitalPin, INPUT);

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

  // delay to mate flame sensor stable
  delay(1000);

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

  // when the Digital pin turn HIGH then it means flame is present
  if (checkFlameSensor() == HIGH) {
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

// this function checks flame sensor two time to check if flame is really detected or not
bool checkFlameSensor() {
  if (digitalRead(FlameSensorDigitalPin) == HIGH) {
    // wait for 20 ms to check for signal debouncing
    delay(20);
    if (digitalRead(FlameSensorDigitalPin) == HIGH) {
      return HIGH;
    } else {
      return LOW;
    }
  } else {
    return LOW;
  }
}
