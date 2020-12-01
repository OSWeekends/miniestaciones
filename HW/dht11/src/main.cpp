#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <NTPClient.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>


#include "secrets.h"

const String SENSOR_ID = "hermes001";

WiFiUDP ntpUDP;   // UDP client
NTPClient timeClient(ntpUDP); // NTP client

// #define DONT_HAVE_SENSORS

// Feather ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.
#define DHTPIN D3    // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#define BAUDRATE	115200

struct readings {
  bool gas;
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

// will store last time data was sent to Firebase
unsigned long previousMillis = 0;
const long INTERVAL = 30000;
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
  // check to see if it's time to send data to Firebase; that is, if the difference
  // between the current time and last time we sent data is bigger than
  // the interval at which we want to send data.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    // save the last time we sent data to Fireabase
    previousMillis = currentMillis;
    readSensors(&readings);
    displaySensors(readings);
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
    readings.temp = random(0, 80);
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

void displaySensors(struct readings r) {
  if (r.gas == true) {
    Serial.println("[INFO] Gas DETECTED!!!");
  }
  Serial.print("[INFO] Gas status: ");
  Serial.println(r.gas);
  Serial.print("[INFO] Humidity: ");
  Serial.print(r.hum);
  Serial.println("%");
  Serial.print("[INFO] Temperature: ");
  Serial.print(r.temp);
  Serial.print("°C ");
  Serial.println();
  
}

void sendDataToFirebase(struct readings r) {
  timeClient.update();
  timestamp = timeClient.getEpochTime();
  
  const size_t capacity = JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(capacity);
  JsonObject& object1 = jsonBuffer.createObject();

  object1["timestamp"] = timestamp;
  object1["temp"] = r.temp;
  object1["hum"] = r.hum;
  object1["gas"] = r.gas;

  Serial.print("Data:");
  object1.printTo(Serial);
  Serial.println();

  String requestStatusID = Firebase.push(SENSOR_ID, object1);
  if (Firebase.failed()) {
    Serial.println("[ERROR] pushing data failed:");
    Serial.println(Firebase.error());
    return;
  }

  // String humValueID = Firebase.pushFloat(SENSOR_ID + String("/json"), r.temp);
  // if (Firebase.failed()) {
  //   Serial.print("[ERROR] pushing /json failed:");
  //   Serial.println(Firebase.error());
  //   return;
  // }
  // String tempValueID = Firebase.pushFloat(SENSOR_ID + String("/dht11/temperature"), r.temp);
  // if (Firebase.failed()) {
  //   Serial.print("[ERROR] pushing /dht11/temperature failed:");
  //   Serial.println(Firebase.error());
  //   return;
  // }
}
