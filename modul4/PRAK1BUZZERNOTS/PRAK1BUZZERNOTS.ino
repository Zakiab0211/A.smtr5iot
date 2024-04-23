#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4     // Digital pin connected to the DHT sensor

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT11     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

#define BUZZER_PIN 2 // Pin buzzer yang digunakan

float tempThreshold = 31.0;   // Threshold suhu
float humThreshold = 75.0;    // Threshold kelembaban

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // Matikan buzzer

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  delay(1000);

  // Baca suhu dan kelembaban
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Periksa apakah suhu atau kelembaban melewati threshold
  if (t >= tempThreshold || h >= humThreshold) {
    digitalWrite(BUZZER_PIN, HIGH); // Aktifkan buzzer
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
    digitalWrite(BUZZER_PIN, LOW); // Matikan buzzer
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
}
