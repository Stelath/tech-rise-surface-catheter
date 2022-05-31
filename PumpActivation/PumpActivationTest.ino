const int pumpPin = 10; //the number of the motorPin could be changed 

void setup() {
    Serial.begin(9600);
    //initialize motor pin as an output
    pinMode(pumpPin, OUTPUT);
}

void loop() {
    //turn on pump
    Serial.println("Pump Activated");
    turnOnPump();
    delay(1500);
    //turn off pump
    Serial.println("Pump Deactivated");
    turnOffPump();
    delay(1500);
}

void turnOnPump() {
    digitalWrite(pumpPin, HIGH);
}

void turnOffPump() {
    digitalWrite(pumpPin, LOW);
}