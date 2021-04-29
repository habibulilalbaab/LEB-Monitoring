#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "LEB-Monitoring"
#define STAPSK  "12345678"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

void setup(void) {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  IPAddress ip(192,168,5,5);   
  IPAddress gateway(192,168,5,1);   
  IPAddress subnet(255,255,255,0);   
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", []() {
    server.send(200, "text/html", "<center><h1>LEB-Monitoring</h1><br><a href='/api/percentage'>Battery Percentage</a><br><a href='/api/voltage'>Battery Voltage</a><br><a href='/api/status'>Battery Status</a><br><a href='/api/level'>Battery Level</a><br><br><div>powered by <a href='https://github.com/habibulilalbaab/LEB-Monitoring'>LEB-Monitoring<a></div></center>");
  });

  server.on("/api/percentage", []() {
    server.send(200, "text/plain", "100");
  });
  server.on("/api/voltage", []() {
    server.send(200, "text/plain", "11.6");
  });
  server.on("/api/status", []() {
    server.send(200, "text/plain", "GOOD");
  });
  server.on("/api/level", []() {
    server.send(200, "text/plain", "1");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
