// int LED_BUILTIN = 2;

// void setup() {
//     pinMode(LED_BUILTIN, OUTPUT); // Initialize LED pin as OUTPUT
//     // digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off (assuming common cathode configuration)
// }

// void loop() {
//     digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
//     delay(1000);
//     digitalWrite(LED_BUILTIN, LOW);
//     delay(1000);
// }


// String teks = "Belajar Internet of Things dengan ESP32"; 
// void setup() {
// Serial.begin(115200); 
// }
// void loop() { Serial.println(teks); 
// delay(1000);
// }


#include <WiFi.h>
const char* ssid = "akubisa"; 
const char* password = "pastibisa";
void setup() {
Serial.begin(115200);
Serial.print("Connecting to ");
Serial.println(ssid); 
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) { 
delay(500);
Serial.print("."); 
}
// Print local IP address and start web server
Serial.println("");
Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}
void loop() { 
}