// #include <WiFi.h>
// #include <WiFiClientSecure.h>
// #include <UniversalTelegramBot.h>
// #include "DHT.h"

// #define DHTPIN 4
// #define DHTTYPE DHT22

// DHT dht(DHTPIN, DHTTYPE);

// // Inisialisasi koneksi WiFi
// char ssid[] = "akubisa"; // Nama WiFi Anda
// char password[] = "pastibisa"; // Kata sandi WiFi Anda

// // Inisialisasi BOT Telegram
// #define BOTtoken "6510963302:AAGvQ3zWkTxrot4OD2cfhGuwGngiMF2psZs"

// WiFiClientSecure client;
// UniversalTelegramBot bot(BOTtoken, client);

// // Chat ID untuk tujuan notifikasi
// // Ganti dengan chat ID yang sesuai
// String chat_id = "6264528974";

// // Periksa pesan baru setiap 1 detik
// int botRequestDelay = 1000;
// unsigned long lastTimeBotRan;

// void handleNewMessages(int numNewMessages) {
//   Serial.println("handleNewMessages");
//   Serial.println(String(numNewMessages));
  
//   for (int i = 0; i < numNewMessages; i++) {
//     String chat_id = String(bot.messages[i].chat_id);
//     String text = bot.messages[i].text;
//     String from_name = bot.messages[i].from_name;
    
//     if (from_name == "") from_name = "Guest";
    
//     // Cek pembacaan sensor DHT11
//     if (text == "/statussuhu") {
//       int t = dht.readTemperature();
//       String temp = "Suhu saat ini: " + String(t) + " *C\n";
//       bot.sendMessage(chat_id, temp, "");
//     }
//     if (text == "/statuskelembapan") {
//       int h = dht.readHumidity();
//       String humidity = "Kelembaban: " + String(h) + " %\n";
//       bot.sendMessage(chat_id, humidity, "");
//     }
    
//     // Perintah untuk setiap aksi
//     if (text == "/start") {
//       String welcome = "Selamat datang, " + from_name + ".\n";
//       welcome += "/statussuhu : Status Suhu\n";
//       welcome += "/statuskelembapan : Status Kelembapan\n";
//       bot.sendMessage(chat_id, welcome, "Markdown");
//     }
//   }
// }

// void setup() {
//   Serial.begin(115200);
//   dht.begin();
  
//   // Konfigurasi koneksi WiFi
//   client.setInsecure();
//   WiFi.mode(WIFI_STA);
//   WiFi.disconnect();
//   delay(500);
  
//   // Mencoba terhubung ke jaringan WiFi
//   Serial.print("Menghubungkan ke WiFi: ");
//   Serial.println(ssid);
  
//   WiFi.begin(ssid, password);
  
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.print(".");
//     delay(500);
//   }
  
//   Serial.println("");
//   Serial.println("Terhubung ke WiFi");
//   Serial.print("Alamat IP: ");
//   Serial.println(WiFi.localIP());
// }

// void loop() {
//   int t = dht.readTemperature();
//   int h = dht.readHumidity();
  
//   if (millis() > lastTimeBotRan + botRequestDelay) {
//     int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    
//     while (numNewMessages) {
//       Serial.println("Menerima respons");
//       handleNewMessages(numNewMessages);
//       numNewMessages = bot.getUpdates(bot.last_message_received + 1);
//     }
    
//     lastTimeBotRan = millis();
//   }
  
//   if (t > 30) {
//     bot.sendMessage(chat_id, "Peringatan: Suhu melebihi 30°C!", "");
//   }
  
//   if (h > 55) {
//     bot.sendMessage(chat_id, "Peringatan: Kelembaban melebihi 56%!", "");
//   }

//   Serial.print("Suhu: ");
//   Serial.print(t);
//   Serial.print(" Celcius Kelembaban: ");
//   Serial.println(h);
  
//   delay(3000);
// }


#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi koneksi WiFi
char ssid[] = "akubisa"; // Nama WiFi Anda
char password[] = "pastibisa"; // Kata sandi WiFi Anda

// Inisialisasi BOT Telegram
#define BOTtoken "6510963302:AAGvQ3zWkTxrot4OD2cfhGuwGngiMF2psZs"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Chat ID untuk tujuan notifikasi
// Ganti dengan chat ID yang sesuai
String chat_id = "6264528974";

// Periksa pesan baru setiap 1 detik
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
bool isBotStopped = false; // Tambahkan variabel status

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
  
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    
    if (from_name == "") from_name = "Guest";
    
    if (text == "/start") {
      String welcome = "Selamat datang, " + from_name + ".\n";
      welcome += "/statussuhu : Status Suhu\n";
      welcome += "/statuskelembapan : Status Kelembapan\n";
      welcome += "/stop : Berhenti menerima pesan\n"; // Tambahkan perintah stop
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
    
    if (text == "/stop") {
      isBotStopped = true; // Set status bot menjadi "stop"
      bot.sendMessage(chat_id, "Bot berhenti menerima pesan. Ketik /start untuk memulai kembali.", "");
    }
    
    // Cek apakah bot dalam mode "start" atau "stop"
    if (!isBotStopped) {
      // Cek pembacaan sensor DHT22 hanya jika bot dalam mode "start"
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
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  
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
  
  if (!isBotStopped) { // Hanya periksa kondisi suhu dan kelembaban jika bot dalam mode "start"
    if (t > 30) {
      bot.sendMessage(chat_id, "Peringatan: Suhu melebihi 30°C!", "");
    }
    
    if (h > 55) {
      bot.sendMessage(chat_id, "Peringatan: Kelembaban melebihi 55%!", "");
    }
  }

  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print(" Celcius Kelembaban: ");
  Serial.println(h);
  
  delay(5000);
}
