/*
 *  دعمكم لنا يزيدنا قدما وتقديم ماهو الافضل  بلسان ميسر وبسيط
 */
#include <WiFi.h>

const char* ssid = "AISSA_1";
const char* password = "123456789";

WiFiServer server(80);

String header;

String output19 = "منطفى";


const int LED19 = 19;


unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
   Serial.begin(115200);
  pinMode(LED19, OUTPUT);
 
  digitalWrite(LED19, LOW);
 
 
  Serial.print("جاري الاتصال... ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("تم الاتصال ");
  Serial.println("IP عنوان : ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop(){
 WiFiClient client = server.available();   

  if (client) {                             
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("زبون جديد ");          
    String currentLine = "";               
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  
      currentTime = millis();
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




  if (header.indexOf("GET /19/on") >= 0) {
              Serial.println("GPIO 19 on");
              output19 = "منشغل";
              digitalWrite(LED19, HIGH);
            } else if (header.indexOf("GET /19/off") >= 0) {
              Serial.println("GPIO 19 off");
              output19 = "منطفى";
              digitalWrite(LED19, LOW);
            }


            client.println("<!DOCTYPE html><html>");
           client.println("<head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"width=device-width, initial-scale=1\">");

            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #8C1E89; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            client.println("<body><h1>ESP32 التحكم في ليد</h1>");
            client.println("<p>حالة الليد الاول  " + output19 + "</p>");
            if (output19=="منطفى") {
              client.println("<p><a href=\"/19/on\"><button class=\"button\">تشغيل</button></a></p>");
            } else {
              client.println("<p><a href=\"/19/off\"><button class=\"button button2\">إطفاء</button></a></p>");
            } 
               
          
            
            client.println("</body></html>");
            
          
            client.println();
            // Break out of the while loop
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }}
