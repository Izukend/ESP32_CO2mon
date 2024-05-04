/**
 * @file main.h
 * @date 2024-04-05
 * @author Tom
 */

#include "../include/screen.h"
#include "../include/wifi_and_mqtt.h"
#include "../include/frame_and_data.h"

const char Home[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Conf APWIFI</title>
  <link rel="stylesheet" href="styles.css">
  <style>
    body {
        background-color: #1c1c1c;
  margin: 0;
  font-family: Arial, sans-serif;
}

header {
  background-color: #212121 ;
  width: 100%;
}

nav {
  max-width: 1200px;
  margin: 0 auto;
  display: flex;
  justify-content: center;
  align-items: center;
  padding: 10px 0;
}

.logo {
  width: 55px;
  height: 55px;
}

.main-content {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.text {
  color: white;
  text-align: left;
}

.article {
  margin-bottom: 20px;
  background-color: #2E2E2E;
  padding-left: 5%;
  padding-right: 5%;
  padding-top: 2%;
  padding-bottom: 2%;
  border-radius: 10px;
}

form {
  display: flex;
  flex-direction: column;
  align-items: center;
  text-align: center;
}

input[type="text"] {
  margin-top: 10px;
  margin-bottom: 5px;
  border-radius: 5px;
  padding-right: 50%;
  padding-top: 5%;
  width: 100%;
  border: none;
}

input[type="submit"] {
  margin-top: 10%;
  padding: 5%;
  padding-right: 20%;
  padding-left: 20%;
  border-radius: 5px;
}

.input-container {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.button {
  border: none;
  background-color: #787878;
  color: white;
  font-weight: bold;
}

@media screen and (max-width: 600px) {
  .article {
    padding-left: 20%;
    padding-right: 20%;
    padding-top: 5%;
  }
  input[type="text"],
  input[type="submit"] {
    margin-top: 5px;
    margin-bottom: 3px;
  }
  input[type="submit"] {
    margin-top: 10%;
  }
}

  </style>
</head>
<body>
    <header>
        <nav>
            <img class="logo" src="images/CO2logo.png" alt="Logo">
        </nav>
    </header>
  <main class="main-content">
    <h1 class="text">System configuration</h1>
    <article class="article">
      <form action="/submit" method="POST">
        <div class="input-container">
          <label class="text">ESP32 Name</label>
          <input type="text" id="input" name="name"/>
        </div>
        <div class="input-container">
          <label class="text">WIFI SSID</label>
          <input type="text" id="input" name="name_wifi"/>
        </div>
        <div class="input-container">
          <label class="text">WIFI Password</label>
          <input type="text" id="input" name="pass"/>
        </div>
    </article>
    <h1 class="text">MQTT configuration</h1>
    <article class="article">
        <div class="input-container">
          <label class="text">MQTT Server</label>
          <input type="text" id="input" name="server"/>
        </div>
        <div class="input-container">
          <label class="text">MQTT User</label>
          <input type="text" id="input" name="user"/>
        </div>
        <div class="input-container">
          <label class="text">MQTT Password</label>
          <input type="text" id="input" name="pass_mqtt"/>
        </div>
        <input class="button" type="submit" value="Send" style="width: 100%;"/> <!-- Ajouter un style inline pour forcer la largeur à 100% -->
      </form>
    </article>
  </main>
</body>
</html>

)=====";