#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <NTPClient.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>

// You need to include secrets.h with confidential data
#include "secrets.h"

const String SENSOR_ID = "hermes001";
const long INTERVAL = 60000; // miliseconds

WiFiUDP ntpUDP;   // UDP client
NTPClient timeClient(ntpUDP); // NTP client

// #define DONT_HAVE_SENSORS
#define DEBUG

// Feather ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.
#define DHTPIN D3    // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#define BAUDRATE	115200

struct readings {
  bool gas;           // MQ-5 or similar sensor threshold
  float hum;  				// Humidity in Percent	  ( %)
  float temp;  				// Temperature in Celsius (°C)
} readings;


// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
// will store last time data was sent to Firebase
long unsigned int timestamp = 0;

// Defs.
void connectToWiFi(char const *ssid, char const *password);
void readSensors(struct readings *r);
void displaySensors(struct readings r);
void sendDataToFirebase(struct readings r);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(BAUDRATE);
  connectToWiFi(SSID, PASSWORD);

  timeClient.begin(); // init NTP
  timeClient.setTimeOffset(0); // 0= GMT, 3600 = GMT+1
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();
    
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    previousMillis = currentMillis;
    readSensors(&readings);
    sendDataToFirebase(readings);
  }
}

void connectToWiFi(char const *ssid, char const *password) {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
  would try to act as both a client and an access-point and could cause
  network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

 //start connecting to WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // timestamp
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // get Epoch time
  Serial.print("> NTP Time:");
  Serial.println(timeClient.getFormattedTime());
  // save the current NTP time
  timestamp = timeClient.getEpochTime();

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void readSensors(struct readings *r) {
  #ifdef DONT_HAVE_SENSORS
    readings.gas = !readings.gas;
    readings.temp = random(0, 50);
    readings.hum = random(0, 80);
  #else
    // Read Gas status
    r->gas = true;
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    r->hum = dht.readHumidity();
    // Read temperature as Celsius (the default)
    r->temp = dht.readTemperature();
    // Check if any reads failed and exit early (to try again).
    if (isnan(r->hum) || isnan(r->temp)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
  #endif
}

void displaySensors(JsonObject& obj) {
  Serial.print("Data:");
  obj.printTo(Serial);
  Serial.println();
}

void sendDataToFirebase(struct readings r) {
  timeClient.update();
  // Get NTP time data to Fireabase
  timestamp = timeClient.getEpochTime();
  
  const size_t capacity = JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(capacity);
  JsonObject& object1 = jsonBuffer.createObject();

  object1["timestamp"] = timestamp;
  object1["temp"] = r.temp;
  object1["hum"] = r.hum;
  object1["gas"] = r.gas;

  #ifdef DEBUG
    displaySensors(object1);
  #endif
  
  String requestStatusID = Firebase.push(SENSOR_ID, object1);
  if (Firebase.failed()) {
    Serial.println("[ERROR] pushing data failed:");
    Serial.println(Firebase.error());
    return;
  }
}
