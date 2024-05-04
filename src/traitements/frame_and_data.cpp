/**
 * @file frame_and_data.cpp
 * @brief Création de la trame JSON contenant les données des capteurs
 * @date 2024-04-05
 * @author Tom
 */

#include "../../include/frame_and_data.h" // Inclure les bibliothèques nécessaires

/**
 * @brief Fonction pour créer la trame JSON contenant les données des capteurs
 * 
 * Cette fonction crée un objet JSON pour stocker les données de température, d'humidité,
 * de CO2 et l'adresse MAC de l'ESP32. Les données sont récupérées à partir des fonctions
 * correspondantes de récupération des capteurs.
 * 
 * @return La trame JSON contenant les données des capteurs
 */
String createJSONMessage() {
    // Créer un objet JSON pour stocker les données
    StaticJsonDocument<200> jsonDoc;

    // Ajouter des données à l'objet JSON
    jsonDoc["esp32_mac"] = WiFi.macAddress(); // Ajouter l'adresse MAC de l'ESP32
    jsonDoc["temperature"] = recoverTemp(); // Ajouter la température
    delay(200); // Attendre un court délai pour éviter les problèmes de lecture concurrente
    jsonDoc["humidity"] = recoverHum(); // Ajouter l'humidité
    jsonDoc["co2"] = recoverCO2Data(); // Ajouter les données de CO2

    // Convertir l'objet JSON en chaîne JSON
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    return jsonString; // Retourner la trame JSON
}
