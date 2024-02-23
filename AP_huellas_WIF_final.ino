#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
///////////////// lector de huellas ///////////////7
#include <Adafruit_Fingerprint.h>
#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// Para UNO y otros sin serial hardware, debemos usar serial por software...
// El pin #2 es ENTRADA desde el sensor (cable VERDE)
// El pin #3 es SALIDA desde Arduino (cable BLANCO)
// Configurar el puerto serial para usar serial por software...
SoftwareSerial mySerial(D1,D2);
#else
// En Leonardo/M0/etc y otros con serial hardware, utilizar serial hardware.
// #0 es el cable verde, #1 es el blanco.
#define mySerial Serial1
 
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;
/////////////////////////////////7
const int sensorPin = D0;  //El pin al que está conectado el sensor táctil

int ledrojo = D5;  //El pin al que está conectado el sensor táctil
 int ledverde = D6;  //El pin al que está conectado el sensor táctil
 int ledamarillo = D7;  //El pin al que está conectado el sensor táctil
 int ledazul = D8;  //El pin al que está conectado el sensor táctil
int contador = 0; // Variable para almacenar el valor del contador

char names[8][2][16]; // Array to store names in two columns
bool nameSet[8] = {false}; // Array to track whether the name in the second column is set
unsigned long startTime; // Variable para almacenar el tiempo de inicio


/////////////////////////////////////////////////wifi ///////////77
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin D1

const char* ssid = "MiPuntoDeAcceso";
const char* password = "PuntoDeAcceso";
const char* IDcerradura = "nn22kk";     // IP del servidor
const char* conjuto = "conjunto1";      // IP del servidor
const char* host = "192.168.20.141";     // IP del servidor
const int port = 80;                    // Puerto del servidor
ESP8266WebServer server(80);
bool clienteConectado = false;
bool Menu = false;
char localIPChar[16];                   // Un arreglo de caracteres para almacenar la dirección IP local
unsigned long previousMillis = millis();
const int watchdog = 5000;  

    unsigned long currentMillis = millis();
    String h ; //dato pa enviar
    int t = 111; //dato pa enviar    



