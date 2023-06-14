//import that we'll use later in the project
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <HttpClient.h>
#include <WiFi.h>
#include <Bridge.h>
#include <ArduinoHttpClient.h>
#include <BridgeHttpClient.h>
// normal if there are variables not defined, such as client ;)
void makePostRequest(int datadistance) {
  String response;
  client.get("https://www.timeapi.io/api/Time/current/zone?timeZone=Europe/Amsterdam");
  String url = "http://127.0.0.1:2000/distance/datas";
  String data = "{\"distance\":\"";
  println(response);
  data += datadistance;
  data += "\"";
  data += ",\"hour\":\"";
  data += response;
  data += "\",\"token\":\"";
  data += tokenn;
  data += "\"}";
  client.post(url, data);
}