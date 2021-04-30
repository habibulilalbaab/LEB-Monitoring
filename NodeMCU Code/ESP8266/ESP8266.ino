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

int analogInput = A0;
int val = 0;
int percentageBatt = 0;
int percentagePrint = 0;
float Vout = 0.00;
float Vin = 0.00;
float R1 = 10000.00; // resistance of R1 (10K) 
float R2 = 1000.00; // resistance of R2 (1K)
float tmpVoltage = 0.00;
String level = "0";

ESP8266WebServer server(80);
//voltage
float vin() {
  val = analogRead(analogInput);//reads the analog input
  Vout = (val * 3.30) / 1024.00; // formula for calculating voltage out i.e. V+, here 3.30 base on ADC Voltage NodeMCU ESP8266 and 10% decrease for adjust (3.00)
  Vin = Vout / (R2/(R1+R2)); // formula for calculating voltage in i.e. GND
  return Vin;
}
float voltage() {
  if(tmpVoltage == 0.00){
    tmpVoltage = vin();
  }
  if(tmpVoltage > vin()){
    tmpVoltage = vin();
  }
  if(tmpVoltage > vin()+0.20){
    tmpVoltage = vin();
  }
  return tmpVoltage;
}
//percentage
float percentage() {
  percentageBatt = (voltage()-9.00)/3.6*100; // 9.00v is minimum voltage 3S battery, 3.6 is subtraction max voltage to min voltage, in this case (12.60-9.00)
  if(percentageBatt > 100.00){
    percentageBatt = 100.00;
  }
  return percentageBatt;
}
//print voltage
void batteryVoltage() {
  server.send(200, "text/plain", String(voltage()));
}
//print percentage
void batteryPercentage() {
  percentagePrint = int(percentage());
  server.send(200, "text/plain", String(percentagePrint));
}
//print batt level
void batteryLevel() {
  percentagePrint = int(percentage());
  if(percentagePrint >= 80){
    level = "1";  
  }else if(percentagePrint >= 60 && percentagePrint < 80){
    level = "2";  
  }else if(percentagePrint >= 40 && percentagePrint < 60){
    level = "3";  
  }else if(percentagePrint >= 20 && percentagePrint < 40){
    level = "4";  
  }else{
    level = "0";
  }
  server.send(200, "text/plain", level);
}
//print status batt
void statusBattery() {
  percentagePrint = int(percentage());
  if(percentagePrint >= 80){
    server.send(200, "text/plain", "Good Battery");
  }else if(percentagePrint >= 60 && percentagePrint < 80){
    server.send(200, "text/plain", "Normal Battery");
  }else if(percentagePrint >= 40 && percentagePrint < 60){
    server.send(200, "text/plain", "Low Battery");
  }else if(percentagePrint >= 20 && percentagePrint < 40){
    server.send(200, "text/plain", "Critical Battery");
  }
}

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

  server.on("/api/percentage", batteryPercentage);
  server.on("/api/voltage", batteryVoltage);
  server.on("/api/status", statusBattery);
  server.on("/api/level", batteryLevel);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  Serial.println(voltage());
  MDNS.update();
}
