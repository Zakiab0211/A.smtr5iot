#include <WiFi.h>

const char* ssid = "wifi_lat";
const char* password = "123456789";

WiFiServer server(80);

String header;
// String nilai_pin_5 = "off";
// String nilai_pin_18 = "off";
// String nilai_pin_19 = "off";
String nilai_pin_2 = "off";

// const int pin_D5 = 5;
// const int pin_D18 = 18;
// const int pin_D19 = 19;
const int pin_D2 = 2;

void setup() {
  Serial.begin(115200);
  // pinMode(pin_D5, OUTPUT);
  // pinMode(pin_D18, OUTPUT);
  // pinMode(pin_D19, OUTPUT);
  pinMode(pin_D2, OUTPUT);
  // digitalWrite(pin_D5, LOW);
  // digitalWrite(pin_D18, LOW);
  // digitalWrite(pin_D19, LOW);
  digitalWrite(pin_D2, LOW);
  Serial.print("Setting AP (Access Point)...");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;

        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              nilai_pin_2 = "on";
              digitalWrite(pin_D2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              nilai_pin_2 = "off";
              digitalWrite(pin_D2, LOW);

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { border-radius: 50%; background-color: transparent; border: 2px solid #16191b; color: black; padding: 30px 30px;");
            client.println("text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: red;}");
            client.println(".button3 {background-color: green;}</style></head>");

            client.println("<body><h1>Monitoring & Control</h1>");
            client.println("<h2>With ESP32 Web Server</h2>");
            client.println("<h2>Over Soft AP</h2>");

            if (nilai_pin_2 == "off") {
              client.println("<p><span>BUZZER - Status " + nilai_pin_2 + "</span> <a href=\"/2/on\"><button class=\"button button2\">ON</button></a></p>");
            } else {
              client.println("<p><span>BUZZER - Status " + nilai_pin_2 + "</span> <a href=\"/2/off\"><button class=\"button\">OFF</button></a></p>");
            }

            // Tombol Monitoring
            client.println("<a href=\"https://thingspeak.com/channels/YOUR_CHANNEL_ID\" target=\"_blank\">");
            client.println("<button class=\"button\">Monitoring</button></a>");

            // Tombol Buzzer ON
            client.println("<a href=\"/buzzer/on\"><button class=\"button button2\">Buzzer ON</button></a>");

            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
}
