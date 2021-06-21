/////////////// libreria para la pantalla oled //////////////////////////

#include <Adafruit_GFX.h>  // Incluir librerias
#include <Adafruit_SSD1306.h>  // Incluir librerias
#include <SPI.h>
#include <Wire.h>
Adafruit_SSD1306 display;

/////////////// libreria para el lector de huella //////////////////////////
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

/////////////// variables para el usar /////////////

int getFingerprintIDez(); //variable para llamar al lector de huellas
//int PIR = 2;  // pin 2 del arduino el sensor PIR
int buzzer = 3;  //  pin 3 del arduino para el buzzer
int bot_escaneo = 5;  //  pin 5 del arduino para el pulsador
int ledverde = 8; //  pin 8 del arduino para el led verde
int ledrojo = 9; //  pin 9 del arduino para el led rojo
int semag = 4; //  pin 4 del arduino para el sensor magnectico
bool reconocimiento = false; // llamar reconocimiento para el escaneo de huella
bool ventana=false;  /// llamar ventana para esperar que puedan serrar si es correcta la huella 
bool inicio = false;   /// se coloca un inicio como menu
int estado = 0; ///  variable para mirar el estado se sensor magnectico
int valll = 0; //  colocamos una bariable = 0 para evitar revotes de el pulsador
int contador=0; /// contador para poder habrir la ventana sin problemas 
int contador1=0; /// contador 2 para poder habilitar los sensores denuevo
bool ventan=false;/// llamar ventan para poder habrir la ventana sin problema 


/////////////////////////////////////////////// image de la huella ////////////////////////////////777777777777777777777777777777777777777777777
static const uint8_t icon [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x07, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/////////////////////////////////////////////// imagen del chulito ////////////////////////////

static const uint8_t ico [] PROGMEM = {
  0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xcf, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x1f, 0xb0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0b, 0x70, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xdf, 0xb0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0b, 0x60, 0x6a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0xcf, 0xae, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3d, 0x38, 0xd6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x6f, 0x4f, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x56, 0xd9, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0xed, 0xb6, 0xad, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xab, 0x5d, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd6, 0xbb, 0x6b, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x57, 0xb6, 0xd7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x69, 0xb7, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x6b, 0xd3, 0x77, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe2, 0xf6, 0xd9, 0x80, 0x00, 0x00,
  0x00, 0x00, 0xea, 0xa9, 0xaf, 0x80, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaa, 0x31, 0x80, 0x00, 0x00,
  0x00, 0x00, 0xfa, 0xa8, 0xdf, 0x80, 0x00, 0x00, 0x00, 0x00, 0xea, 0xaf, 0x60, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xea, 0xa7, 0x97, 0x80, 0x00, 0x00, 0x00, 0x00, 0x4a, 0xd3, 0xe0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfd, 0x6d, 0xbf, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe5, 0xb6, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xde, 0xdb, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0x6d, 0x40, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x6d, 0xb7, 0xed, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1a, 0xde, 0xad, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x76, 0x6a, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xae, 0xad, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3b, 0x5e, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xd5, 0xfc, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x1d, 0xad, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x5a, 0xd0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x04, 0xb6, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3d, 0xa0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xdb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80
};
SoftwareSerial mySerial(10, 11);  // pin 10 amarillo y PIN 11 blanco

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);







void setup()
{
  Serial.begin(9600); /// inicial comunicacion serial 

  // COMUNICACION, COLOR, TAMAÑO DE LETRA DE LA PANTALLA OLED
  delay(100);  //Este retraso es necesario para que la pantalla se inicialice
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Inicializar la pantalla con la dirección I2C de 0x3C
  display.clearDisplay();  // limpiar pantalla
  display.setTextColor(WHITE);  // color
  display.setRotation(0);  // tamaño de letra
  display.setTextWrap(false);
  display.dim(0); // Establecer brillo (0 es máximo y 1 es un poco tenue)


  pinMode(5, INPUT);
  pinMode(2, INPUT);  
  pinMode(4, OUTPUT);  
  pinMode(9, INPUT);
  pinMode(8, INPUT);
  while (!Serial);  
  delay(100);
  /////////////////////////////////////////////  primer texto en la pantalla led ///////////////
  Serial.println("Prueba de seguridad");
  display.setTextSize(0);
  display.setCursor(0, 5);  // (x,y)
  display.println(F("Prueba de "));  // Text or value to print
  display.setCursor(0, 15);  // (x,y)
  display.println(F("seguridad :) "));
  display.display();  // Print everything we set previously
  delay(2000);

  ////////////////// conecion con el lector de huellas ///////////////////////////////
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Sensor de huellas digitales encontrado!");
   delay(100);
    display.clearDisplay();  ///// limpiar la pantalla oled 
    display.setTextSize(0); ////////////// tamaño de la letra que saldra en la pantalla oled
    display.setCursor(0, 5);  // (x,y) donde saldra el texto 
    display.println(F("Sensor "));  ///// texto 
    display.setCursor(0, 15);  // (x,y)  donde saldra el texto
    display.println(F("Encontrado :) ")); ////  texto
    display.display();  /// para poder imprimir el texto escrito anterior mente 
    delay(3000);
    inicio = true; ///////// nos manda directamente al menu o al inicio 

  } else {   ///////  si no se incuentra el lector de huellas 
    
    Serial.println("No encontré el sensor de huellas digitales :(");
    delay(100);
    display.clearDisplay();  // limpiar la pantalla oled 
    display.setTextSize(0);////////////// tamaño de la letra que saldra en la pantalla oled
    display.setCursor(0, 5);  //(x,y) donde saldra el texto 
    display.println(F("Sensor No"));  ///// texto 
    display.setCursor(0, 15);  ////(x,y) donde saldra el texto 
    display.println(F("Encontrado :( ")); /// texto 
    display.display();  /// para poder imprimir el texto escrito anterior mente 
    delay(5000);
    while (1) {
      delay(1);
    }
  }

}


