#define BLYNK_TEMPLATE_ID "TMPL6uGMGELif"
#define BLYNK_TEMPLATE_NAME "monitoring air"
#define BLYNK_AUTH_TOKEN "hkeC-8CjquHHSHa_IPZjy0UTTiEnzgFM"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial

#define TRIGGER_PIN 19  // Pin untuk sensor ultrasonik Trigger
#define ECHO_PIN 18     // Pin untuk sensor ultrasonik Echo
#define BUZZER_PIN 4    // Pin untuk buzzer
#define LED_PIN 2       // Pin untuk LED

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "akubisa";
char pass[] = "pastibisa";  // Tambahkan kata sandi Wi-Fi Anda di sini

bool ledStatus = false;     // Status awal LED mati
bool buzzerActive = false;  // Status awal buzzer tidak aktif
unsigned long lastBuzzerTime = 0;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  // Inisialisasi sensor ultrasonik, buzzer, dan LED
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  timer.setInterval(1000L, sendUltrasonicData);  // Kirim data ultrasonik setiap 1 detik

  // Inisialisasi widget Blynk untuk mengontrol LED
  Blynk.virtualWrite(V3, ledStatus);
}

bool isFirstConnect = true;

BLYNK_CONNECTED() {
  if (isFirstConnect) {
    Blynk.syncAll();
    isFirstConnect = false;
  }
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendUltrasonicData() {
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration / 2.0) * 0.0344;  // Menghitung jarak dalam cm

  int buzzerData = digitalRead(BUZZER_PIN);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Blynk.virtualWrite(V0, distance);  // Kirim data jarak ke Blynk

  // Logika Buzzer dan LED
  if (distance <= 5) {
    // Jika jarak <= 5 cm, ada bahaya
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    ledStatus = true;
    buzzerActive = true;
    Serial.println("Bahaya");
  } else if (distance <= 10) {
    // Jika jarak < 10 cm, ada peringatan
    if (millis() - lastBuzzerTime > 5000) {
      digitalWrite(BUZZER_PIN, HIGH);
      ledStatus = true;
      buzzerActive = true;
      lastBuzzerTime = millis();
      Serial.println("Warning");
    }
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    ledStatus = false;
    buzzerActive = false;
    Serial.println("Normal aja....");
  } 

  Blynk.virtualWrite(V1, buzzerData);
  Blynk.virtualWrite(V3, ledStatus);
}
