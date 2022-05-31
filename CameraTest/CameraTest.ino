const int cameraPin = 9;

void setup() {
    Serial.begin(9600);
    //initialize motor pin as an output
    pinMode(cameraPin, OUTPUT);
    turnOnCamera();
}

void loop() {
    //turn on Camera
    Serial.println("Camera Activated");
    turnOnCamera();
    delay(10000);
    //turn off Camera
    Serial.println("Camera Deactivated");
    turnOffCamera();
    delay(5000);
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