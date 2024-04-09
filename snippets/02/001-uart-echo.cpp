String receivingBufFromConsole; // Global variant，which is used in storing our input
void setup() {
  Serial.begin(115200);
  Serial.println("Program SetUp Success");
}

void loop() {
  if(Serial.available()) {
      receivingBufFromConsole = Serial.readString();
      Serial.println("I received the String from Console:> ");
      Serial.println(receivingBufFromConsole);
      Serial.println("Waiting for your next String...");
  } else {
    delay(100);
  }
}