//////////////////////////////////////////////////////////
    
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Bienvenido a mi ESP8266</h1>";
  
  if (server.hasArg("nombre") && server.hasArg("clave")) {
    String newNombre = server.arg("nombre");
    String newClave = server.arg("clave");

    if (newNombre.length() >= 8 && newClave.length() >= 8) {
      Serial.print("Nuevo SSID: ");
      Serial.println(newNombre);
      Serial.print("Nueva contraseña: ");
      Serial.println(newClave);
      // Mostrar los datos del nuevo nombre y contraseña en la página web
      html += "<p>Nuevo SSID: " + newNombre + "</p>";
      html += "<p>Nueva contraseña: " + newClave + "</p>";

      // Convertir las cadenas String a arreglos de caracteres (char)
      char nombreCharArray[newNombre.length() + 1];  // +1 para el carácter nulo
      char claveCharArray[newClave.length() + 1];    // +1 para el carácter nulo

      newNombre.toCharArray(nombreCharArray, sizeof(nombreCharArray));
      newClave.toCharArray(claveCharArray, sizeof(claveCharArray));

      // Cambiar el SSID y la contraseña
      WiFi.softAPdisconnect();
      WiFi.softAP(nombreCharArray, claveCharArray);

      // Informar sobre la actualización del SSID y la contraseña
      html += "<p>SSID y contraseña actualizados.</p>";
        Serial.println("SSID y contraseña actualizados.");
      // Redirigir al usuario a la página principal después de 400 segundos
     delay(1000);
      server.sendHeader("Location", "/", true);
      server.send(302, "text/plain", "");
    } else {
      html += "<p>No cumple con los requisitos.</p>";
      Serial.println("No cumple con los requisitos.");
    }
  } 
  
  if (server.hasArg("wifi") && server.hasArg("ssid") && server.hasArg("password")) {
    String newSsid = server.arg("ssid");
    String newPassword = server.arg("password");
    
    Serial.print("Nuevo SSID: ");
    Serial.println(newSsid);
    Serial.print("Nueva contraseña: ");
    Serial.println(newPassword);

    // Mostrar los datos de ssid y password en la página web
    html += "<p>Nuevo SSID: " + newSsid + "</p>";
    html += "<p>Nueva contraseña: " + newPassword + "</p>";

    // Convertir las cadenas String a arreglos de caracteres (char)
    char ssidCharArray[newSsid.length() + 1];  // +1 para el carácter nulo
    char passwordCharArray[newPassword.length() + 1];  // +1 para el carácter nulo

    newSsid.toCharArray(ssidCharArray, sizeof(ssidCharArray));
    newPassword.toCharArray(passwordCharArray, sizeof(passwordCharArray));

    // Desactivar el punto de acceso
    WiFi.softAPdisconnect();

    // Intentar conectarse a la red Wi-Fi de la casa
    WiFi.begin(ssidCharArray, passwordCharArray);
  unsigned long wifiTimeout = 20000;     // Tiempo límite para la conexión WiFi en milisegundos (2 minutos)
   unsigned long wifiStartTime = millis(); // Registrar el tiempo de inicio del intento de conexión WiFi
 
   
  
    // Esperar a que se conecte a la red Wi-Fi de la casa durante 40 segundos
    int timeout = 4000;
    while (WiFi.status() != WL_CONNECTED ) {
   
    delay(250);
    Serial.print("Connecting to WiFi...");
     if (millis() - wifiStartTime > wifiTimeout) {
      Serial.println("\nTiempo de espera de la conexión WiFi agotado. Continuando sin WiFi.");
      
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
     Serial.println("Dirección IP del Punto de Acceso: ");
     
    digitalWrite(ledazul, HIGH);  // Encender el LED
  Serial.println(WiFi.softAPIP());
      break; // Salir del bucle de conexión WiFi
    } 
    }

    // Comprobar si se ha conectado correctamente a la red Wi-Fi de la casa
    if (WiFi.status() == WL_CONNECTED) {
      
    digitalWrite(ledazul, LOW);   // Apagar el LED en otros casos
      Serial.print("Conectado a la red: ");
      Serial.println(ssidCharArray);
      Serial.print("Dirección IP asignada: ");
        
  
  
      Serial.println(WiFi.localIP());

        IPAddress localIP = WiFi.localIP();
  snprintf(localIPChar, sizeof(localIPChar), "%d.%d.%d.%d", localIP[0], localIP[1], localIP[2], localIP[3]);

  // Print the local IP address
  Serial.print("IP LOCAL dada por el router");
  Serial.println(localIPChar);
  
 unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > watchdog) {
    previousMillis = currentMillis;
    WiFiClient client;

    if (!client.connect(host, port)) {
      Serial.println("Failed to connect");
      return;
    }

    Serial.print("Local IP address as char array: ");
    Serial.println(localIPChar);
    String url = "/AppCerradura/camb.php?conj=";
    url += conjuto;
    url += "&ip=";
    url += localIPChar;
    url += "&Cerrad=";
    url += IDcerradura;
    // Send request to the server
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

    // Read the server's response
    while(client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  delay(800);
      
      html += "<p>Conectado a la red: " + String(ssidCharArray) + "</p>";
      html += "<p>Dirección IP asignada: " + WiFi.localIP().toString() + "</p>";
    } else {
      html += "<p>No se pudo conectar a la red de la casa. Continuará funcionando como AP punto de acceso.</p>";
      Serial.println("No se pudo conectar a la red de la casa. Continuará funcionando como AP punto de acceso.");
   
    }

    // Redirigir al usuario a la página principal después de 400 segundos
    delay(1000);
      server.sendHeader("Location", "/", true);
      server.send(302, "text/plain", "");
      
  }  else if (server.hasArg("guardar") && server.hasArg("Id") && server.hasArg("Nombre")) {
    // Obtén el valor de Id como cadena
    String IdString = server.arg("Id");
      int Id = IdString.toInt();
      int selectedRow = Id;
      t=Id;
      
         if (IdString != "" && Id != 0) {
       Serial.print("guardar ID (entero): ");
      Serial.println(Id);
    } else {
       Serial.print("Error: ID no es un número entero válido");
       }
    
      if (selectedRow >= 1 && selectedRow <= 8) {
        Serial.print(selectedRow);
        Serial.println(": ");
        if (nameSet[selectedRow - 1]) {
          Serial.println("El nombre en la segunda columna ya está establecido y no se puede cambiar.");
        } else {
          Serial.println("Ingrese el nombre que quieres guardar: ");
          
   String Nombre = server.arg("Nombre");
   h=Nombre;
    Serial.println("Nombre: " + Nombre);

     
          String newName = server.arg("Nombre");
          newName.trim();

          if (newName.length() > 0) {
            strcpy(names[selectedRow - 1][0], newName.c_str());
            Serial.println("Nombre actualizado en la primera columna.");
            nameSet[selectedRow - 1] = true;
            EEPROM.put(selectedRow * sizeof(bool), nameSet[selectedRow - 1]);
               server.send(200, "text/plain", "ok" );
            delay(2000);
           accion_3();
           delay(100);
            agregar();
          } else {
            Serial.println("El nombre no puede estar vacío.");
          }
        }
      }
    // Intenta convertirlo a un número entero
    

    // Verifica si la conversión fue exitosa
   

    
    // Redirigir al usuario a la página principal después de 400 segundos
    delay(1000);
    Menu = true;

      
  } else if (server.hasArg("eliminar") && server.hasArg("Id")) {
    // Obtén el valor de Id como cadena
    String IdString = server.arg("Id");

    // Intenta convertirlo a un número entero
    int Id = IdString.toInt();

      int deleteRow = Id;
     t=Id;
     h="";
      if (deleteRow >= 1 && deleteRow <= 8) {
        if (names[deleteRow - 1][0][0] == '\0') {
          Serial.println("La fila seleccionada está vacía. Por favor, seleccione otra fila.");
          delay(4000);
         
        } else {
          names[deleteRow - 1][0][0] = '\0';
          names[deleteRow - 1][1][0] = '\0';
          nameSet[deleteRow - 1] = false;
          EEPROM.put(deleteRow * sizeof(bool), nameSet[deleteRow - 1]);
          Serial.println("Nombre eliminado.");
          server.send(200, "text/plain", "ok" );
          delay(2000);
         accion_2();
         delay(100);
         eliminar();
        }
      } else {
        Serial.println("Número de fila no válido. Elija una fila entre 1 y 8.");
      }
    

    // Verifica si la conversión fue exitosa
    if (IdString != "" && Id != 0) {
      html += "<p>Eliminar ID (entero): " + String(Id) + "</p>";
      Serial.print("Eliminar ID (entero): ");
      Serial.println(Id);
      t=Id;
      
     
    } else {
         Serial.println("Error: ID no es un número entero válido");
    }

    Menu = true;

    // Redirigir al usuario a la página principal después de 400 segundos
    delay(1000);
  } else if (server.hasArg("registro")) {

      Serial.println("Columna 1\tColumna 2");
  for (int i = 0; i < 8; i++) {
    Serial.print(i + 1);
    Serial.print("\t");
    Serial.print(names[i][0]);
    Serial.print("\t");
    Serial.println(names[i][1]);
  }

  String response = "ID \t Nombre\n";
  for (int i = 0; i < 8; i++) {
    response += String(i + 1) + "\t" + names[i][0] + "\t" + names[i][1] + "\n";
  }
  server.send(200, "text/plain", response);
    delay(1000);
      
  } else if (server.hasArg("huella")) { 
   
    Serial.println(" coloca tu dedo para poderlo indentificar");

      
     scan();
     if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Estás conectado a la red WiFi.");
    Serial.println("nombre : " + h + "Id" + t);
    historial();
  } else {
    Serial.println("No estás conectado a la red WiFi.");
  }
      delay(1000);
      server.sendHeader("Location", "/", true);
      server.send(302, "text/plain", "");
    }
  else {
    // Si no se cumple ninguna de las condiciones anteriores, redirige al cliente a la página principal
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
  }

  html += "no hay trascion de datos";
  server.send(200, "text/html", html);
}



