#include <WiFi.h>

const char* ssid     = "MEDIAWIRE-CUCAITA";      // SSID
const char* password = "1003614300DMCC";      // Password
const char* host = "192.168.1.39";// IP serveur - Server IP
//const char* host = "192.168.1.39";
const int   port = 80;            // Port serveur - Server Port
const int   watchdog = 5000;        // Fréquence du watchdog - Watchdog frequency
unsigned long previousMillis = millis(); 

int pulsador=23;
float puls=25.5;
void setup(){
    Serial.begin(115200); 
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

   pinMode(pulsador,INPUT_PULLDOWN);
}
void loop(){
 int n_state=digitalRead(pulsador);
 //if(n_state==HIGH){
  //Serial.println("pulsador=");
 // Serial.print(puls);
  
unsigned long currentMillis = millis();
    
   if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
   if (client.connect(host, port)) {
     Serial.println("conectado");
    }
   else {
     Serial.println("Fallo al conectar");
     return;
   }
//String pullss = String(puls, 3);
    String url = "/PruebasESP32_r/BaseDatosp1/PruebaPulsador.php?puls=";
    url += puls;
    
    // Enviamos petición al servidor
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
  
    // Leemos la respuesta del servidor
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  delay(800);
}
