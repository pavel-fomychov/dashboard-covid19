/*
   Project Name: COVID-19 DASHBOARD
   Components Used: ESP32, OLED Display

   Author: Vinod Mandavkar
   Edited by: Pavel Fomychov
   Instagram: https://www.instagram.com/pavel.fomychov/
   Youtube: https://www.youtube.com/channel/UCKnntbMKHQb7DF9WJJ-vYPA
*/

//Use this if you are using ESP32
//#include <WiFi.h>
//#include <HTTPClient.h>

//Use this if you are using ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ArduinoJson.h"
HTTPClient http;
JsonObject root;

int screen = 1;
String population = "", cases_precent = "", cases_new = "", deaths_new = "";
unsigned long cases_active, cases_recovered, cases_total, deaths_total, lastUpdate;

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire); //Using the Adafruit Library

#include "OneButton.h"
OneButton button(13, false); //D7 (GPIO13)

const char* ssid = "********";  //Add your WIFi-SSID
const char* password = "********";  //Add your WIFi-password

void setup() {
  Serial.begin(115200);  //Starting Serial Communication
  WiFi.disconnect(true); //Disconecting the WiFi if we are previouly connected.

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64  |  You can change this to 0x3C if your display doesn't work
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  button.attachClick(clickBtn);
  button.attachLongPressStart(longPressBtn);

  //Intro Page - Change according to your needs
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(14, 1);
  display.println("COVID-19");
  display.setCursor(2, 20);
  display.println("STATISTICS");
  display.setCursor(8, 40);
  display.println("(<LOCATION>)"); // display Country name
  display.display();
  delay(2000);

  WiFi.begin(ssid, password); // Connecting to the WiFi

  while (!(WiFi.status() == WL_CONNECTED)) { //Wait till we are connected
    animate_oled_wifi();  // Animate it on the Screen
  }

  Serial.println("Connected to the WiFi network");

  display.clearDisplay();
  display.setCursor(19, 1);
  display.println("SUCCESS");
  display.setCursor(7, 20);
  display.println("Connected");
  display.setCursor(19, 40);
  display.println("to WiFi");
  display.display();
}

void loop() {
  button.tick();

  if (lastUpdate < millis()) {

    if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

      // ATTENTION! replace values <YOUR_DOMAIN> <YOUR_AUTH_KEY> <YOUR_COUNTRY>
      http.begin("http://<YOUR_DOMAIN>/api-covid.php?auth-key=<YOUR_AUTH_KEY>&country=<YOUR_COUNTRY>");
      int httpCode = http.GET(); //Make the request

      if (httpCode > 0) { //Check for the returning code

        String payload = http.getString();
        Serial.println(payload);   //Print request response payload

        DynamicJsonDocument doc(2 * payload.length());  //Flexible size
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.c_str());
          return;
        }

        root = doc.as<JsonObject>(); //Mapping the data to Json Object
      }
      http.end(); //Free the resources
    }

    for (JsonPair kv : root) {
      //Finding specific keys and extracting their values in varibales
      if (String(kv.key().c_str()) == "population") {
        population = (kv.value().as<String>());
      }
      if (String(kv.key().c_str()) == "cases_new") {
        cases_new = kv.value().as<String>();
      }
      if (String(kv.key().c_str()) == "cases_active") {
        cases_active = kv.value().as<int>();
      }
      if (String(kv.key().c_str()) == "cases_recovered") {
        cases_recovered = kv.value().as<long>();
      }
      if (String(kv.key().c_str()) == "cases_precent") {
        cases_precent = kv.value().as<String>();
      }
      if (String(kv.key().c_str()) == "cases_total") {
        cases_total = kv.value().as<long>();
      }
      if (String(kv.key().c_str()) == "deaths_new") {
        deaths_new = kv.value().as<String>();
      }
      if (String(kv.key().c_str()) == "deaths_total") {
        deaths_total = kv.value().as<long>();
      }
    }

    if (cases_active > 0) {
      lastUpdate = millis() + 60000;
    } else {
      lastUpdate = 0;
    }

  }


  if (cases_active > 0) {
    if (screen == 1) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(4, 1);
      display.println("ACTIVE:");
      display.setCursor(4, 17);
      display.println(cases_active);
      display.setTextSize(1);
      display.setCursor(4, 37);
      display.println("OF THEM NEW:");
      display.setTextSize(2);
      display.setCursor(4, 47);
      display.println(cases_new);
      display.display();
    }
    if (screen == 2) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(4, 1);
      display.println("RECOVERED:");
      display.setCursor(4, 17);
      display.println(cases_recovered);
      display.setTextSize(1);
      display.setCursor(4, 37);
      display.println("PRECENT OF CASES:");
      display.setTextSize(2);
      display.setCursor(4, 47);
      display.print(cases_precent);
      display.println("%");
      display.display();
    }
    if (screen == 3) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(4, 1);
      display.println("DEATHS:");
      display.setCursor(4, 17);
      display.println(deaths_total);
      display.setTextSize(1);
      display.setCursor(4, 37);
      display.println("OF THEM NEW:");
      display.setTextSize(2);
      display.setCursor(4, 47);
      display.println(deaths_new);
      display.display();
    }
    if (screen == 4) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(4, 1);
      display.println("TOTAL:");
      display.setCursor(4, 17);
      display.println(cases_total);
      display.setTextSize(1);
      display.setCursor(4, 37);
      display.println("PRECENT OF POPULAT.");
      display.setTextSize(2);
      display.setCursor(4, 47);
      display.print(population);
      display.println("%");
      display.display();
    }
  }

}

void clickBtn() {
  screen++;
  if (screen > 4) screen = 1;
}

void longPressBtn() {
  lastUpdate = 0;
}

//WiFi Connection Animation
void animate_oled_wifi() {
  display.clearDisplay();
  display.setCursor(2, 20);
  display.println("Connecting");
  display.setCursor(2, 40);
  display.println("to WiFi...");
  display.setCursor(9, 1);
  display.println("   {-}   ");
  display.display();
  delay(500);
  display.clearDisplay();
  display.setCursor(2, 20);
  display.println("Connecting");
  display.setCursor(2, 40);
  display.println("to WiFi...");
  display.setCursor(9, 1);
  display.println("  { - }  ");
  display.display();
  delay(500);
  display.clearDisplay();
  display.setCursor(2, 20);
  display.println("Connecting");
  display.setCursor(2, 40);
  display.println("to WiFi...");
  display.setCursor(9, 1);
  display.println(" {  -  } ");
  display.display();
  delay(500);
  display.clearDisplay();
  display.setCursor(2, 20);
  display.println("Connecting");
  display.setCursor(2, 40);
  display.println("to WiFi...");
  display.setCursor(9, 1);
  display.println("{   -   }");
  display.display();
  delay(500);
}
