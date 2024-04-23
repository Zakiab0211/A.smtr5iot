// #include <WiFi.h>
// #include <WiFiClientSecure.h>
// #include <UniversalTelegramBot.h>
// #include <DHT.h>

// #define DHTPIN 4
// #define DHTTYPE DHT22

// DHT dht(DHTPIN, DHTTYPE);

// // WiFi connection configuration
// char ssid[] = "akubisa"; // Your WiFi network name
// char password[] = "pastibisa"; // Your WiFi password

// // Telegram Bot initialization
// #define BOTtoken "6510963302:AAGvQ3zWkTxrot4OD2cfhGuwGngiMF2psZs"
// WiFiClientSecure client;
// UniversalTelegramBot bot(BOTtoken, client);

// // Chat ID for notifications
// // Replace with your appropriate chat ID
// String chat_id = "6264528974";

// // Periksa pesan baru setiap 1 detik
// int botRequestDelay = 1000;
// unsigned long lastTimeBotRan;
// bool isBotStopped = false; // Add status variable

// // Daily humidity data
// int kelembaban[] = {50, 53, 51, 56, 58};
// int jumlahSampel = 5;

// // Notification threshold
// int threshold = 55;

// void handleNewMessages(int numNewMessages) {
//   Serial.println("handleNewMessages");
//   Serial.println(String(numNewMessages));
  
//   for (int i = 0; i < numNewMessages; i++) {
//     String chat_id = String(bot.messages[i].chat_id);
//     String text = bot.messages[i].text;
//     String from_name = bot.messages[i].from_name;
    
//     if (from_name == "") from_name = "Guest";
    
//     if (text == "/start") {
//       String welcome = "Selamat datang, " + from_name + ".\n";
//       welcome += "/status_temperature: Status Suhu\n";
//       welcome += "/status_humidity: Status Kelembapan\n";
//       welcome += "/stop: Berhenti menerima pesan\n"; // Tambahkan perintah stop
//       bot.sendMessage(chat_id, welcome, "Markdown");
//     }
    
//     if (text == "/stop") {
//       isBotStopped = true; // Set status bot menjadi "stop"
//       bot.sendMessage(chat_id, "Bot berhenti menerima pesan. Ketik /start untuk memulai kembali.", "");
//     }
    
//     // Cek apakah bot dalam mode "start" atau "stop"
//     if (!isBotStopped) {
//       // Cek pembacaan sensor DHT22 hanya jika bot dalam mode "start"
//       if (text == "/status_temperature") {
//         float t = dht.readTemperature();
//         String temp = "Suhu saat ini: " + String(t) + " °C\n";
//         bot.sendMessage(chat_id, temp, "");
//       }
      
//       if (text == "/status_humidity") {
//         float h = dht.readHumidity();
//         String humidity = "Kelembaban: " + String(h) + " %\n";
//         bot.sendMessage(chat_id, humidity, "");
//       }
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
//   float t = dht.readTemperature();
//   float h = dht.readHumidity();
  
//   if (millis() > lastTimeBotRan + botRequestDelay) {
//     int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    
//     while (numNewMessages) {
//       Serial.println("Menerima respons");
//       handleNewMessages(numNewMessages);
//       numNewMessages = bot.getUpdates(bot.last_message_received + 1);
//     }
    
//     lastTimeBotRan = millis();
//   }
  
//   if (!isBotStopped) { // Hanya periksa kondisi suhu dan kelembaban jika bot dalam mode "start"
//     if (t > 30) {
//       bot.sendMessage(chat_id, "Peringatan: Suhu melebihi 30°C!", "");
//     }
    
//     if (h > 55) {
//       bot.sendMessage(chat_id, "Peringatan: Kelembaban melebihi 55%!", "");
//     }
//   }

//   Serial.print("Suhu: ");
//   Serial.print(t);
//   Serial.print(" °C Kelembaban: ");
//   Serial.println(h);
  
//   delay(5000);
// }


#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
const int ledPin = 2;
bool ledState = LOW;

// WiFi connection configuration
char ssid[] = "akubisa"; // Your WiFi network name
char password[] = "pastibisa"; // Your WiFi password

// Telegram Bot initialization
#define BOTtoken "6510963302:AAGvQ3zWkTxrot4OD2cfhGuwGngiMF2psZs"
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Chat ID for notifications
// Replace with your appropriate chat ID
String chat_id = "6264528974";

// Periksa pesan baru setiap 1 detik
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
bool isBotStopped = false; // Add status variable

// Daily humidity data
// int kelembaban[] = {50, 53, 51, 56, 58};
// const int jumlahSampel = 5; // Use a constant value for the array size

int kelembaban[] = {50, 53, 51, 56};
const int jumlahSampel = 4; // Use a constant value for the array size

// Notification threshold
int threshold = 52;

// Simple Moving Average variables
int humidityBuffer[jumlahSampel] = {0}; // Fix array initialization
int humidityIndex = 0;

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
      welcome += "/status_temperature: Status Suhu\n";
      welcome += "/status_humidity: Status Kelembapan\n";
      welcome += "/ledon: Nyalakan LED\n";
      welcome += "/ledoff: Matikan LED\n";
      welcome += "/stop: Berhenti menerima pesan\n";
         ledState = HIGH;
      digitalWrite(ledPin, ledState);
      bot.sendMessage(chat_id, welcome, "Markdown");
    }

    if (text == "/stop") {
      isBotStopped = true;
      bot.sendMessage(chat_id, "Bot berhenti menerima pesan. Ketik /start untuk memulai kembali.", "");
       ledState = LOW;
      digitalWrite(ledPin, ledState);
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

    if (!isBotStopped) {
      if (text == "/status_temperature") {
        float t = dht.readTemperature();
        String temp = "Suhu saat ini: " + String(t) + " °C\n";
        bot.sendMessage(chat_id, temp, "");
      }

      if (text == "/status_humidity") {
        float h = dht.readHumidity();
        String humidity = "Kelembaban: " + String(h) + " %\n";
        bot.sendMessage(chat_id, humidity, "");
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  client.setInsecure();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);

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
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (millis() > lastTimeBotRan + botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("Menerima respons");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    lastTimeBotRan = millis();
  }

  if (!isBotStopped) {
    if (t > 30) {
      bot.sendMessage(chat_id, "Peringatan: Suhu melebihi 30°C!", "");
    }

    humidityBuffer[humidityIndex] = h;
    humidityIndex = (humidityIndex + 1) % jumlahSampel;

    float totalHumidity = 0;
    for (int i = 0; i < jumlahSampel; i++) {
      totalHumidity += humidityBuffer[i];
    }
    float smaHumidity = totalHumidity / jumlahSampel;

    if (smaHumidity > threshold) {
      String message = "Peringatan: Kelembaban prediksi melebihi threshold!\nKelembaban Prediksi: " + String(smaHumidity) + " %\nKelembaban Aktual: " + String(h) + " %";
      bot.sendMessage(chat_id, message, "");
    }
  }

  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print(" °C Kelembaban: ");
  Serial.println(h);

  delay(5000);
}
