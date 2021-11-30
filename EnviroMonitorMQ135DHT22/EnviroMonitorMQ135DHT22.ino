#include <MQ135.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define PIN_MQ135 A0 // MQ135 Analog Input Pin
#define DHTPIN 2 // DHT Digital Input Pin
#define DHTTYPE DHT22 // DHT11 or DHT22, depends on your sensor
#define SERVER_IP ":5000"

// Wifi credentials
const char* ssid = "";
const char* password = "";

MQ135 mq135_sensor(PIN_MQ135);
DHT dht(DHTPIN, DHTTYPE);

float temperature, humidity; // Temp and Humid floats, will be measured by the DHT

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Wifi Connected! IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
}

void loop() {
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;
    //================
    //Reading sensors
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

  
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    float rzero = mq135_sensor.getRZero();
//    Serial.print("rzero:");
//    Serial.print(rzero);
    float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
    float resistance = mq135_sensor.getResistance();
    float ppm = mq135_sensor.getPPM();
    float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);

    //=================

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" SERVER_IP "/environment_readings/"); //HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body

//    char msg[] = "";
//    sprintf(msg, "{\"rZero\":\"%s\",\"correctedRZero\":\"%s\"}", rzero, correctedRZero);
//    Serial.print(msg);
//    Serial.print(rzero);
//    Serial.print(correctedRZero);
    String data  = "{\"rZero\":\"" + String(rzero) + "\"";
    data += ",\"correctedRZero\":\"" + String(correctedRZero) + "\"";
    data += ",\"resistance\":\"" + String(resistance) + "\"";
    data += ",\"ppm\":\"" + String(ppm) + "\"";
    data += ",\"temperature\":\"" + String(temperature) + "\"";
    data += ",\"humidity\":\"" + String(humidity) + "\"";
    data += "}";
    int httpCode = http.POST(data);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(100000);





//  Serial.print("MQ135 RZero: ");
//  Serial.print(rzero);
//  Serial.print("\t Corrected RZero: ");
//  Serial.print(correctedRZero);
//  Serial.print("\t Resistance: ");
//  Serial.print(resistance);
//  Serial.print("\t PPM: ");
//  Serial.print(ppm);
//  Serial.print("ppm");
//  Serial.print("\t Corrected PPM: ");
//  Serial.print(correctedPPM);
//  Serial.println("ppm");
//  float t = dht.readTemperature();
//  Serial.print("\t Temperature: ");
//  Serial.print(t);
//  Serial.print("\t Humidity: ");
//  Serial.print(humidity);
//  //https://www.kane.co.uk/knowledge-centre/what-are-safe-levels-of-co-and-co2-in-rooms
//  if (ppm < 400) {
//    Serial.println("CO2: Normal background concentration in outdoor ambient air");
//  }
//  else if (ppm > 400 && ppm <= 1000) {
//    Serial.println(" CO2: Concentrations typical of occupied indoor spaces with good air exchange");
//  }
//  else {
//    Serial.println("CO2: Complaints of drowsiness and poor air.");
//  }
//  Serial.println(ppm);
//
//
//  delay(3000);
}