//////////////////////////////////////////// agregar base de datos /////////////

void agregar() {


  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > watchdog) {
    previousMillis = currentMillis;
    WiFiClient client;

    if (!client.connect(host, port)) {
      Serial.println("No se pudo conectar");
      return;
    }

    
    String url = "/AppCerradura/Agre.php?cerrad=";
    url += IDcerradura;
    url += "&Nombre=";
    url += h;
    url += "&Nhuellas=";
    url += t;
        Serial.println(IDcerradura + h + t );
    // Send request to the server
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

    // Read the server's response
    while(client.available()) {
      String line = client.readStringUntil('\r');
      Serial.println(line);
    }
  }
  delay(800);
}

//////////////////////////////////////////// eliminar base de datos /////////////

void eliminar() {


  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > watchdog) {
    previousMillis = currentMillis;
    WiFiClient client;

    if (!client.connect(host, port)) {
      Serial.println("No se pudo conectar");
      return;
    }

    
    String url = "/AppCerradura/Eliminar.php?cerrad=";
    url += IDcerradura;
    url += "&Nhuellas=";
    url += t;
        Serial.println(IDcerradura + h + t );
    // Send request to the server
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

    // Read the server's response
    while(client.available()) {
      String line = client.readStringUntil('\r');
      Serial.println(line);
    }
  }
  delay(800);
}

