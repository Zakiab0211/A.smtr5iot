#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT22

//Tambahan utk OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

#include "ThingSpeak.h"  //header utk thingspeak

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Setting untuk WiFi
// ganti dengan API Keys anda di Thingspeak
#define CHANNEL_ID  2269586
#define CHANNEL_API_KEY "ID273PYY0MRBJ709"

const char* ssid = "akubisa";  //masukkan dari tethering hp anda 
const char* password = "pastibisa";  
const char* server = "api.thingspeak.com";
WiFiClient client;

DHT dht(DHTPIN, DHTTYPE);
void setup() {  //Serial.begin(9600);
  Serial.begin(115200);
  Serial.println("Deteksi Suhu dan kelembaban");
  dht.begin();  //Tambahan utk OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(500);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  //Initial WiFi
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  ThingSpeak.begin(client);  // Initialize ThingSpeak
}
void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Sensor tidak terbaca!");
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

    //Tambahan utk OLED     
    display.clearDisplay();
    display.setCursor(0, 0);      
    display.println("Monitoring Suhu\n");     
    display.print("Hum: ");      
    display.print(h);      
    display.println(" %");     
    display.print("Temp: ");      
    display.print(t);      
    display.println(" *C");     
    display.display();
  }
  client.stop();
  Serial.println("Waiting…");
  delay(20000);
}
