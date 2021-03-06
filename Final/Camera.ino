const int cameraPin = 9;

void setupCamera() {
    pinMode(cameraPin, OUTPUT);
    turnOnCamera();
    delay(1000);
    turnOffCamera();
}

void turnOnCamera() {
    digitalWrite(cameraPin, LOW);
    delay(750);
    digitalWrite(cameraPin, HIGH);
}

void turnOffCamera() {
    digitalWrite(cameraPin, LOW);
    delay(250);
    digitalWrite(cameraPin, HIGH);
}