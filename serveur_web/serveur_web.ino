#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

const char* ssid = "VotreSSID";
const char* password = "VotreMotDePasse";

WebServer server(80);

void handleRoot() {
  // Charge le contenu de la première page à partir du fichier HTML
  File file = SPIFFS.open("/page1.html", "r");
  if (!file) {
    Serial.println("Erreur lors de l'ouverture du fichier page1.html");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handlePage2() {
  // Charge le contenu de la deuxième page à partir du fichier HTML
  File file = SPIFFS.open("/page2.html", "r");
  if (!file) {
    Serial.println("Erreur lors de l'ouverture du fichier page2.html");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void setup() {
  Serial.begin(115200);

  // Connexion au réseau WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi en cours...");
  }
  Serial.println("Connecté au WiFi");

  // Initialisation du système de fichiers SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Erreur d'initialisation du SPIFFS");
    return;
  }

  // Définition des gestionnaires d'URL
  server.on("/", handleRoot);
  server.on("/page2", handlePage2);

  // Démarrage du serveur
  server.begin();
  Serial.println("Serveur démarré");
}

void loop() {
  server.handleClient();
}