void loop()
{

  ////////////////////////////////// menu principal /////////////////
  if (inicio == true)
  {
    display.clearDisplay();  // limpiar la pantalla oled 
    delay(1000);
    display.setTextSize(0);//////// tamaño de la letra que saldra en la pantalla oled
    display.setCursor(0, 5);  //(x,y) donde saldra el texto 
    display.println(F("Bienvenido :)"));  /// texto 
    display.setCursor(0, 15);  //(x,y) donde saldra el texto 
    display.println(F("Esperando Intruccion"));/// texto 
    
    display.setCursor(0, 25);  //(x,y) donde saldra el texto 
    display.println(F("Sensor Desactivado"));  /// texto 
    display.display(); /// para poder imprimir el texto escrito anterior mente 

    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(4, HIGH);
    contador=0;
    inicio = false;
  }
//////////////////////////////////// colocar contador si esta el buzzer apagado ////////
 
 valll=digitalRead(5);
  if  (valll == HIGH ) // si el pin 2 para aun nivel alto
 {
  contador1=0;
Serial.println("contando"); // salir en el monitor serial Sensor Activado
   contador=1+ contador;
   delay(1000);
   Serial.println(contador); // salir en el monitor serial Sensor Activado
    if  (contador>=2)
    {
        digitalWrite(4, HIGH);
        
    display.clearDisplay();  // limpiar la pantalla oled 
    delay(1000);
    display.setTextSize(0);//////// tamaño de la letra que saldra en la pantalla oled
    display.setCursor(0, 5);  //(x,y) donde saldra el texto 
    display.println(F("sistema "));  /// texto 
    display.setCursor(0, 15);  //(x,y) donde saldra el texto 
    display.println(F(" apagandose"));/// texto 
    display.display(); /// para poder imprimir el texto escrito anterior mente 
       delay(2000);
        ventan =true;
      
       }
   
}

  /////////////////////////////// cuando hablren la ventana y suena el buzzer ///////////

  if (digitalRead(6) == HIGH) // si el pin 2 para aun nivel alto
  {
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
   
    Serial.println("Sensor Activado"); // salir en el monitor serial Sensor Activado

    display.clearDisplay();  // Clear the display so we can refresh
    delay(1000);
    display.setTextSize(0);
    display.setCursor(0, 5);  // (x,y)
    display.println(F("Bienvenido :)"));  // Text or value to print
    display.setCursor(0, 15);  // (x,y)
    display.println(F("Esperando Intruccion"));
    display.setCursor(0, 25); // (x,y)
    display.println(F("Sensor Activado"));  // Text or value to print
    display.display();  // Print everything we set previously
   

       getFingerprintID();
   delay(50);   //don't ned to run this at full speed.

         getFingerprintID();
   delay(50);   //don't ned to run this at full speed.

  getFingerprintIDez();
  delay(50);   //don't ned to run this at full speed.
 

}
////////////////////////////////// PODER TENER LA VENTANA AVIERTA /////////////////////
 while (ventan == true)
{
  contador=0;
  digitalWrite(4, HIGH);
  
    display.clearDisplay();  // limpiar la pantalla oled 
    delay(1000);
    display.setTextSize(0);//////// tamaño de la letra que saldra en la pantalla oled
    display.setCursor(0, 5);  //(x,y) donde saldra el texto 
    display.println(F("habrir  "));  /// texto 
    display.setCursor(0, 15);  //(x,y) donde saldra el texto 
    display.println(F(" ventana"));/// texto 
    display.display(); /// para poder imprimir el texto escrito anterior mente 
 valll=digitalRead(5);
  if  (valll == HIGH ) // si el pin 2 para aun nivel alto
 {
Serial.println("contando2"); // salir en el monitor serial Sensor Activado
   contador1=1+ contador1;
   delay(1000);
   Serial.println(contador1); // salir en el monitor serial Sensor Activado
    if  (contador1>=2) //////////// sii micontador pasa de 2 pulsaciones 
    {   
   
    ventan = false;
    
    display.clearDisplay();  // limpiar la pantalla oled 
    delay(1000);
    display.setTextSize(0);//////// tamaño de la letra que saldra en la pantalla oled
    display.setCursor(0, 5);  //(x,y) donde saldra el texto 
    display.println(F("encender sistema  "));  /// texto 
    display.setCursor(0, 15);  //(x,y) donde saldra el texto 
    display.println(F("cerrar ventana"));/// texto 
    display.setCursor(0, 25); //(x,y) donde saldra el texto 
    display.println(F("2 minutos de espera"));  /// texto 
    display.display(); /// para poder imprimir el texto escrito anterior mente 
Serial.println("cerrar ventana "); // salir en el monitor serial Sensor Activado
         
      delay(3000);
      inicio=true;  ///// nos envia al menu o inicio 
       }
   
    
}
}
  /////////////////////////// si la huella es correcta desactiva el sensor durante 2 minutos tenemos que serrar la ventana //////////
  while (ventana == true)

{
   digitalWrite(4, HIGH);
 
    display.clearDisplay();   // limpiar la pantalla oled 
    delay(1000);
    display.setTextSize(0); //// tamaño de la letra que saldra en la pantalla oled
    display.setCursor(0, 5);  //(x,y) donde saldra el texto 
    display.println(F("restaurar Sensor"));   /// texto 
    display.setCursor(0, 15);  //(x,y) donde saldra el texto 
    display.println(F("cerrar ventana"));
    display.setCursor(0, 25); //(x,y) donde saldra el texto 
    display.println(F("2 minutos de espera"));  /// texto 
    display.display();  /// para poder imprimir el texto escrito anterior mente
      delay(20000);
    reconocimiento=false; //// termina el reconocimento 
    
    ventana =false; ////// termina ventana 
  inicio=true;  ///// nos envia al menu o inicio 
}
}


