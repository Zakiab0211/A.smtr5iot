#include <WiFi.h>

const char* ssid = "akubisa";
const char* password = "pastibisa";

int ledPin1 = 5; // GPIO 5
int ledPin2 = 18; // GPIO 18
int ledPin3 = 19; // GPIO 19

WiFiServer server(80);

String header;
String LED_STATE1 = "OFF";
String LED_STATE2 = "OFF";
String LED_STATE3 = "OFF";

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);

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

            if (header.indexOf("LED1=ON") != -1) {
              Serial.println("LED 1 is ON");
              LED_STATE1 = "ON";
              digitalWrite(ledPin1, HIGH);
            }
            if (header.indexOf("LED1=OFF") != -1) {
              Serial.println("LED 1 is OFF");
              LED_STATE1 = "OFF";
              digitalWrite(ledPin1, LOW);
            }
            
            if (header.indexOf("LED2=ON") != -1) {
              Serial.println("LED 2 is ON");
              LED_STATE2 = "ON";
              digitalWrite(ledPin2, HIGH);
            }
            if (header.indexOf("LED2=OFF") != -1) {
              Serial.println("LED 2 is OFF");
              LED_STATE2 = "OFF";
              digitalWrite(ledPin2, LOW);
            }
            
            if (header.indexOf("LED3=ON") != -1) {
              Serial.println("LED 3 is ON");
              LED_STATE3 = "ON";
              digitalWrite(ledPin3, HIGH);
            }
            if (header.indexOf("LED3=OFF") != -1) {
              Serial.println("LED 3 is OFF");
              LED_STATE3 = "OFF";
              digitalWrite(ledPin3, LOW);
            }
            
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<center><h2>Press buttons to control LEDs</h2></center>");
            client.println("<form><center>");
            
            client.println("<p1> LED 1 is " + LED_STATE1 + "</p1>");
            client.println("<button class=\"button\" name=\"LED1\" value=\"ON\" type=\"submit\">LED 1 ON</button>");
            client.println("<button class=\"button\" name=\"LED1\" value=\"OFF\" type=\"submit\">LED 1 OFF</button><br><br>");
            
            client.println("<p2> LED 2 is " + LED_STATE2 + "</p2>");
            client.println("<button class=\"button\" name=\"LED2\" value=\"ON\" type=\"submit\">LED 2 ON</button>");
            client.println("<button class=\"button\" name=\"LED2\" value=\"OFF\" type=\"submit\">LED 2 OFF</button><br><br>");
            
            client.println("<p3> LED 3 is " + LED_STATE3 + "</p3>");
            client.println("<button class=\"button\" name=\"LED3\" value=\"ON\" type=\"submit\">LED 3 ON</button>");
            client.println("<button class=\"button\" name=\"LED3\" value=\"OFF\" type=\"submit\">LED 3 OFF</button><br><br>");
            
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
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
