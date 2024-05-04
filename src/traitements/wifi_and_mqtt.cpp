/**
 * @file wifi_and_mqtt.cpp
 * @brief Gestion de la connexion WiFi et MQTT
 * @date 2024-04-05
 * @author Tom
 */

#include "../../include/wifi_and_mqtt.h" // Inclure les bibliothèques nécessaires

WebServer server(80); // Créer une instance de serveur Web sur le port 80
WiFiClient eClient; // Créer une instance de client WiFi
PubSubClient client(eClient); // Créer une instance de client MQTT

/**
 * @brief Fonction pour gérer la soumission du formulaire
 * 
 * Cette fonction récupère les informations du formulaire, tente de se connecter au réseau WiFi
 * et au serveur MQTT, puis envoie un message MQTT.
 */
void handleFormSubmit() {
  // Récupérer les informations du formulaire
  String esp32Name = server.arg("name");
  String wifiSSID = server.arg("name_wifi");
  String wifiPassword = server.arg("pass");
  String mqttServer = server.arg("server");
  String mqttUser = server.arg("user");
  String mqttPassword = server.arg("pass_mqtt");
  
  Serial.print("Tentative de connexion au réseau WiFi: ");
  Serial.println(wifiSSID);

  WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());

  // Attendre la connexion au réseau WiFi
  if (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Veuillez configurer à nouveau le système");
  } else{
    Serial.print("Connexion au WIFI choisi effectuée avec succès");
  }

  Serial.print("Tentative de connexion au serveur MQTT: ");
  client.setServer(mqttServer.c_str(), 1883);
  
  // Tenter de se connecter au serveur MQTT
  if (client.connect("ESP32Client", mqttUser.c_str(), mqttPassword.c_str())) {
    
    Serial.println("Connecté au MQTT !");

    WiFi.softAPdisconnect(false); // Désactiver le mode station WiFi
    Serial.print("WiFi déconnecté");
    delay(1000);

    subcribeTopic(); // S'abonner au topic MQTT
    client.setCallback(callback); // Définir la fonction de rappel MQTT

  } else {
    Serial.print("Échec de la connexion, erreur: ");
    Serial.println(client.state());
  } 
  oledErase(); // Effacer l'écran OLED
}

/**
 * @brief Fonction pour s'abonner à un topic MQTT
 * 
 * Cette fonction permet de s'abonner au topic "topic/capteurs".
 */
void subcribeTopic(){
    // S'abonner au topic MQTT distant
  client.subscribe("topic/capteurs");
  Serial.println("Abonnement au topic distant effectué avec succès !");
}

/**
 * @brief Fonction pour envoyer un message MQTT avec une trame JSON
 * 
 * Cette fonction convertit une chaîne JSON en un tableau de caractères et l'envoie sur un topic MQTT désiré.
 * 
 * @param message La chaîne JSON à envoyer
 */
void sendMQTTFrame(const String& message) {
  // Convertir la chaîne JSON en tableau de caractères pour l'envoi MQTT
  char messageBuffer[200];
  message.toCharArray(messageBuffer, 200);

  // Envoyer le message MQTT sur le topic désiré
  client.publish("topic/capteurs", messageBuffer);
  Serial.println("Message MQTT envoyé avec succès !");
  Serial.println(messageBuffer);
}

/**
 * @brief Fonction de rappel pour la réception de messages MQTT
 * 
 * Cette fonction est appelée lorsque des messages sont reçus sur un topic MQTT auquel le client est abonné.
 * Elle affiche le topic et le contenu du message sur la console série.
 * @param Le topic, le contenue du message et la longueur du message
 */
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message reçu sur le topic : ");
  Serial.println(topic);

  Serial.print("Contenu du message : ");
  for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
  }
  Serial.println();
}