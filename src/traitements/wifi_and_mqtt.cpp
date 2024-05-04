/**
 * @file wifi_and_mqtt.cpp
 * @brief WiFi and MQTT Connection Management
 * @date 2024-04-05
 * @author Izukend
 */

#include "../../include/wifi_and_mqtt.h" // Include necessary libraries

WebServer server(80); // Create an instance of Web server on port 80
WiFiClient eClient; // Create an instance of WiFi client
PubSubClient client(eClient); // Create an instance of MQTT client

/**
 * @brief Function to handle form submission
 * 
 * This function retrieves form information, attempts to connect to the WiFi network
 * and the MQTT server, and then sends an MQTT message.
 */
void handleFormSubmit() {
  // Retrieve form information
  String esp32Name = server.arg("name");
  String wifiSSID = server.arg("name_wifi");
  String wifiPassword = server.arg("pass");
  String mqttServer = server.arg("server");
  String mqttUser = server.arg("user");
  String mqttPassword = server.arg("pass_mqtt");
  
  Serial.print("Attempting to connect to WiFi network: ");
  Serial.println(wifiSSID);

  WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());

  // Wait for WiFi network connection
  if (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Please reconfigure the system");
  } else{
    Serial.print("Successfully connected to chosen WIFI");
  }

  Serial.print("Attempting to connect to MQTT server: ");
  client.setServer(mqttServer.c_str(), 1883);
  
  // Attempt to connect to MQTT server
  if (client.connect("ESP32Client", mqttUser.c_str(), mqttPassword.c_str())) {
    
    Serial.println("Connected to MQTT!");

    WiFi.softAPdisconnect(false); // Disable WiFi station mode
    Serial.print("WiFi disconnected");
    delay(1000);

    subcribeTopic(); // Subscribe to MQTT topic
    client.setCallback(callback); // Set MQTT callback function

  } else {
    Serial.print("Connection failed, error: ");
    Serial.println(client.state());
  } 
  oledErase(); // Clear OLED screen
}

/**
 * @brief Function to subscribe to an MQTT topic
 * 
 * This function subscribes to the "topic/sensors" MQTT topic.
 */
void subcribeTopic(){
    // Subscribe to remote MQTT topic
  client.subscribe("topic/sensors");
  Serial.println("Subscribed to remote topic successfully!");
}

/**
 * @brief Function to send an MQTT message with a JSON frame
 * 
 * This function converts a JSON string to a character array and sends it on a desired MQTT topic.
 * 
 * @param message The JSON string to send
 */
void sendMQTTFrame(const String& message) {
  // Convert JSON string to character array for MQTT sending
  char messageBuffer[200];
  message.toCharArray(messageBuffer, 200);

  // Send MQTT message on desired topic
  client.publish("topic/sensors", messageBuffer);
  Serial.println("MQTT message sent successfully!");
  Serial.println(messageBuffer);
}

/**
 * @brief Callback function for receiving MQTT messages
 * 
 * This function is called when messages are received on an MQTT topic to which the client is subscribed.
 * It displays the topic and message content on the serial console.
 * @param topic The topic, message content, and message length
 */
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);

  Serial.print("Message content: ");
  for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
  }
  Serial.println();
}
