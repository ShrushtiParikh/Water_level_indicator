const int buzzerPin = 3;
const int floatSensorPin = 8;
unsigned long previousMillis = 0;
const long interval = 1000; // Interval for buzzer on/off in milliseconds
const long buzzerDuration = 60000; // Total duration for buzzer activation in milliseconds
bool buzzerState = false;
bool sensorTriggered = false;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(floatSensorPin, INPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
}

void loop() {
  int sensorState = digitalRead(floatSensorPin);

  Serial.print("Sensor State: ");
  Serial.println(sensorState);

  unsigned long currentMillis = millis();

  if (sensorState == HIGH) {
    Serial.print("---------------------HIGH-----------------------------");
   sensorTriggered = true; // Start tracking time
  } else {
     sensorTriggered = false; // Stop tracking time and turn off buzzer
    Serial.print("LOWWWWWWWWWWWW--------------------------------------------------");
    digitalWrite(buzzerPin, LOW);
  }

 if (sensorTriggered) {
   if (currentMillis - previousMillis >= interval) {
     // Save the last time the buzzer state was toggled
     previousMillis = currentMillis;

     // If the buzzer is off, turn it on, and vice versa
     buzzerState = !buzzerState;
     digitalWrite(buzzerPin, buzzerState ? HIGH : LOW);
   }

   // Turn off buzzer after the duration has passed
   if (currentMillis - previousMillis >= buzzerDuration) {
     digitalWrite(buzzerPin, LOW);
     sensorTriggered = false; // Stop buzzer operation
   }
 }
}
