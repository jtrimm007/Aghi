#include <dummy.h>

#include <WiFi.h>
#include <MQTT.h>
#include <NTPClient.h>
#include <Arduino_JSON.h>

const char ssid[] = "YOUR WIFI ROUTER ID HERE";
const char pass[] = "YOUR WIFI PASSWORD HERE";

#define clientID "aghiMasterNode"
#define MQTTInstance "aghiv1"
#define MQTTtToken "AghiProject"


const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

//WiFiClient SetUp
WiFiClient net;

//MQTTClient
MQTTClient client;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

unsigned long lastMillis = 0;

void connect() {
  
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  
  Serial.print("\nConnected!...");

  Serial.print("\nconnecting to MQTT Server...");
  while (!client.connect(clientID, MQTTInstance, MQTTtToken)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConnected!");

  client.subscribe("GH");
}

void messageReceived(String &topic, String &payload) {
  Serial.println(topic + ": " + payload);
}

void setup() {
  Serial.begin(115200);

  // start wifi and mqtt
  WiFi.begin(ssid, pass);
  
  // Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(28800);
  
  //client.begin("aghiproject.cloud.shiftr.io", net);
  client.begin("aghiv1.cloud.shiftr.io", net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }
  
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  
  //Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int monthDay = ptm->tm_mday - 1;
  int currentMonth = ptm->tm_mon + 1;
  int currentYear = ptm->tm_year + 1900;
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);

  Serial2.begin(9600, SERIAL_8N1, trigPin, echoPin);
  Serial.println("Waiting: ");
  delay(900);

  char readSensor[10];
  int count = 0; 
  while (Serial2.available()) {
    readSensor[count++] = Serial2.read();
    //Serial.println(char(readSensor));



  }
Serial.println(String(readSensor));
//    Serial.println(timeClient.getFormattedTime());
//    Serial.println(currentDate);

      String input = "{\"Reading\":\"" + String(readSensor) + "\"}";
      Serial.println(input);

    JSONVar myObject = JSON.parse(input);
    client.publish("/GH", JSON.stringify(myObject));

}
