#include <Arduino.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DHT.h>

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

const char* ssid = "ciclope12";
const char* password = "almaciga1275c";
float temperature;
  float humidity;
WebServer server(80);

DHT dht(DHTPIN, DHTTYPE);
void handleRoot() {

  char temp[400];
  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
   float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

    Serial.print( "T = " );
    Serial.print( t, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( h, 1 );
    Serial.println( "%" );



    snprintf(temp, 400, "<html>\
    <head>\
      <meta http-equiv='refresh' content='5'/>\
      <title>ESP32 Demo</title>\
      <style>\
        body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      </style>\
    </head>\
    <body>\
      <h1>DHT from ESP32!</h1>\
      <p>Humidity: %.2f  Temperature:%.2f</p>\
    </body> \
  </html>",  h,t);
  server.send(200, "text/html", temp);

}

void handleNotFound() {
  server.send(404,"text/plain", "File Not Found\n\n");

}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
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

  if (MDNS.begin("esp32")) {
    Serial.println(F("MDNS responder started"));
  }
dht.begin();
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);


server.begin();
  Serial.println(F("HTTP server started"));

}

void loop() {
 server.handleClient();



}
