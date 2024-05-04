/**
 * @file frame_and_data.cpp
 * @brief Creation of JSON frame containing sensor data
 * @date 2024-04-05
 * @author Izukend
 */

#include "../../include/frame_and_data.h" // Including necessary libraries

/**
 * @brief Function to create the JSON frame containing sensor data
 * 
 * This function creates a JSON object to store temperature, humidity,
 * CO2 data, and the MAC address of the ESP32. The data is retrieved from
 * the corresponding sensor recovery functions.
 * 
 * @return The JSON frame containing sensor data
 */
String createJSONMessage() {
    // Create a JSON object to store data
    StaticJsonDocument<200> jsonDoc;

    // Add data to the JSON object
    jsonDoc["esp32_mac"] = WiFi.macAddress(); // Add ESP32 MAC address
    jsonDoc["temperature"] = recoverTemp(); // Add temperature
    delay(200); // Wait for a short delay to avoid concurrent reading issues
    jsonDoc["humidity"] = recoverHum(); // Add humidity
    jsonDoc["co2"] = recoverCO2Data(); // Add CO2 data

    // Convert the JSON object to JSON string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    return jsonString; // Return the JSON frame
}
