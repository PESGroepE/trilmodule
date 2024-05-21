
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const String host = "10.0.10.1:8080"; //pi adres

int vibPin = D5; //pin waarop de motor is aangesloten
String payload = ""; // de payload string dat vanuit de Pi ontvangen wordt


void setup() {
    Serial.begin(9600);
    pinMode(vibPin, OUTPUT);  //pin van de trilmodule op output
    digitalWrite(vibPin, LOW);  //trillen uitzetten

    WiFi.begin("pigroep5", "pigroep5"); //Wemos verbinden met Pi Wifi
  Serial.println("Connecting to pigroep5 WiFi"); 
  while (WiFi.status() != WL_CONNECTED)       //Wachten Wemos met Wifi verbonden is
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

}

void loop() {

  WiFiClient client;
  HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    String url = "http://" +host+ "/trilmodule?data";
    if (http.begin(client, url)) {  //

      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();

      //httpCode will be negative on error
      if (httpCode < 0) {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        return;
      }

        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
          if (payload == "1") {
        digitalWrite(vibPin, HIGH);
    } else if (payload == "0") {
        digitalWrite(vibPin, LOW);
    }
        }

      http.end();
    } else {
      Serial.println("[HTTP] Unable to connect");
    }

  //delay(1000);

}    

}