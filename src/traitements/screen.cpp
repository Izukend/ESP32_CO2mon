/**
 * @file screen.cpp
 * @brief Gestion de l'écran OLED
 * @date 2024-04-05
 * @author Matthieu et Tom
 */

#include "../../include/screen.h" // Inclure les bibliothèques nécessaires

SSD1306Wire display(0x3c, SDA, SCL); // Créer une instance d'écran OLED avec l'adresse 0x3c

/**
 * @brief Fonction d'initialisation de l'écran OLED
 * 
 * Cette fonction initialise l'écran OLED en configurant l'affichage avec un texte centré
 * indiquant l'adresse IP à entrer dans le navigateur web.
 */
void oledInit(){
    // Initialiser l'écran OLED
    display.init();
    display.setTextAlignment(TEXT_ALIGN_CENTER); // Alignement du texte au centre
    display.setFont(ArialMT_Plain_10); // Utiliser la police ArialMT en taille 10

    // Afficher le texte sur l'écran OLED
    display.drawString(64, 16, "Rentrer sur navigateur web :");
    display.drawString(64, 48, "192.168.4.1");
    display.display(); // Mettre à jour l'affichage
}

/**
 * @brief Fonction pour effacer l'écran OLED
 * 
 * Cette fonction efface le contenu actuel de l'écran OLED.
 */
void oledErase(){
    display.clear(); // Effacer l'écran OLED
    display.display(); // Mettre à jour l'affichage pour appliquer les modifications
}

/**
 * @brief Affiche les données de CO2 sur l'écran OLED.
 * 
 * Cette fonction initialise la communication série avec le capteur MH-Z19, récupère les données
 * de CO2 depuis le capteur, les convertit en chaîne de caractères et les affiche sur l'écran OLED.
 */
void oledPrintData() {
    // Initialiser la communication série avec le capteur MH-Z19
    mySerial.begin(9600);
    // Initialiser le capteur MH-Z19
    myMHZ19.begin(mySerial);

    // Attendre 3 secondes pour permettre au capteur de s'initialiser
    delay(2000);

    // Récupérer les données brutes de CO2 depuis le capteur MH-Z19
    double adjustedCO2 = myMHZ19.getCO2();
    // Convertir les données de CO2 en chaîne de caractères
    String strCO2 = String(adjustedCO2);
    // Effacer l'écran OLED pour une nouvelle mise à jour
    display.clear();

    // Afficher les données de CO2 en haut de l'écran OLED
    display.drawString(64, 16, "CO2: " + strCO2);

    // Mettre à jour l'affichage sur l'écran OLED
    display.display();
}
