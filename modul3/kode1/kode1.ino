#include <WiFi.h>
const char* ssid = "akubisa";
const char* password = "pastibisa";



int ledPin = 5;
WiFiServer server(80);

String header;
String LED_STATE1 = "OFF";

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
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

            if (header.indexOf("LED=ON") != -1) {
              Serial.println("LED is ON");
              LED_STATE1 = "ON";
              digitalWrite(ledPin, HIGH);
            }
            if (header.indexOf("LED=OFF") != -1) {
              Serial.println("LED is OFF");
              LED_STATE1 = "OFF";
              digitalWrite(ledPin, LOW);
            }
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            // Web Page Heading client.println("<body><center><h1>ESP32 Web server LED controlling</h1></center>");
client.println("<center><h2>Press on button to turn on led and off button to turn off LED</h3></center>");
client.println("<form><center>");
client.println("<p> LED is " + LED_STATE1 + "</p>"); 
client.println("<center> <button class=\"button\" name=\"LED\" value=\"ON\" type=\"submit\">LED ON</button>") ; 
client.println("<button class=\"button\" name=\"LED\" value=\"OFF\" type=\"submit\">LED OFF</button><br><br>"); 
client.println("</center></form></body></html>");
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
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}