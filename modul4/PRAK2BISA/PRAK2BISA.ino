#include <WiFi.h>

// const char* ssid = "Oke";            // Nama SSID jaringan WiFi yang akan dihubungkan
// const char* password = "123456789";  // Kata sandi jaringan WiFi yang akan dihubungkan


const char* ssid = "akubisa";            // Nama SSID jaringan WiFi yang akan dihubungkan
const char* password = "pastibisa";  // Kata sandi jaringan WiFi yang akan dihubungkan

const int buzzerPin = 2;  // GPIO 2
WiFiServer server(80);    // Declare the server object


WiFiClient client;

String buzzerState = "OFF";
String header;  // Declare the header variable

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  Serial.println("Connecting to WiFi...");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.println("Connected to WiFi");
  server.begin();
  Serial.println("Server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}


void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client is requesting web page");
    String current_data_line = "";
    while (client.connected()) {
      if (client.available()) {
        char new_byte = client.read();
        Serial.write(new_byte);
        header += new_byte;
        if (new_byte == '\n') {

          if (current_data_line.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /buzzer/on") >= 0) {
              Serial.println("Buzzer is ON");
              buzzerState = "ON";
              digitalWrite(buzzerPin, HIGH);
            } else if (header.indexOf("GET /buzzer/off") >= 0) {
              Serial.println("Buzzer is OFF");
              buzzerState = "OFF";
              digitalWrite(buzzerPin, LOW);
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { border-radius: 50%; background-color: transparent; border: 2px solid #16191b; color: black; padding: 30px 30px;");
            client.println("text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: red;}");
            client.println(".button3 {background-color: blue;}</style></head>");

            client.println("<body><h1>Monitoring & Control</h1>");
            client.println("<h2>With ESP32 Web Server</h2>");
            client.println("<h2>Over Station Mode</h2>");

            client.println("<p><span>Buzzer - Status " + buzzerState + "</span> <a href=\"/buzzer/on\"><button class=\"button button2\">ON</button></a> <a href=\"/buzzer/off\"><button class=\"button\">OFF</button></a></p>");

            client.println("<a href=\"https://thingspeak.com/channels/2269586\" target=\"_blank\"><button class=\"button button3\">Monitoring</button></a>");

            client.println("</body></html>");
            client.println();
            break;
          } else {
            current_data_line = "";
          }
        } else if (new_byte != '\r') {
          current_data_line += new_byte;
        }
      }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}