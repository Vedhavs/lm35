const int temperaturePin = A0;
const int ledPin = 13;

const int belowThresholdBlinkInterval = 250; // milliseconds
const int aboveThresholdBlinkInterval = 500; // milliseconds
const int temperatureThreshold = 30; // degrees Celsius

unsigned long previousMillis = 0;
int currentTemperature = 0;
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // Read temperature from the LM35 sensor
  int Temperature_value = analogRead(temperaturePin);
  float voltage = (Temperature_value / 1024.0) * 5.0;
  currentTemperature = (voltage - 0.5) * 100;
  Serial.println(currentTemperature);

  // Check temperature and control LED accordingly
  if (currentTemperature < temperatureThreshold) {
    blinkLED(belowThresholdBlinkInterval);
  } else {
    blinkLED(aboveThresholdBlinkInterval);
  }
}
void blinkLED(int interval) {
  unsigned long currentMillis = millis();
  // Check if the specified interval has passed
  if (currentMillis - previousMillis >= interval) {
    // Save the last time the LED was blinked
    previousMillis = currentMillis;
    // Toggle the LED state
    if (digitalRead(ledPin) == HIGH) {
      digitalWrite(ledPin, LOW);
    } else {
      digitalWrite(ledPin, HIGH);
    }
  }
}