///////// esscaneo de la huella /////////////////



uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen tomada");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No se detecta  ningún dedo");
       digitalWrite(4, LOW); ///// suena el buser si no hay ningún dedo
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

  // OK success!

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
      Serial.println("No se encontraron características de huellas digitales");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("No se encontraron características de huellas digitales");
      return p;
    default:
      Serial.println("Error desconocido");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Encontró una coincidencia de impresión!");
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
   digitalWrite(4, HIGH);
    display.clearDisplay();   // limpiar la pantalla oled 

    display.setTextSize(0);
    display.drawBitmap(80, 0, icon, 60, 120, WHITE);  ///// mostar la imagen de la huella 

    display.drawBitmap(10, 0, ico, 60, 60, WHITE);  ////// mostrar el chulo 
    delay(3000);
    display.display();  //////// mostar el nuemero de la huella identificada
    delay(3000);


    display.clearDisplay();   // limpiar la pantalla oled 
    display.setTextSize(0);
    display.setCursor(15, 10);  // (x,y)
    display.println("Huella Incontrada ");  /// /// texto 
    display.setCursor(47, 20);  ///// (x,y)
    display.println(" N"); /// texto 
    display.setCursor(67, 20);  // (x,y)
    display.println(finger.fingerID);  ///// mostar el nuemero de la huella identificada
    
    display.display();  /// para poder imprimir el texto escrito anterior mente 
    ventana=true;      ////// nos envia a ventana donde tendremos 2 minutos para cerrar la ventana 
    delay(1000);
  
 
    

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de comunicación");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("No encontré una coincidencia");
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
    display.clearDisplay();  // Clear the display so we can refresh

    display.setTextSize(0);
    display.setCursor(8, 3);  // (x,y)
    display.println(F(" Retirese Intruso "));   /// texto 
    display.display();  /// para poder imprimir el texto escrito anterior mente
    delay(5000);
    delay(2000);
    digitalWrite(4, LOW);
    return p;
  } else {
    Serial.println("Error desconocido");
    return p;
  }

  // huella incontrada!
  Serial.print("Encontrado ID #"); Serial.print(finger.fingerID);
  Serial.print("con la confianza de "); Serial.println(finger.confidence);

  return finger.fingerID;
   
}


// returns -1 if failed, otherwise returns ID #

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  /// aqui se comprueva la guella

  Serial.print("Encontrado ID #"); Serial.print(finger.fingerID);

  Serial.print(" con la confianza de "); Serial.println(finger.confidence);
  return finger.fingerID;
  {
    getFingerprintIDez();
    delay(50);            //don't ned to run this at full speed.

    finger.fingerID = -1;
  }
}
