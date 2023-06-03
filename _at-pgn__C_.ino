#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include <HttpClient.h>
#include <WiFi.h>
#include <ArduinoHttpClient>
const int trigPin = 9;
const int echoPin = 8;
const int buzzerPin = 3;
long duration;
int distance;
Servo myServo;
String token = "45e04c0f-07d8-48ab-9386-b0af81bab9c3" 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(7);
  pinMode(buzzerPin, OUTPUT); // Définit le buzzerPin comme une sortie
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
void sendJsonData(int distance) {
  if (WiFi.status() == WL_CONNECTED) {
    String jsonData = "{\"distance\": " + String(distance) + '"' "}";
    String url = "http://127.0.0.1:2000/AT-PGN/distance/datas"
    int httpResponseCode = HttpClient().post(url,jsonData);
    if (httpResponseCode > 0) {
      Serial.print("Envoi de données JSON réussi. Code de réponse : ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Erreur lors de l'envoi de données JSON. Code d'erreur : ");
      Serial.println(httpResponseCode);
    }
  }
}
