#include <ESP8266WiFi.h>
const char* ssid     = "Sujit";         //JioFi_1087366";
const char* password = "sujee000";           //bmlhe3bpnf";
const char* host = "172.20.10.3";            //15.18";           //universalcard.000webhostapp.com";
char rfid[20];
char a;
int ct=0,ct1=0,ct2=0,ct3=0,b=0;

void setup() {
  Serial.begin(9600);
  delay(10);

  
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
 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

 }

int value = 0;
void loop() {
   
 delay(1000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
 
  for(int j=0;j<20;j++)
  {rfid[j] = '\0';}
  
  ct=0,ct1=0,ct2=0,ct3=0;
  while(Serial.available()>0)
  {
      a = (char)Serial.read(); 
    if(ct>=0 && ct<20)
    {
    rfid[ct]=a;
    ct++;
    }
    b=1;
  }
      if(b==1)
{
      String ch= rfid;
        Serial.println(rfid);
        
        // We now create a URI for the request
       
       String url = "/gms/data.php";
        url += "?temp=";
        url += rfid;
        Serial.print("Requesting URL: ");
        //Serial.println(url);
        
        // This will send the request to the server
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" + 
                     "Connection: close\r\n\r\n");
        unsigned long timeout = millis();
        while (client.available() == 0) {
          if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
          }
        }
        
        Serial.println();
        Serial.println("closing connection");
   b=0;
}
}
