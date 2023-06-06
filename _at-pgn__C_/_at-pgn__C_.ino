#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include <HttpClient.h>
#include <WiFi.h>
#include <Bridge.h>
#include <ArduinoHttpClient.h>
#include <BridgeHttpClient.h>
#include "config/configuration.h"
const int trigPin = 9;
const int echoPin = 8;
const int buzzerPin = 3;
long duration;
int distance;
Servo myServo;
BridgeHttpClient client;
String token = "45e04c0f-07d8-48ab-9386-b0af81bab9c3" //token à envoyer à l'api pour s'authentifier
const char* serverIP = "127.0.0.1"
const char* port = "2000"
const char* endpoint = "/distance/datas"
void setup() {
  WiFi.begin(ssid, password); //déjà importées
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(7);
  pinMode(buzzerPin, OUTPUT); // Définit le buzzerPin comme une sortie
  Bridge.begin();
  SerialUSB.begin(9600)
  while(!SerialUSB);
  client.addHeader("Content-Type: application/json");
  client.enableInsecure();
}

void loop() {
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(0);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(",");

    if (distance <= 100) { // Condition pour une distance inférieure à 1 mètre
      tone(buzzerPin, 500, 400); // Active le buzzer
      makePostRequest(distance);
    }
  }

  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(0);
    distance = calculateDistance();

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(",");

    if (distance <= 100) { // Condition pour une distance inférieure à 1 mètre
      tone(buzzerPin, 500, 400); // Active le buzzer
      makePostRequest(distance);
    }
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Calcul de la distance en centimètres
  return distance;
}
void makePostRequest(int datadistance) {
  String response;
  client.get("https://www.timeapi.io/api/Time/current/zone?timeZone=Europe/Amsterdam");
  String url = "http://127.0.0.1:2000/distance/datas";
  String data = "{\"distance\":\"";
  data+=datadistance;
  data +="\"}";
  data += "\",\"hour\":\"";
  data += response;
  data +="\",\"token\":\"";
  data += token
  data += "\"}";
  client.post(url, data);
}
