#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "SSID HERE";
const char* password = "PASSWORD HERE";

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(115200);
  initWiFi();

}

void loop() {
  // put your main code here, to run repeatedly:
  // dummy code to show connection strength
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
  delay(300);
}
