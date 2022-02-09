// Pin variables
const byte PUMP_PIN = 9;

void setupPump() {
    // Initialize pump pin as an output
    pinMode(PUMP_PIN, OUTPUT);
}

void turnOnPump() {
    digitalWrite(PUMP_PIN, HIGH);
}

void turnOffPump() {
    digitalWrite(PUMP_PIN, LOW);
}