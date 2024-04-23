#include <WiFi.h>

const char* ssid = "wifi_latkel5";
const char* password = "123456789";

// char* ssid = "akubisa";
// const char* password = "pastibisa";

WiFiServer server(80);

String header;
String nilai_pin_5 = "off";
String nilai_pin_18 = "off";
String nilai_pin_19 = "off";

const int pin_D5 = 5;
const int pin_D18 = 18;
const int pin_D19 = 19;

void setup() {
  Serial.begin(115200);
  pinMode(pin_D5, OUTPUT);
  pinMode(pin_D18, OUTPUT);
  pinMode(pin_D19, OUTPUT);

  digitalWrite(pin_D5, LOW);
  digitalWrite(pin_D18, LOW);
  digitalWrite(pin_D19, LOW);

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

            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              nilai_pin_5 = "on";
              digitalWrite(pin_D5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              nilai_pin_5 = "off";
              digitalWrite(pin_D5, LOW);
            } else if (header.indexOf("GET /18/on") >= 0) {
              Serial.println("GPIO 18 on");
              nilai_pin_18 = "on";
              digitalWrite(pin_D18, HIGH);
            } else if (header.indexOf("GET /18/off") >= 0) {
              Serial.println("GPIO 18 off");
              nilai_pin_18 = "off";
              digitalWrite(pin_D18, LOW);
            } else if (header.indexOf("GET /19/on") >= 0) {
              Serial.println("GPIO 19 on");
              nilai_pin_19 = "on";
              digitalWrite(pin_D19, HIGH);
            } else if (header.indexOf("GET /19/off") >= 0) {
              Serial.println("GPIO 19 off");
              nilai_pin_19 = "off";
              digitalWrite(pin_D19, LOW);
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { border-radius: 50%; background-color: transparent; border: 2px solid #16191b; color: black; padding: 30px 30px;");
            client.println("text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: red;}");
            client.println(".button3 {background-color: green;}</style></head>");


            client.println("<body><h1>Control Led</h1>");
            client.println("<h2>With ESP32 Web Server</h2>");
            client.println("<h2>Over Soft AP</h2>");
            // client.println("<p>LED1 - Status " + nilai_pin_5 + "</p>");
            // client.println("<p>LED2  - Status " + nilai_pin_18 + "</p>");
            // client.println("<p>LED3  - Status " + nilai_pin_19 + "</p>");

            if (nilai_pin_5 == "off") {
              client.println("<p><span>LED1 - Status " + nilai_pin_5 + "</span> <a href=\"/5/on\"><button class=\"button button2\">ON</button></a></p>");
            } else {
              client.println("<p><span>LED1 - Status " + nilai_pin_5 + "</span> <a href=\"/5/off\"><button class=\"button\">OFF</button></a></p>");
            }

            if (nilai_pin_18 == "off") {
              client.println("<p><span>LED2 - Status " + nilai_pin_18 + "</span> <a href=\"/18/on\"><button class=\"button button2\">ON</button></a></p>");
            } else {
              client.println("<p><span>LED2 - Status " + nilai_pin_18 + "</span> <a href=\"/18/off\"><button class=\"button\">OFF</button></a></p>");
            }

            if (nilai_pin_19 == "off") {
              client.println("<p><span>LED3 - Status " + nilai_pin_19 + "</span> <a href=\"/19/on\"><button class=\"button button2\">ON</button></a></p>");
            } else {
              client.println("<p><span>LED3 - Status " + nilai_pin_19 + "</span> <a href=\"/19/off\"><button class=\"button\">OFF</button></a></p>");
            }

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