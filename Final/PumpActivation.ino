// Pin Definitions:
const byte PUMP_PIN = 9;

void setup() {
    //initialize motor pin as an output
    pinMode(PUMP_PIN, OUTPUT);
}

void turnOnPump() {
    digitalWrite(PUMP_PIN, HIGH);
}

void turnOffPump() {
    digitalWrite(PUMP_PIN, LOW);
}