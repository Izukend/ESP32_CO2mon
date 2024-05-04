# ESP32 Wi-Fi and MQTT Configuration

This project demonstrates how to configure an ESP32 to connect to a Wi-Fi station and an MQTT server to send messages.

## Setup

1. **Connect the ESP32:** Connect your ESP32 board to your computer using a USB cable.

2. **Install Dependencies:**
   - Install the Arduino IDE if you haven't already.
   - Install the necessary libraries: `WiFi.h` and `PubSubClient.h`.

3. **Configure Wi-Fi and MQTT Credentials:**
   - Open the `wifi_mqtt_config.ino` file in your Arduino IDE.
   - Replace the placeholders with your Wi-Fi and MQTT credentials:
     ```cpp
     const char* ssid = "YourWiFiSSID";
     const char* password = "YourWiFiPassword";
     const char* mqttServer = "mqtt.example.com";
     const int mqttPort = 1883;
     const char* mqttUser = "YourMQTTUsername";
     const char* mqttPassword = "YourMQTTPassword";
     const char* mqttTopic = "esp32/data";
     ```

4. **Upload the Sketch:** Upload the sketch to your ESP32 board.

5. **Monitor Serial Output:** Open the serial monitor in the Arduino IDE to view the ESP32's connection status and message sending.

## Usage

- Once the ESP32 is connected to Wi-Fi and MQTT, it will send a message ("Hello from ESP32") to the specified MQTT topic ("esp32/data") every 5 seconds.
- Monitor the serial output to ensure the ESP32 is successfully connected and sending messages.

## Troubleshooting

- If the ESP32 fails to connect to Wi-Fi or MQTT, double-check your credentials and ensure the network and broker are accessible.
- Ensure the necessary libraries (`WiFi.h` and `PubSubClient.h`) are properly installed in your Arduino IDE.

## Contributing

Contributions are welcome! If you have suggestions for improvements or encounter any issues, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
