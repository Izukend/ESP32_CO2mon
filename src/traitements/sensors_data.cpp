/**
 * @file sensors_data.cpp
 * @brief Récupération des données de capteurs
 * @date 2024-04-05
 * @author Matthieu et Tom
 */

#include "../../include/sensors_data.h" // Inclure les bibliothèques nécessaires

#define RX_PIN 10 // Définir la broche RX pour la communication série
#define TX_PIN 11 // Définir la broche TX pour la communication série
#define BAUDRATE 9600 // Définir le débit en bauds pour la communication série

MHZ19 myMHZ19; // Déclarer un objet pour le capteur MH-Z19
DHTesp dht; // Déclarer un objet pour le capteur DHT22
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Déclarer un objet pour la communication série logicielle

int dhtPin = 17; // Définir la broche à laquelle le capteur DHT22 est connecté

/**
 * @brief Fonction pour récupérer les données de CO2
 * 
 * Cette fonction initialise la communication série avec le capteur MH-Z19, récupère les données brutes de CO2,
 * les ajuste selon une formule spécifique, puis les convertit en un entier.
 * 
 * @return La valeur de CO2 ajustée en entier
 */
int recoverCO2Data() {
    mySerial.begin(BAUDRATE); // Initialiser la communication série
    myMHZ19.begin(mySerial); // Initialiser le capteur MH-Z19

    double adjustedCO2 = myMHZ19.getCO2(); // Récupérer les données brutes de CO2 depuis le capteur

    Serial.println("----------------");
    Serial.print("Affichage CO2: ");
    Serial.println(adjustedCO2);
    // Convertir la valeur en entier
    int intValue = int(adjustedCO2);
    
    return intValue; // Retourner la valeur de CO2
}

/**
 * @brief Fonction pour récupérer la température
 * 
 * Cette fonction configure le capteur DHT22, récupère les données de température et les convertit en un entier.
 * 
 * @return La température en entier
 */
int recoverTemp(){
    dht.setup(dhtPin, DHTesp::DHT22); // Configurer le capteur DHT22
    TempAndHumidity value = dht.getTempAndHumidity(); // Récupérer les données de température
    
    Serial.println("----------------");
    Serial.println("Affichage Temp :");
    Serial.println(value.temperature);
    
    int tempValue = int(value.temperature); // Convertir la température en entier
    return tempValue; // Retourner la température
}

/**
 * @brief Fonction pour récupérer l'humidité
 * 
 * Cette fonction configure le capteur DHT22, récupère les données d'humidité et les convertit en un entier.
 * 
 * @return L'humidité en entier
 */
int recoverHum() {
    dht.setup(dhtPin, DHTesp::DHT22); // Configurer le capteur DHT22
    TempAndHumidity value = dht.getTempAndHumidity(); // Récupérer les données d'humidité
    
    Serial.println("----------------");
    Serial.println("Affichage Hum :");
    Serial.println(value.humidity);
    
    int humidityValue = int(value.humidity); // Convertir l'humidité en entier
    return humidityValue; // Retourner l'humidité
}
