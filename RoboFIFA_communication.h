#ifndef ROBOFIFA_COMMUNICATION
#define ROBOFIFA_COMMUNICATION

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

class RoboFIFA_communication{
  public:
    RoboFIFA_communication(const char* mqtt_server);
    void setup_wifi(const char* ssid, const char* password);
    void setup_mqtt(void (*callback)(char*, byte*, unsigned int));
    void loop();
    void reconnect();
    PubSubClient client;
    int robot_id = 0;
  private:
    // Replace the next variables with your SSID/Password combination
    WiFiClient espClient;
    const char* mqtt_server;
    void (*callback)(char*, byte*, unsigned int);
};



#endif
