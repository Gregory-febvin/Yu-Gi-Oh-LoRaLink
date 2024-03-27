#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>  // Include the SPIFFS library

const char* ssid = "Yu-Gi-Oh! LoRaLink";     // Name of the access point
const char* password = "Nice-Cock";  // Password for the access point

ESP8266WebServer server(80); // Create a webserver object that listens on port 80

void setup() {
  Serial.begin(115200);
  delay(100);

  // Initialize the access point
  WiFi.softAP(ssid, password);

  // Print IP address of the access point
  Serial.println();
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());

  // Mount SPIFFS filesystem
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  // List files in SPIFFS (for debugging)
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    Serial.print("FILE: ");
    Serial.println(dir.fileName());
  }

  // Route for root / web page
  server.on("/", HTTP_GET, handleRoot);

  // Start the server
  server.begin();
}

void loop() {
  server.handleClient(); // Handle client requests
}

// Handle root / web page
void handleRoot() {
  // Open the index.html file
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    Serial.println("Failed to open file");
    return;
  }

  // Set content type
  server.streamFile(file, "text/html");

  // Close the file
  file.close();
}
