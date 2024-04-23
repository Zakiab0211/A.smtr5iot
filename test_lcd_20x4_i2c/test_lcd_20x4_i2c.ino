// #include <Wire.h>  // Library for I2C communication
// #include <LiquidCrystal_I2C.h>  // Library for I2C LCD

// // Initialize the LCD with its I2C address
// LiquidCrystal_I2C lcd(0x27, 20, 4);  // Change the address (0x3F) based on your module

// void setup() {
//   lcd.init();  // Initialize the LCD
//   lcd.backlight();  // Turn on the backlight
//   lcd.setCursor(0, 0);  // Set the cursor to the top left corner
//   lcd.print("Hello, World!");  // Print a message on the first line
//   lcd.setCursor(0, 1);  // Set the cursor to the second line
//   lcd.print("LCD 20x4 with I2C");
// }

// void loop() {
//   // Your loop code here
// }

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHT_PIN 2 // Hubungkan pin data sensor DHT22 ke pin 2 pada Arduino
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Ganti alamat sesuai dengan modul I2C LCD Anda

const int ledPin = 7;  // Hubungkan LED ke pin 7 pada Arduino

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Suhu ");
  lcd.setCursor(1, 1);
  lcd.print("Kelembaban ");
  lcd.setCursor(2, 3);
  lcd.print("By:JekIELTRiC021");
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  lcd.setCursor(12, 0);
  lcd.print(":");
  lcd.setCursor(15, 0);
  lcd.print(temperature, 1); // Menampilkan suhu dengan satu desimal
  
  lcd.setCursor(12, 1);
  lcd.print(":");
  lcd.setCursor(15, 1);
  lcd.print(humidity, 1); // Menampilkan kelembaban dengan satu desimal

  if (humidity <= 60) {
    lcd.setCursor(1, 2);
    lcd.print("Kondisi");
    lcd.setCursor(12, 2);
    lcd.print(": Dingin");
    digitalWrite(ledPin, LOW);  // Matikan LED
  } else if (humidity >= 65) {
    lcd.setCursor(1, 2);
    lcd.print("Kondisi");
    lcd.setCursor(12, 2);
    lcd.print(": Panas");
    // Aktifkan efek kedipan cepat
    for (int i = 0; i < 10; i++) {
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
  } else {
    lcd.setCursor(1, 2);
    lcd.print("Kondisi");
    lcd.setCursor(12, 2);
    lcd.print(": Normal");
    digitalWrite(ledPin, LOW);  // Matikan LED
  }
  
  delay(2000);  // Baca data setiap 2 detik
}


// /*I2C_scanner
// This sketch tests standard 7-bit addresses.
// Devices with higher bit address might not be seen properly.*/
 
// #include <Wire.h>
 
// void setup() {
// Wire.begin();
 
// Serial.begin(9600);
// while (!Serial);
// Serial.println("\nI2C Scanner");
// }
 
// void loop() {
// byte error, address;
// int nDevices;
 
// Serial.println("Scanning...");
 
// nDevices = 0;
// for (address = 1; address < 127; address++ ) {
// Wire.beginTransmission(address);
// error = Wire.endTransmission();
 
// if (error == 0) {
// Serial.print("I2C device found at address 0x");
// if (address < 16)
// Serial.print("0");
// Serial.print(address, HEX);
// Serial.println(" !");
 
// nDevices++;
// }
// else if (error == 4) {
// Serial.print("Unknown error at address 0x");
// if (address < 16)
// Serial.print("0");
// Serial.println(address, HEX);
// }
// }
// if (nDevices == 0)
// Serial.println("No I2C devices found\n");
// else
// Serial.println("done\n");
 
// delay(5000);
// }
