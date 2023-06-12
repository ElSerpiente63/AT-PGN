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


const char* tokenn = "45e04c0f-07d8-48ab-9386-b0af81bab9c3"; //token à envoyer à l'api pour s'authentifier il a été importé 
const char* ssid = "LIVEBOX-D7DC";
char* password = "E77F795C9EF46CF92E419DAC2C";

String serverIP = "127.0.0.1";
String port = "2000";
String endpoint = "/distance/datas";
void setup() {
  BridgeHttpClient client;
  Serial.println(ssid);
  Serial.println(password);
  Serial.println(tokenn);
  WiFi.begin(ssid, password); //déjà importées
  Serial.begin(9600);
  Bridge.begin();
  client.addHeader("Content-Type: application/json");
  client.enableInsecure();
}
void makePostRequest(int datadistance) {
  BridgeHttpClient client;
  String response;
  client.get("https://www.timeapi.io/api/Time/current/zone?timeZone=Europe/Amsterdam");
  String url = "http://127.0.0.1:2000/distance/datas";
  String data = "{\"distance\":\"";
  Serial.println(response);
  data += datadistance;
  data += "\"";
  data += ",\"hour\":\"";
  data += response;
  data += "\",\"token\":\"";
  data += tokenn;
  data += "\"}";
  client.post(url, data);
}
void loop() {
  makePostRequest(250);

}
