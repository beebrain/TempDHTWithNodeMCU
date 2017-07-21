#include "DHT.h"
#include <AntoIO.h>

#define DHTPIN D2     // what digital pin we're connected t
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

const char *ssid = "boobee";
const char *pass = "123443213";
const char *user = "beebrain";
const char *token = "Ep6DmnL2BmhRR9KvYQbpfpRuKdVtOY8Nw55t5OnT";
const char *thing = "TempSensor";



DHT dht(DHTPIN, DHTTYPE);
AntoIO anto(user, token, thing);
void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();

  anto.begin(ssid, pass, messageReceived);
  //Anto.begin("JP_Terrace01_N1", "82341991", "fKbwcRlgb2ibpF7j7x4sFlEhDcIoeM65ULhIJOPE", "TempSensor");
 //Anto.begin("JP_Terrace01_N1", "82341991", "fKbwcRlgb2ibpF7j7x4sFlEhDcIoeM65ULhIJOPE", "TempSensor");
}

void loop() {
  
    anto.mqtt.loop();
    Serial.println("Loop MQTT");
   if (!anto.mqtt.isConnected())
    Serial.println("Disconnected");

  float temp = dht.readTemperature();
  float humid = dht.readHumidity();

  Serial.print("TEMP: ");
  Serial.println(temp);

  Serial.print("HUMID: ");
  Serial.println(humid);
     anto.pub("Temp",temp);           
     anto.pub("HHD",humid);

  delay(1000);
}

// a callback function for arriving data.
void messageReceived(String thing, String channel, String payload) {
  Serial.print("Recieved: ");
  Serial.print(thing);
  Serial.print("/");
  Serial.print(channel);
  Serial.print("-> ");
  Serial.println(payload);
}
