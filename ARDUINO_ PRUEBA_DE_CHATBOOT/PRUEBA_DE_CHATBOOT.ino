int Boton = 13;
int Led = 33;

void setup() {
  Serial.begin(9600);
  pinMode(Boton, INPUT);
  pinMode(Led, OUTPUT);
}

void loop() {
  if (digitalRead(Boton) == 0) {
    Serial.println("H");
    delay(500);
  }

  if (Serial.available()) {
    char Letra = Serial.read();
    if (Letra == 'H') {
      digitalWrite(Led, HIGH);
    }
    else if (Letra == 'L') {
      digitalWrite(Led, LOW);
    }
  }
}
