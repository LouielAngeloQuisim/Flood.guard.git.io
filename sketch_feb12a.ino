#include <WiFiS3.h>

#define sensorPin A0  // Adjusted for Arduino UNO R4 WiFi

// WiFi credentials
const char* ssid = "HUAWEI-2.4G-E62q";      // Replace with your WiFi SSID
const char* password = "Rocky0124!";          // Replace with your WiFi Password

// Use your computer's IP address (from which XAMPP is running)
char server[] = "https://louielangeloquisim.github.io/Flood.guard.git.io/"; // "https://louielangeloquisim.github.io/Flood.guard.git.io/" if live server
// Define the path to your PHP script
String path = "post.php"; //post.php if live server

// SET WIFI CLIENT
WiFiClient client;

const int analogInPin = A0;
int sensorValue = 0;

void setup() {
  // Declare pins to be outputs:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);

  // Attempt to connect to WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to network named: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    delay(1000);
  }
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  sensorValue = analogRead(analogInPin);
  Serial.print("sensor = ");
  Serial.println(sensorValue);
  delay(100);

  if ((sensorValue >= 100) && (sensorValue <= 600)) {
    digitalWrite(2, HIGH);
    sendDataToWebsite("HIGH");
    delay(100);
  } else if ((sensorValue >= 601) && (sensorValue <= 625)) {
    digitalWrite(3, HIGH);
    sendDataToWebsite("HIGH");
    delay(100);
  } else if ((sensorValue >= 626) && (sensorValue <= 700)) {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    sendDataToWebsite("HIGH");
    delay(100);
  } else {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    sendDataToWebsite("LOW");
    delay(100);
  }
}

void sendDataToWebsite(String data) {
  String postData = "alert=True";
  WiFiClient clientLocal;  // New instance for each request
  bool connected = clientLocal.connect(server, 80);
  
  if (connected) {
    // Send the POST request
    clientLocal.print("POST ");
    clientLocal.print(path);
    clientLocal.println(" HTTP/1.1");
    clientLocal.print("Host: ");
    clientLocal.println(server);
    clientLocal.println("Content-Type: application/x-www-form-urlencoded");
    clientLocal.print("Content-Length: ");
    clientLocal.println(postData.length());
    clientLocal.println();
    clientLocal.print(postData);
    clientLocal.stop();
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Connection to server failed");
  }
  
  Serial.print("Data sent: ");
  Serial.println(data);
  Serial.print("Endpoint: ");
  Serial.println(String(server) + path);
  Serial.print("Connection attempt result: ");
  Serial.println(connected ? "Success" : "Failed");

}

