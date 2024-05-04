/**
 * @file main.cpp
 * @brief WiFi and MQTT Configuration from a Web Page
 * @author Izukend
 * @date 2024-03-08
 * @description Allows configuring WiFi and MQTT from a web page for the technician
 */

#include "main.h" // Include necessary libraries

const char* ssid = "Your ssid";
const char* password = "Your password";
const char* redirectUrl = "/data/index.html"; // Path to the index.html file

unsigned long getDataTimer = 0; // Timer for data retrieval

/**
 * @brief Function for handling the home page
 * 
 * This function redirects to the configuration web page.
 */
void handleRoot() {
  server.sendHeader("Location", redirectUrl); // Redirect to the specified URL
  server.send(200, "text/html", Home); // Send the home page to the client
  Serial.println("Redirecting to web page...");
}

/**
 * @brief Initialization function
 * 
 * This function initializes the system and configures the WiFi access point.
 */
void setup() {
  // Initialization
  Serial.begin(9600); // Start serial communication
  delay(2000); // Wait 2 seconds to allow startup

  // OLED screen initialization
  oledInit();

  // Configure WiFi access point mode
  WiFi.mode(WIFI_MODE_AP); // Configure WiFi mode to access point
  WiFi.softAP(ssid, password); // Start WiFi access point

  // Display access point IP address
  Serial.print("Access Point IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Configure the Web server to handle redirection
  server.on("/", handleRoot); // Handle the home page

  // Handle form submission
  server.on("/submit", HTTP_POST, [](){
      server.send(200, "text/plain", "Data received successfully !");
      handleFormSubmit();
  });

  server.begin(); // Start the Web server
  Serial.println("Web Server started !");
}

/**
 * @brief Main function of the program loop
 * 
 * This function handles HTTP and MQTT clients, periodically retrieves sensor data,
 * and sends it via MQTT.
 */
void loop() {
    // Handle clients (HTTP and MQTT)
    server.handleClient(); // Handle HTTP requests
    client.loop(); // Handle MQTT messages

    // Check if MQTT client is connected
    if (client.connected()) {
        // Display real-time CO2 data
        oledPrintData();

        // Check if it's time to retrieve data
        if (millis() - getDataTimer >= 60000) { // Wait 60 seconds
            // Send MQTT message containing JSON data
            sendMQTTFrame(createJSONMessage());
            Serial.println("Frame sent successfully");
            // Reset timer
            getDataTimer = millis();
        }
    }
}
