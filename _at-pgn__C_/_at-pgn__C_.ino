#include <Servo.h>
#include "C:/Users/33769/Desktop/config/configuration.h"


#define STEPPER_PIN_1 6
#define STEPPER_PIN_2 11
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 12

int trigPin = 9;
int echoPin = 8;
int buzzerPin = 3;
long duration;
int distance;
Servo myServo;
//BridgeHttpClient client;
//String tokenn = token; //token à envoyer à l'api pour s'authentifier il a été importé 
//String serverIP = "127.0.0.1";
//String port = "2000";
//String endpoint = "/distance/datas";
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(7);
  pinMode(buzzerPin, OUTPUT); // Définit le buzzerPin comme une sortie
}
// à mettre dans le futur void setup
//Bridge.begin();
//SerialUSB.begin(9600);
//while(!SerialUSB);
//client.addHeader("Content-Type: application/json");
//client.enableInsecure();
//WiFi.begin(ssid, password); 
//Serial.println(ssis);
//Serial.println(password);
//Serial.println(token);
//WiFi.begin(ssid, password); //déjà importées
void loop() {
  OneStep(false);
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(0);
    distance = calculateDistance();
    if (distance <= 100) { // Condition pour une distance inférieure à 1 mètre
      tone(buzzerPin, 500, 400);
      digitalWrite(buzzerPin, HIGH);
       // Active le buzzer
    }
  }

  for (int i = 165; i > 15; i--) {
    OneStep(false);
    myServo.write(i);
    delay(0);
    distance = calculateDistance();
    if (distance <= 100) { // Condition pour une distance inférieure à 1 mètre
      tone(buzzerPin, 500, 400);
      digitalWrite(buzzerPin, HIGH); // Active le buzzer
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

bool import() {
  try {
    #include "C:/Users/33769/Desktop/config/configuration.h"
    Serial.println("Imported");
    } 
  catch {
    Serial.println("Not imported");
    } 
}



void OneStep(bool dir){
    if(dir){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 
  }else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
 
  
} 
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}