////////////////////////////////////////////////////////  inicio del setup //////////////////////////////////////////////////////////////

void historial(){


  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > watchdog) {
    previousMillis = currentMillis;
    WiFiClient client;

    if (!client.connect(host, port)) {
      Serial.println("No se pudo conectar");
      return;
    }

    
    String url = "/AppCerradura/histoo.php?cerrad=";
    url += IDcerradura;
    url += "&Nhuellas=";
    url += t;
    url += "&Nombre=";
    url += h;
        Serial.println(IDcerradura + h + t );
    // Send request to the server
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

    // Read the server's response
    while(client.available()) {
      String line = client.readStringUntil('\r');
      Serial.println(line);
    }
  }
  delay(800);
}

////////////////////////////////////////////// actualizar informacion de registro de cerradura al conectarce a la red del conjunto ///////

void actualizar(){


  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > watchdog) {
    previousMillis = currentMillis;
    WiFiClient client;

    if (!client.connect(host, port)) {
      Serial.println("No se pudo conectar");
      return;
    }

    
    String url = "/AppCerradura/histoo.php?cerrad=";
    url += IDcerradura;
    url += "&Nhuellas=";
    url += t;
    url += "&Nombre=";
    url += h;
        Serial.println(IDcerradura + h + t );
    // Send request to the server
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

    // Read the server's response
    while(client.available()) {
      String line = client.readStringUntil('\r');
      Serial.println(line);
    }
  }
  delay(800);
}


void setup() {
  
  pinMode(sensorPin, INPUT);
  pinMode(ledrojo,  OUTPUT);
  pinMode(ledverde,  OUTPUT);
  pinMode(ledamarillo, OUTPUT);
  pinMode(ledazul,  OUTPUT);
  Serial.begin(115200);
  
  digitalWrite(ledazul, HIGH);  // Encender el LED
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
  Serial.println("");
  Serial.println("Dirección IP del Punto de Acceso: ");
  Serial.println(WiFi.softAPIP());

    unsigned long startTime = millis();
  unsigned long elapsedTime = 0;
  

  //////////////////////////////////////// lector de huellla /////////
  
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);

  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Encontrado sensor de huellas dactilares");

 finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("El sensor no contiene ningún dato de huellas dactilares.");
    Serial.print("Recuerda que la cantidad maxima de huellas para guardar es de 8");
 
   delay(4000);
    Menu= true;
  }
  else {
      Serial.print("El sensor contiene "); Serial.print(finger.templateCount); Serial.println(" plantillas");
  delay(2000); 

     Menu= true;
      }
  delay(2000);
  
  } else {
    Serial.println("No encontré el sensor de huellas dactilares :(");
    while (1); 
  }
}

/////////////////////////////  void loop //////////////////
void loop() {
  if (Menu == true) {
    Serial.println("Menu");
    Menu = false;
  }
 int sensorValue = digitalRead(sensorPin);

  // Si el sensor táctil está activado (tocado), enciende el LED y muestra un mensaje en el monitor serial
  if (sensorValue == HIGH) {
    Serial.println("Sensor táctil tocado");
      unsigned long startTime = millis(); // Obtener el tiempo de inicio
  while (millis() - startTime < 10000) { // Esperar 10 segundos
    getFingerprintID();
    delay(50);
  }
  } else {
    Serial.println("Sensor táctil no tocado");
     delay(1000);
  }

  
  server.handleClient();
  if (server.client().connected() && !clienteConectado) {
   /// Serial.println("Conexión establecida");
    clienteConectado = true;
  } else if (!server.client().connected() && clienteConectado) {
    Serial.println("Cliente desconectado");
    clienteConectado = false;
  }
}

///////////////////////////// fin void loop //////////////////
void accion_3() {
  Serial.println("Listo para inscribir una huella digital.");
  Serial.println("Por favor, escriba el número de ID (de 1 a 127) en el que desea guardar esta huella...");
  id = t;
  if (id == 0) {// El ID #0 no está permitido, ¡inténtelo de nuevo!
     return;
  }
  Serial.print("Inscribiendo ID #");
  Serial.println(id);

  while (!getFingerprintEnroll());
}

          
  
void accion_2(){ 
  Serial.println("Por favor, escriba el número de ID (de 1 a 127) que desea borrar...");
  uint8_t id = t;
  if (id == 0) {// ID #0 no permitido, ¡inténtelo de nuevo!
     return;
    }
  Serial.print("Borrando ID #");
  Serial.println(id);
  deleteFingerprint(id);
}

