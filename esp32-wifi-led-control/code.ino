// Include the Wi-Fi library for ESP32
#include <WiFi.h>

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Create a web server object on port 80
WiFiServer server(80);

// GPIO pin connected to the LED
int ledPin = 22;

// Variable used to store incoming HTTP requests
String request = "";

void setup() {

  // Start serial communication for debugging
  Serial.begin(115200);

  // Small startup delay
  delay(2000);

  Serial.println("Starting ESP32...");

  // Configure LED pin as output
  pinMode(ledPin, OUTPUT);

  // Connect ESP32 to Wi-Fi network
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");

  // Wait until Wi-Fi connection is successful
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Display successful connection message
  Serial.println("\nWi-Fi connected!");

  // Print ESP32 local IP address
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the web server
  server.begin();

  Serial.println("Web server started!");
}

void loop() {

  // Check if a client has connected to the server
  WiFiClient client = server.available();

  // If a client connects
  if (client) {

    Serial.println("Client connected");

    String currentLine = "";

    // Keep connection active while client is connected
    while (client.connected()) {

      // Check if data is available from client
      if (client.available()) {

        // Read one character from incoming request
        char c = client.read();

        // Store character in request string
        request += c;

        // Detect end of line
        if (c == '\n') {

          // Empty line means end of HTTP request
          if (currentLine.length() == 0) {

            // If URL contains "/ON", turn LED ON
            if (request.indexOf("GET /ON") >= 0) {
              digitalWrite(ledPin, HIGH);
              Serial.println("LED turned ON");
            }

            // If URL contains "/OFF", turn LED OFF
            if (request.indexOf("GET /OFF") >= 0) {
              digitalWrite(ledPin, LOW);
              Serial.println("LED turned OFF");
            }

            // Send HTTP response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Create webpage content
            client.println("<html><body>");
            client.println("<h1>ESP32 LED Control</h1>");

            // ON button
            client.println("<a href=\"/ON\"><button>ON</button></a>");

            // OFF button
            client.println("<a href=\"/OFF\"><button>OFF</button></a>");

            client.println("</body></html>");

            // End HTTP response
            client.println();

            // Exit loop after sending response
            break;
          }

          // Clear current line for next line of request
          else {
            currentLine = "";
          }
        }

        // Add character to current line if not carriage return
        else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    // Clear stored request after processing
    request = "";

    // Disconnect client
    client.stop();

    Serial.println("Client disconnected");
  }

  // Small delay for stability
  delay(3000);
}
