#include "ROBOFIFA_COMMUNICATION.h"

RoboFIFA_communication::RoboFIFA_communication(const char* mqtt_server): mqtt_server(mqtt_server), client(PubSubClient(espClient)){

}

void  RoboFIFA_communication::setup_mqtt(void (*callback)(char*, byte*, unsigned int)){
  this->callback = callback;
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void RoboFIFA_communication::setup_wifi(const char* ssid, const char* password) {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void RoboFIFA_communication::loop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
void RoboFIFA_communication::reconnect() {
  char mqtt_name[32] = "RoboFIFA/";
  int len = strlen(mqtt_name);
  sprintf(mqtt_name + len, "robot%i", robot_id);
  Serial.print("Attempting MQTT connection...");
  // Attempt to connect
  if (client.connect(mqtt_name + len)) {
    Serial.print("connected as ");
    Serial.println(mqtt_name + len);
    // Subscribe
    client.subscribe(mqtt_name);
    Serial.print("subscribed to ");
    Serial.println(mqtt_name);
  } else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
    // Wait 1 seconds before retrying
    delay(1000);
  }
}
