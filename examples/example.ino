#include <RoboFIFA_communication.h>

RoboFIFA_communication com("192.168.43.12");


void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}

void setup() {
  
  Serial.begin(115200);
  const char* ssid = "miwifi";
  const char* password = "neeneenee";
  com.setup_wifi(ssid, password);
  com.setup_mqtt(callback);
}


void loop() {
  static long lastMsg = 0;
  
  com.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    
    // Convert the value to a char array
    char tempString[32];
    dtostrf(lastMsg, 1, 2, tempString);
    com.client.publish("esp32/temperature", tempString);
  }
}
