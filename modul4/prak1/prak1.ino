#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <ESP8266WiFi.h> // Menggunakan ESP8266WiFi untuk modul ESP8266
#include <ThingSpeak.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define CHANNEL_ID  2269586
#define CHANNEL_API_KEY "ID273PYY0MRBJ709"

const char* ssid = "akubisa";
const char* password = "pastibisa";
const char* server = "api.thingspeak.com";
WiFiClient client;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4
#define DHTTYPE    DHT22

DHT dht(DHTPIN, DHTTYPE);

#define BUZZER_PIN 2

float tempThreshold = 31.0;
float humThreshold = 75.0;

void setup() {
  Serial.begin(115200);
  Serial.println("Deteksi Suhu dan kelembaban");
  dht.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  ThingSpeak.begin(client);
}

void loop() {
  delay(1000);

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (client.connect(server, 80)) {
    ThingSpeak.setField(1, t);
    ThingSpeak.setField(2, h);
    int x = ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);
    if (x == 200) {
      Serial.println("Channel update successful.");
    } else {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.println("% send to Thingspeak");

    if (t >= tempThreshold || h >= humThreshold) {
      digitalWrite(BUZZER_PIN, HIGH);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.print("Status: ALERT");
      display.setTextSize(1);
      display.setCursor(0, 20);
      display.print("Temp: ");
      display.print(t);
      display.write(167);
      display.print("C");
      display.setTextSize(1);
      display.setCursor(0, 40);
      display.print("Humidity: ");
      display.print(h);
      display.print(" %");
      display.display();
    } else {
      digitalWrite(BUZZER_PIN, LOW);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.print("Status: SAFE");
      display.setTextSize(1);
      display.setCursor(0, 20);
      display.print("Temp: ");
      display.print(t);
      display.write(167);
      display.print("C");
      display.setTextSize(1);
      display.setCursor(0, 40);
      display.print("Humidity: ");
      display.print(h);
      display.print(" %");
      display.display();
    }
    client.stop();
    Serial.println("Waiting…");
    delay(20000);
  }
}
