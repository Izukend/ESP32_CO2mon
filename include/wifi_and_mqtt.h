/**
 * @file wifi_and_mqtt.h
 * @date 2024-04-05
 * @author Tom
 */

#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>
#include "screen.h"
#include "frame_and_data.h"

extern WebServer server;
extern PubSubClient client;


extern void handleFormSubmit();

extern void subcribeTopic() ;

extern void callback(char* topic, byte* payload, unsigned int length);

extern void sendMQTTFrame(const String& message) ;