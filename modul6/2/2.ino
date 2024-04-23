#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const int ledPin = 2; 
bool ledState = LOW; 

// Inisialisasi koneksi WiFi
char ssid[] = "akubisa"; // Nama WiFi Anda
char password[] = "pastibisa"; // Kata sandi WiFi Anda

// Inisialisasi BOT Telegram
#define BOTtoken "6510963302:AAGvQ3zWkTxrot4OD2cfhGuwGngiMF2psZs"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Periksa pesan baru setiap 1 detik
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
  
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    
    if (from_name == "") from_name = "Guest";
    
    // Cek pembacaan sensor DHT11
    if (text == "/statussuhu") {
      int t = dht.readTemperature();
      String temp = "Suhu saat ini: " + String(t) + " *C\n";
      bot.sendMessage(chat_id, temp, "");
    }
    if (text == "/statuskelembapan") {
      int h = dht.readHumidity();
      String humidity = "Kelembaban: " + String(h) + " %\n";
      bot.sendMessage(chat_id, humidity, "");
    }
    
    // Perintah untuk setiap aksi
    if (text == "/start") {
      String welcome = "Selamat datang, " + from_name + ".\n";
      welcome += "/statussuhu : Status Suhu\n";
      welcome += "/statuskelembapan : Status Kelembapan\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
    if (text == "/ledon") {
  bot.sendMessage(chat_id, "LED dinyalakan", "");
  ledState = HIGH;
  digitalWrite(ledPin, ledState);
}

if (text == "/ledoff") {
  bot.sendMessage(chat_id, "LED dimatikan", "");
  ledState = LOW;
  digitalWrite(ledPin, ledState);
}

if (text == "/statusLED") {
  if (digitalRead(ledPin)) {
    bot.sendMessage(chat_id, "LED menyala", "");
  } else {
    bot.sendMessage(chat_id, "LED mati", "");
  }
}

// Cek Command untuk setiap aksi
if (text == "/start") {
  String welcome = "Selamat datang, " + from_name + ".\n";
  welcome += "/statussuhu : Status Suhu\n";
  welcome += "/statuskelembapan : Status Kelembapan\n";
  welcome += "Gunakan perintah berikut untuk LED:\n";
  welcome += "/ledon untuk menghidupkan LED\n";
  welcome += "/ledoff untuk mematikan LED\n";
  welcome += "/statusLED untuk mengetahui kondisi LED\n";
  bot.sendMessage(chat_id, welcome, "Markdown");
}

  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, ledState); 

  
  // Konfigurasi koneksi WiFi
  client.setInsecure();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);
  
  // Mencoba terhubung ke jaringan WiFi
  Serial.print("Menghubungkan ke WiFi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.println("Terhubung ke WiFi");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int t = dht.readTemperature();
  int h = dht.readHumidity();
  
  if (millis() > lastTimeBotRan + botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    
    while (numNewMessages) {
      Serial.println("Menerima respons");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    
    lastTimeBotRan = millis();
  }
  
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print(" Celcius Kelembaban: ");
  Serial.println(h);
  
  delay(3000);
}
