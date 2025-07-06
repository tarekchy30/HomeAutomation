#include <ESP8266WiFi.h>

const char* apSSID = "Wemos_Light";  // you can change wemos_Light to anything
const char* apPassword = "12345678"; // also password

#define RELAY_PIN D4  

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);
  

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); 


  WiFi.softAP(apSSID, apPassword);
  
  Serial.println("\nAccess Point Started");
  Serial.print("SSID: "); Serial.println(apSSID);
  Serial.print("IP: "); Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("\nNew client connected");
    String request = client.readStringUntil('\r');
    Serial.println("Request: " + request);
    client.flush();

    if (request.indexOf("/on") != -1) {
      digitalWrite(RELAY_PIN, LOW); 
      Serial.println("Relay ON - Light ON");
    }
    else if (request.indexOf("/off") != -1) {
      digitalWrite(RELAY_PIN, HIGH); 
      Serial.println("Relay OFF - Light OFF");
    }

    // Send HTTP response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    

    delay(10);
    client.stop();
    Serial.println("Client disconnected");
  }
}