void scan(){
  unsigned long startTime = millis(); // Obtener el tiempo de inicio
  while (millis() - startTime < 10000) { // Esperar 10 segundos
    getFingerprintID();
    delay(50);
  }
  
  }
  
uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;

  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("¡Eliminado!");
  
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de comunicación");
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("No se pudo eliminar en esa ubicación");
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error al escribir en flash");
  } else {
    Serial.print("Error desconocido: 0x"); Serial.println(p, HEX);
  }

  return p;
}


uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Esperando un dedo válido para inscribirse como #"); Serial.println(id);
  delay(500);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen tomada");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");  
    digitalWrite(ledamarillo, HIGH);  // Encender el LED
    delay(200);
    digitalWrite(ledamarillo, LOW);   // Apagar el LED en otros casos
     
      
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Error de imagen");
      break;
    default:
      Serial.println("Error desconocido");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagen demasiado desordenada");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("No se pudieron encontrar funciones de huellas dactilares");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("No se pudieron encontrar funciones de huellas dactilares");
      return p;
    default:
      Serial.println("Error desconocido");
      return p;
  }

  Serial.println("quitar el dedo");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Coloque el mismo dedo nuevamente");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen tomada");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
       delay(100);
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Error de imagen");
      break;
    default:
      Serial.println("Error desconocido");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagen demasiado desordenada");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("No se pudieron encontrar funciones de huellas dactilares");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("No se pudieron encontrar funciones de huellas dactilares");
      return p;
    default:
      Serial.println("Error desconocido");
      return p;
  }

  // OK converted!
  Serial.print("Creando modelo para #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Impresiones coincidentes!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de comunicación");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Las huellas dactilares no coincidían");
    return p;
  } else {
    Serial.println("Error desconocido");
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("¡Guardado!");
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de comunicación");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error al escribir en flash");
    return p;
  } else {
    Serial.println("Error desconocido");
    return p;
  }

  return true;
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen capturada");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No se detectó un dedo");
       delay(500);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Error de imagen");
      return p;
    default:
      Serial.println("Error desconocido");
      return p;
  }

  // ¡Éxito!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagen demasiado desordenada");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("No se pudieron encontrar características de huellas dactilares");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("No se pudieron encontrar características de huellas dactilares");
      return p;
    default:
      Serial.println("Error desconocido");
      return p;
  }

  // ¡Conversión OK!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("¡Se encontró una coincidencia de huella!");
     int compareRow = finger.fingerID;

    digitalWrite(ledverde, HIGH);  // Encender el LED
    delay(4000);
    digitalWrite(ledverde, LOW);   // Apagar el LED en otros casos
  if (compareRow >= 1 && compareRow <= 8) {
    Serial.print("Fila ");
    Serial.print(compareRow);
    Serial.print(": ");
    Serial.print(names[compareRow - 1][0]);
    t= compareRow;
    h=names[compareRow - 1][0];
  
    delay(2000);
  }
    delay(4000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de comunicación");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("No se encontró una coincidencia");
    digitalWrite(ledrojo, HIGH);  // Encender el LED
    delay(9000);
    digitalWrite(ledrojo, LOW);   // Apagar el LED en otros casos
    t= 120;
    h="intruso";
    contador++;

  // Reiniciar el contador cuando alcanza 4
  if (contador > 3) {
    
    digitalWrite(ledrojo, HIGH);  // Encender el LED
    delay(2000);
    digitalWrite(ledrojo, LOW);   // Apagar el LED en otros casos
     delay(1000);
    digitalWrite(ledrojo, HIGH);  // Encender el LED
    delay(2000);
    digitalWrite(ledrojo, LOW);   // Apagar el LED en otros casos
     delay(1000);
    digitalWrite(ledrojo, HIGH);  // Encender el LED
    delay(9000);
    digitalWrite(ledrojo, LOW);   // Apagar el LED en otros casos
    contador = 0;
    Serial.println("Alerta de Segurida enviado al departamento de seguridad");
  }

    
    delay(4000);
    return p;
  } else {
    Serial.println("Error desconocido");
    return p;
  }

  // ¡Se encontró una coincidencia!
  Serial.print("ID encontrado #"); Serial.print(finger.fingerID);
  Serial.print(" con una confianza de "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// devuelve -1 si falla, de lo contrario, devuelve el ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // ¡Se encontró una coincidencia!
  Serial.print("ID encontrado #"); Serial.print(finger.fingerID);
  Serial.print(" con una confianza de "); Serial.println(finger.confidence);
  return finger.fingerID;
}
