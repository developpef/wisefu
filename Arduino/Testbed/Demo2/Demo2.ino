#define LED_BIG 3
#define LED_LITTLE 4


void setup() {
  pinMode(LED_BIG, OUTPUT);
  pinMode(LED_LITTLE, OUTPUT);
}

void loop() {
  digitalWrite(LED_LITTLE, HIGH);
  delay(2000);
  digitalWrite(LED_BIG, HIGH);
  delay(2000);
  digitalWrite(LED_LITTLE, LOW);
  delay(2000);
  digitalWrite(LED_BIG, LOW);
  delay(2000);
}
