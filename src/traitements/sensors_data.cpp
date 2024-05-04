/**
 * @file sensors_data.cpp
 * @brief Sensor Data Retrieval
 * @date 2024-04-05
 * @author Izukend
 */

#include "../../include/sensors_data.h" // Include necessary libraries

#define RX_PIN 10 // Define the RX pin for serial communication
#define TX_PIN 11 // Define the TX pin for serial communication
#define BAUDRATE 9600 // Define the baud rate for serial communication

MHZ19 myMHZ19; // Declare an object for the MH-Z19 sensor
DHTesp dht; // Declare an object for the DHT22 sensor
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare an object for software serial communication

int dhtPin = 17; // Define the pin to which the DHT22 sensor is connected

/**
 * @brief Function to retrieve CO2 data
 * 
 * This function initializes serial communication with the MH-Z19 sensor, retrieves raw CO2 data,
 * adjusts it according to a specific formula, and then converts it to an integer.
 * 
 * @return The adjusted CO2 value as an integer
 */
int recoverCO2Data() {
    mySerial.begin(BAUDRATE); // Initialize serial communication
    myMHZ19.begin(mySerial); // Initialize the MH-Z19 sensor

    double adjustedCO2 = myMHZ19.getCO2(); // Retrieve raw CO2 data from the sensor

    Serial.println("----------------");
    Serial.print("CO2 Reading: ");
    Serial.println(adjustedCO2);
    // Convert the value to an integer
    int intValue = int(adjustedCO2);
    
    return intValue; // Return the CO2 value
}

/**
 * @brief Function to retrieve temperature
 * 
 * This function sets up the DHT22 sensor, retrieves temperature data, and converts it to an integer.
 * 
 * @return The temperature as an integer
 */
int recoverTemp(){
    dht.setup(dhtPin, DHTesp::DHT22); // Set up the DHT22 sensor
    TempAndHumidity value = dht.getTempAndHumidity(); // Retrieve temperature data
    
    Serial.println("----------------");
    Serial.println("Temperature Reading:");
    Serial.println(value.temperature);
    
    int tempValue = int(value.temperature); // Convert temperature to an integer
    return tempValue; // Return the temperature
}

/**
 * @brief Function to retrieve humidity
 * 
 * This function sets up the DHT22 sensor, retrieves humidity data, and converts it to an integer.
 * 
 * @return The humidity as an integer
 */
int recoverHum() {
    dht.setup(dhtPin, DHTesp::DHT22); // Set up the DHT22 sensor
    TempAndHumidity value = dht.getTempAndHumidity(); // Retrieve humidity data
    
    Serial.println("----------------");
    Serial.println("Humidity Reading:");
    Serial.println(value.humidity);
    
    int humidityValue = int(value.humidity); // Convert humidity to an integer
    return humidityValue; // Return the humidity
}
