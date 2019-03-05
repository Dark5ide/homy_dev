#define DEBUG

#include "Homy_dev.h"

void setup(void)
{
  pinMode(mdl1.pinNb, OUTPUT);
  pinMode(mdl2.pinNb, OUTPUT);
  pinMode(mdl3.pinNb, OUTPUT);
  pinMode(mdl4.pinNb, OUTPUT);
  

  //DEBUG_INIT_LED(led, OUTPUT);
  //DEBUG_LED(mdl1.pinNb, HIGH);
  //DEBUG_LED(mdl2.pinNb, HIGH);
  //DEBUG_LED(led, LOW);
  
#ifdef DEBUG
  Serial.begin(115200);
#endif
  DEBUGGING_L("");

  WiFiConnect();
  MDNSSetup();
  MqttSetup();
  WebSocketSetup();
  InitHandleHTTP();
  HTTPUpdateConnect();
  //InitIR();

  Command("turn_on", &mdl0);
  Command("turn_on", &mdl1);
  Command("turn_on", &mdl2);
  Command("turn_on", &mdl3);
  //DEBUG_LED(mdl1.pinNb, mdl1.state);
  //DEBUG_LED(mdl2.pinNb, mdl2.state);
}

void loop(void)
{

  if (WiFi.status() != WL_CONNECTED)
  {
    WiFiConnect();
    MDNSSetup();
    MqttSetup();
    WebSocketSetup();
  }
  else
  {
    if (!client.connected())
    {
      MqttConnect();
    }
    client.loop();
    webSocket.loop();
    httpServer.handleClient();
    //MDNS.update();
  }
}

