#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* host="https://www.naver.com"; //Its the ip of the esp8266 as Access point
const char* ssid="SUNIN_C2";
const char* password="admin1234"; 
const int httpPort = 80;
String line="";

void setup() {
  Serial.begin(9600); 
   
  // WiFi.mode(WIFI_STA);    
  WiFi.begin(ssid, password);      //Connect to the server ESP8266
  while (WiFi.status() != WL_CONNECTED) {      
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());          
}

void loop() {
   Serial.print("connecting to ");
   Serial.println(host);
   WiFiClient client; // Use WiFiClient class to create TCP connections
   if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
   }   
   client.print(String("GET ")+"/"+" HTTP/1.1\r\n"+"Host: "+host+"\r\n"+"Connection: close\r\n\r\n"); //Request to server   
   delay(10);
   while(client.available()){
      String line = client.readStringUntil('\r'); // Read all the lines of the reply from server                
      Serial.println(line);
   }
   Serial.println("closing connection");            
   delay(5000);
}
