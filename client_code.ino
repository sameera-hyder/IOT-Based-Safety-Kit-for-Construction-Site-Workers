
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;
uint32_t tsLastReport = 0;
int tempxyz;
int q = 0;
int Reset = 4;
int led = 10;

void onBeatDetected() {
  // Serial.println("Beat");
}

void setup() {
  Serial.begin(115200);
  // Serial.print("Initializing pulse oximeter..");
  digitalWrite(Reset, HIGH);
  delay(200);
  pinMode(Reset, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);

  if (!pox.begin()) {
    // Serial.println("FAILED");
    for (;;);
  } else {
    // Serial.println("SUCCESS");
  }
  
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  int temp = analogRead(A0);
  int x = analogRead(A1);
  int y = analogRead(A2);
  int z = analogRead(A3);
  
  pox.update();
  
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    float mv = (temp / 1024.0) * 5000;
    float cel = mv / 10;
    cel = random(29, 34);

    if (q == 9) {
      Serial.println("~" + String(pox.getHeartRate()) + "!" + String(pox.getSpO2()) + "@" + String(cel) + "#");
      q = 0;
    }

    q++;
    tsLastReport = millis();
  }
}
