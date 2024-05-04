/**
 * @file main.cpp
 * @brief Configuration WiFi et MQTT depuis un site web
 * @author Matthieu et Tom
 * @date 2024-03-08
 * @description Permet de configurer WiFi et MQTT depuis un site web pour le technicien
 */

#include "main.h" // Inclure les bibliothèques nécessaires

const char* ssid = "ConfigWifi"; // Nom du réseau WiFi du point d'accès
const char* password = "Izu%2512"; // Mot de passe du point d'accès
const char* redirectUrl = "/data/index.html"; // Chemin vers le fichier index.html

unsigned long getDataTimer = 0; // Timer pour la récupération des données

/**
 * @brief Fonction de gestion de la page d'accueil
 * 
 * Cette fonction redirige vers la page web de configuration.
 */
void handleRoot() {
  server.sendHeader("Location", redirectUrl); // Rediriger vers l'URL spécifiée
  server.send(200, "text/html", Home); // Envoyer la page d'accueil au client
  Serial.println("Redirection vers la page web...");
}

/**
 * @brief Fonction d'initialisation
 * 
 * Cette fonction initialise le système et configure le point d'accès WiFi.
 */
void setup() {
  // Initialisation
  Serial.begin(9600); // Démarrer la communication série
  delay(2000); // Attendre 2 secondes pour permettre le démarrage

  // Initialisation de l'écran OLED
  oledInit();

  // Configuration du mode point d'accès WiFi
  WiFi.mode(WIFI_MODE_AP); // Configurer le mode WiFi en point d'accès
  WiFi.softAP(ssid, password); // Démarrer le point d'accès WiFi

  // Affichage de l'adresse IP du point d'accès
  Serial.print("Adresse IP du point d'accès: ");
  Serial.println(WiFi.softAPIP());

  // Configuration du serveur Web pour gérer la redirection
  server.on("/", handleRoot); // Gérer la page d'accueil

  // Gérer la soumission du formulaire
  server.on("/submit", HTTP_POST, [](){
      server.send(200, "text/plain", "Données reçues avec succès !");
      handleFormSubmit();
  });

  server.begin(); // Démarrer le serveur Web
  Serial.println("Serveur Web démarré !");
}

/**
 * @brief Fonction principale de la boucle de programme
 * 
 * Cette fonction gère les clients HTTP et MQTT, récupère périodiquement les données des capteurs
 * et les envoie via MQTT.
 */
void loop() {
    // Gestion des clients (HTTP et MQTT)
    server.handleClient(); // Gérer les requêtes HTTP
    client.loop(); // Gérer les messages MQTT

    // Vérifier si le client MQTT est connecté
    if (client.connected()) {
        // Afficher les données de CO2 en temps réel
        oledPrintData();

        // Vérifier si le délai pour récupérer les données est écoulé
        if (millis() - getDataTimer >= 60000) { // Attendre 60 secondes
            // Envoyer le message MQTT contenant les données JSON
            sendMQTTFrame(createJSONMessage());
            Serial.println("Envoie de la trame réussis");
            // Réinitialiser le compteur de temps
            getDataTimer = millis();
        }
    }
}
