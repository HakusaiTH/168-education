//firebase
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "FF1_15"
#define WIFI_PASSWORD "123456789"

#define API_KEY "EBbLB9Gaj7xTDRhF6CSuEy7qZ4bOrByn2MvOKqGi"  

#define DATABASE_URL "https://my-robot-9fdff-default-rtdb.asia-southeast1.firebasedatabase.app/" 

int intValue;

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void setup(){
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  
  config.database_url = DATABASE_URL;
  
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
  if(Firebase.RTDB.getString(&fbdo, "/Status")) 
  {
    String Status = fbdo.stringData();
    Serial.println(Status.toInt());
  }
  else{
    Serial.println(fbdo.errorReason());  
  }
}
