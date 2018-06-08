
#include <Servo.h>
#include <ESP8266WiFi.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

// GPIO the servo is attached to
static const int servoPin = 13;

// Replace with your network credentials
const char* ssid     = "ozmen";
const char* password = "ozmen2250801";
int ledPin = 2;
int ledPin2 = 0;
int ledPin3 = 4;
// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Decode HTTP GET value
String valueString = String(1);
String valueString2 = String(0);
String valueString3 = String(0);
int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5 = 0;
int pos6 = 0;

void setup() {
  Serial.begin(115200);
pinMode(ledPin, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
  // attaches the servo on the servoPin to the servo object

  // Connect to Wi-Fi network with SSID and password
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
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

                     
            
            
            
            client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
// CSS to style the on/off buttons 
// Feel free to change the background-color and font-size attributes to fit your preferences
client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
client.println(".slider { width: 300px; }</style>");
client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
        
// Web Page
client.println("</head><body><h1>Bos Adam Mıyız ? <3</h1>");
client.println("<p>Position: <span id=\"servoPos\"></span></p>");          
client.println("<input type=\"range\" min=\"0\" max=\"1023\" class=\"slider\" id=\"servoSlider\" onchange=\"servo()\" value=\""+valueString+"\"/>");
client.println("<br><p>Position 2: <span id=\"servoPos2\"></span></p>");          
client.println("<input type=\"range\" min=\"0\" max=\"1023\" class=\"slider\" id=\"servoSlider2\" onchange=\"servo()\" value=\""+valueString2+"\"/>");
client.println("<br><p>Position 3: <span id=\"servoPos3\"></span></p>");          
client.println("<input type=\"range\" min=\"0\" max=\"1023\" class=\"slider\" id=\"servoSlider3\" onchange=\"servo()\" value=\""+valueString3+"\"/>");

client.println("<script>var slider = document.getElementById(\"servoSlider\");");
client.println("var slider2 = document.getElementById(\"servoSlider2\");");
client.println("var slider3 = document.getElementById(\"servoSlider3\");");
client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
client.println("var servoP2 = document.getElementById(\"servoPos2\"); servoP2.innerHTML = slider2.value;");
client.println("var servoP3 = document.getElementById(\"servoPos3\"); servoP3.innerHTML = slider3.value;");
client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
client.println("slider2.oninput = function() { slider2.value = this.value; servoP2.innerHTML = this.value; }");
client.println("slider3.oninput = function() { slider3.value = this.value; servoP3.innerHTML = this.value; }");
client.println("$.ajaxSetup({timeout:1000}); function servo() { ");
client.println("$.get(\"/?value=\" + slider.value + \"&\" + slider2.value + \"&\" + slider3.value + \"&\"); {Connection: close};}</script>");

client.println("</body></html>");
                     
             
            //GET /?value=180& HTTP/1.1
            if(header.indexOf("GET /?value=")>=0) {
              
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              
              valueString = header.substring(pos1+1, pos2);
              valueString2 = header.substring(pos2+1, pos2+4);
              valueString3 = header.substring(pos2+5, pos2+9);

             int valueStringA= map(valueString.toInt(),100,999,0,1023);
             int valueStringB= map(valueString2.toInt(),100,999,0,1023);
             int valueStringC= map(valueString3.toInt(),100,999,0,1023);
             
              analogWrite(ledPin,valueStringA);
              analogWrite(ledPin2,valueStringB);
              analogWrite(ledPin3,valueStringC);
                
                
              
              Serial.println(valueStringA); 
              Serial.println(valueStringB);
              Serial.println(valueStringC); 
                
            }         
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
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
