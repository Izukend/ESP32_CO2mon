/**
 * @file screen.cpp
 * @brief OLED Screen Management
 * @date 2024-04-05
 * @author Izukend
 */

#include "../../include/screen.h" // Including necessary libraries

SSD1306Wire display(0x3c, SDA, SCL); // Creating an instance of the OLED screen with address 0x3c

/**
 * @brief Function to initialize the OLED screen
 * 
 * This function initializes the OLED screen by configuring the display with centered text
 * indicating the IP address to enter in the web browser.
 */
void oledInit(){
    // Initialize the OLED screen
    display.init();
    display.setTextAlignment(TEXT_ALIGN_CENTER); // Text alignment set to center
    display.setFont(ArialMT_Plain_10); // Using ArialMT font with size 10

    // Display text on the OLED screen
    display.drawString(64, 16, "Enter on web browser:");
    display.drawString(64, 48, "192.168.4.1");
    display.display(); // Update the display
}

/**
 * @brief Function to clear the OLED screen
 * 
 * This function clears the current content of the OLED screen.
 */
void oledErase(){
    display.clear(); // Clear the OLED screen
    display.display(); // Update the display to apply the changes
}

/**
 * @brief Display CO2 data on the OLED screen.
 * 
 * This function initializes serial communication with the MH-Z19 sensor, retrieves the CO2 data
 * from the sensor, converts it to a string, and displays it on the OLED screen.
 */
void oledPrintData() {
    // Initialize serial communication with the MH-Z19 sensor
    mySerial.begin(9600);
    // Initialize the MH-Z19 sensor
    myMHZ19.begin(mySerial);

    // Wait for 3 seconds to allow the sensor to initialize
    delay(2000);

    // Retrieve raw CO2 data from the MH-Z19 sensor
    double adjustedCO2 = myMHZ19.getCO2();
    // Convert CO2 data to a string
    String strCO2 = String(adjustedCO2);
    // Clear the OLED screen for a fresh update
    display.clear();

    // Display CO2 data at the top of the OLED screen
    display.drawString(64, 16, "CO2: " + strCO2);

    // Update the display on the OLED screen
    display.display();
}
