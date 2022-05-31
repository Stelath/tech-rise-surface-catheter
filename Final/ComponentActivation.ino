// Pin variables
const byte PUMP_PIN = 12;
const byte EXPULSION_PIN = 11;
const byte CAMERA_LIGHT_PIN = 10;

void setupComponents() {
    // Initialize pump pin as an output
    pinMode(PUMP_PIN, OUTPUT);
    pinMode(EXPULSION_PIN, OUTPUT);
    pinMode(CAMERA_LIGHT_PIN, OUTPUT);
}

void turnOnPump() {
    digitalWrite(PUMP_PIN, HIGH);
}

void turnOffPump() {
    digitalWrite(PUMP_PIN, LOW);
}

void turnOnCameraLight() {
    digitalWrite(CAMERA_LIGHT_PIN, HIGH);
}

void turnOffCameraLight() {
    digitalWrite(CAMERA_LIGHT_PIN, LOW);
}

void turnOnExpulsion() {
    digitalWrite(EXPULSION_PIN, HIGH);
}

void turnOffExpulsion() {
    digitalWrite(EXPULSION_PIN, LOW);
}