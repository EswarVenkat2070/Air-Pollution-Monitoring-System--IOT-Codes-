#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>

#include <LiquidCrystal_I2C.h>


#include <ESP8266HTTPClient.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

Set these to run example.
#define FIREBASE_HOST "com.example.myapp"
#define FIREBASE_AUTH "9JY3fy8LbyPDN3ZcXYeVwMbtprERsCABICVKTRF5"
#define WIFI_SSID "Eswar Venkat"
#define WIFI_PASSWORD "venkat02"

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int sensor_pin = A0;
int air;
void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);
  lcd.begin();
  lcd.home();
  //lcd.print("Hello, NodeMCU");
    // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {

  air = analogRead(sensor_pin);
  Serial.print("Air Quality == ");
  Serial.println(air);
  lcd.print(air);
  lcd.clear();
  
  // set value
  Firebase.setFloat("number", air);
  // handle error
  if (Firebase.failed()) {
      //Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // update value
  Firebase.setFloat("number", air);
  // handle error
  if (Firebase.failed()) {
     // Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // get value 
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  delay(1000);

  // remove value
  Firebase.remove("number");
  delay(1000);

  // set string value
  Firebase.setString("message", "Air Quality");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set bool value
  Firebase.setBool("truth", false);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);
}
