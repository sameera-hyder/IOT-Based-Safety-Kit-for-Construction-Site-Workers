
#include <SoftwareSerial.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Wire.h>

#define Addr 0x53
int pin = 2;
const uint8_t scl = 14; // D5
const uint8_t sda = 12; // D6
float xAccl, yAccl, zAccl;
#define FIREBASE_HOST "project-c3a35-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Tnf476oGSBRXZKmfpIZtSGLmDoLvnMVmH5opOTEb"
#define WIFI_SSID "iotkit"
#define WIFI_PASSWORD "123456789"
FirebaseData firebaseData;
SoftwareSerial BTSerial(5, 4);

void setup(void) {
  Serial.begin(115200);
  Wire.begin(sda, scl);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.println("----------Begin Set Test -----------");
}

void handleRoot() {
  unsigned int data[6];
  Wire.beginTransmission(Addr);
  // Other I2C related code...
  // Convert the data to 10-bits
  int xAccl = (((data[1] & 0x03) * 256) + data[0]);
  // Other conversion code...
  Serial.print("Acceleration in X-Axis : ");
  Serial.println(xAccl);
  // Other printing and condition code...
}

void loop(void) {
  handleRoot();
  // Other Bluetooth and Firebase related code...
}

void bluetooth() {
  // Bluetooth initialization and commands...
}
