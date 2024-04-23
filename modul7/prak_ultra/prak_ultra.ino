
// #define BLYNK_PRINT Serial
// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <BlynkSimpleEsp32.h>


// char auth[] = "MhvHV2YXxQCYDI7G_SU0VszrPaGUpuu-";   //Token Blynk

// #define BLYNK_TEMPLATE_ID "TMPL6uGMGELif"
// #define BLYNK_TEMPLATE_NAME "monitoring air"
// #define BLYNK_AUTH_TOKEN "MhvHV2YXxQCYDI7G_SU0VszrPaGUpuu-"
// //===========================================

// //=============== Koneksi WiFi ==============
// char ssid[] = "akubisa";   
// char pass[] = "pastibisa";   

// //Deklarasi Sensor
// #define trigPin D1
// #define echoPin D2
// #define LEDsystem D6
// #define LEDalarm D7
// #define BUZZ D5

// BlynkTimer timer;

// //Widget Blynk 
// WidgetLED led1(V3);
// WidgetLCD lcd(V1);


// //Deklarasi variabel 
// long duration;
// long distance;


// void setup() {
//   //===Debug console
//   Serial.begin(115200);

//   // Blynk.begin(auth, ssid, pass);
//   // You can also specify server:
//   Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
//   //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

//   // code blynk akan jalan setiap 1 detik
//   //timer.setInterval(10L, sendSensor);

//   //===attempt to connect to Wifi network:
//   configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP

//   Serial.print("Connecting to Wifi SSID ");
//   Serial.print(ssid);
//   WiFi.begin(ssid, pass);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     Serial.print(".");
//     delay(500);
//   }
//   Serial.print("\nWiFi connected. IP address: ");
//   Serial.println(WiFi.localIP());

//   // PIN sebagai...
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);

//   pinMode(BUZZ, OUTPUT);
//   pinMode(LEDsystem, OUTPUT);
//   pinMode(LEDalarm, OUTPUT);

//   Startup();
// }

// void loop() {
//   Blynk.run();
//   if (digitalRead(LEDsystem) == HIGH)  {
//     digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
  
//   //Set the trigPin on HIGH state for 10 micro seconds
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
  
//   //Read the echoPin, return to sound wave travel time to microseconds
//   duration = pulseIn(echoPin, HIGH);
  
//   //Calculating the distance
//   distance = duration*0.034/2; //s=t*v
  
//   //kirim data ke blynk
//   Blynk.virtualWrite(V2, distance);   

//   //LCD Di Blynk
//   lcd.print (0, 0, "Monitoring Jarak");
//   lcd.print (0, 1, "Jarak : " + String(distance) + " cm");
//     timer.run();
//     logic();

//     Serial.print("Durasi: ");
//     Serial.println(duration);
//     Serial.print("Jarak: ");
//     Serial.print(distance);
//     Serial.print (" cm");
//     Serial.println (" ");
//     delay(100);
//   }
//   else  {
//     digitalWrite(LEDsystem, LOW);
//     Serial.println("Sistem OFF");
//     delay(1000);
//   }

// }


// //Logika Jarak 
// void logic() {
//   if ( distance <= 5) {

//     Blynk.setProperty(V3, "color", "#FF0000"); //warna merah
//     led1.on();
//       digitalWrite(BUZZ, HIGH);
//       digitalWrite(LEDalarm, HIGH);
//       delay(60);
//       digitalWrite(BUZZ, LOW);
//       digitalWrite(LEDalarm, LOW);
//       delay(30);
//     //}
//     Serial.println(" MEPET");
//   }

//   else if (( distance > 5 ) && ( distance < 15)) {

//     Blynk.setProperty(V3, "color", "#FFE600"); // warna kuning
//     led1.on();
//       digitalWrite(BUZZ, HIGH);
//       digitalWrite(LEDalarm, HIGH);
//       delay(400);
//       digitalWrite(BUZZ, LOW);
//       digitalWrite(LEDalarm, LOW);
//       delay(400);
//     //}
//     Serial.println ( " DEKAT");

//   }

//   else if ( distance >= 15) {
//     Blynk.setProperty(V3, "color", "#2EFF26"); //warna hijau
//     led1.on();
//     delay(200);
//     Serial.println ( " JAUH");

