const int pumpPin = 9; //the number of the motorPin could be changed 

void setup() {
    //initialize motor pin as an output
    pinMode(pumpPin, OUTPUT);
}

void turnOnPump() {
    digitalWrite(pumpPin, HIGH);
}

void turnOffPump() {
    digitalWrite(pumpPin, LOW);
}