//   }
// }
// //

// //Kirim Data Sensor 
// void sendSensor() {
//   //clear the trigPin
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
  
//   //Set the trigPin on HIGH state for 10 micro seconds
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
  
//   //Read the echoPin, return to sound wave travel time to microseconds
//   duration = pulseIn(echoPin, HIGH);
  
//   //Calculating the distance
//   distance = duration*0.034/2; //s=t*v
  
//   //kirim data ke blynk
//   Blynk.virtualWrite(V2, distance);   

//   //LCD Di Blynk
//   lcd.print (0, 0, "Monitoring Jarak");
//   lcd.print (0, 1, "Jarak : " + String(distance) + " cm");
// }

// //Bunyi Awal Saat Tersambung 
// void Startup()  {
//   // bunyi awal buzzer
//   digitalWrite(BUZZ, HIGH);
//   delay(500);
//   digitalWrite(BUZZ, LOW);
//   delay(500);
//   digitalWrite(BUZZ, HIGH);
//   delay(100);
//   digitalWrite(BUZZ, LOW);
//   delay(100);
//   digitalWrite(BUZZ, HIGH);
//   delay(300);
//   digitalWrite(BUZZ, LOW);
//   delay(200);
//   digitalWrite(BUZZ, HIGH);
//   delay(100);
//   digitalWrite(BUZZ, LOW);
// }
#define BLYNK_TEMPLATE_ID "TMPL6uGMGELif"
#define BLYNK_TEMPLATE_NAME "monitoring air"
#define BLYNK_AUTH_TOKEN "hkeC-8CjquHHSHa_IPZjy0UTTiEnzgFM"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial

#define TRIGGER_PIN 19 // Pin untuk sensor ultrasonik Trigger
#define ECHO_PIN 18    // Pin untuk sensor ultrasonik Echo
#define BUZZER_PIN 4   // Pin untuk buzzer
#define LED_PIN 2      // Pin untuk LED

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "akubisa";
char pass[] = "pastibisa"; // Tambahkan kata sandi Wi-Fi Anda di sini

bool ledStatus = false; // Status awal LED mati
bool buzzerActive = false; // Status awal buzzer tidak aktif
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
  timer.setInterval(1000L, sendUltrasonicData); // Kirim data ultrasonik setiap 1 detik

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
  float distance = (duration / 2.0) * 0.0344; // Menghitung jarak dalam cm

  int buzzerData = digitalRead(BUZZER_PIN);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Blynk.virtualWrite(V0, distance); // Kirim data jarak ke Blynk

  // Logika Buzzer
  if (( distance >= 6 ) && ( distance < 10)) {
    if (millis() - lastBuzzerTime > 5000) {
      // Buzzer akan berbunyi setiap 5 detik sekali jika ada peringatan
      digitalWrite(BUZZER_PIN, HIGH);
      buzzerActive = true;
      lastBuzzerTime = millis();

      // Hidupkan LED saat buzzer berbunyi
      digitalWrite(LED_PIN, LOW);
      ledStatus = true;
      Serial.println("Warning");
    }
    else if ( distance <= 5) {
      digitalWrite(BUZZER_PIN, HIGH);
      buzzerActive = true;

      // Hidupkan LED saat buzzer berbunyi
      digitalWrite(LED_PIN,HIGH );
      ledStatus = true;
      Serial.println("Bahaya");
    }

  } else if ( distance > 10){
    digitalWrite(BUZZER_PIN, LOW);
    buzzerActive = false;
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
    buzzerActive = false;
    // Matikan LED jika buzzer tidak aktif
    digitalWrite(LED_PIN, LOW);
    ledStatus = false;
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    ledStatus = false;
    Serial.println("Normal aja....");
  }
  else{
    digitalWrite(BUZZER_PIN, LOW);
    buzzerActive = false;
    // Matikan LED jika buzzer tidak aktif
    digitalWrite(LED_PIN, LOW);
    ledStatus = false;
  }

  Blynk.virtualWrite(V1, buzzerData);
  Blynk.virtualWrite(V3, ledStatus);
}
