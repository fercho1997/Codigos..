#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display
#include <SPI.h>
#include <Wire.h>
Adafruit_SSD1306 display;
#include <Servo.h>
Servo controlador; 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


char pulsacion;       // almacena la tecla pulsada
int  contador = 1;    // cuenta el nivel del menu en el que se esta
bool inicio = false;
int getFingerprintIDez();

char CLAVE[5];                     // almacena en un array 4 digitos ingresados
char CLAVE_MAESTRA[5] = "1111";    // almacena en un array la contraseña inicial
byte INDICE = 0;     

uint8_t id;

SoftwareSerial mySerial(10,11);  // pin 10 AMARILLO y PIN 11 blanco 

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


const byte ROWS = 4;  //Cuatro Filas
const byte COLS = 4;  //Cuatro Columnas 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6}; //Puntos de conexion del teclado al arduino FILAS
byte colPins[COLS] = {5,4,3,2}; //Puntos de conexion del teclado al arduino COLUMNAS
Keypad Teclado1 = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //Configura el teclado
LiquidCrystal_I2C lcd(0x27,16,2); // dependiendo del fabricante del I2C el codigo 0x27 cambiar a
                                  // 0x3F , 0x20 , 0x38 , 
////////////////////////////////// Void Setup() ///////////
void setup () { 
  
 Serial.begin(9600);      // inicializa comunicacion serie
 
  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Sensor de huellas digitales encontrado!");
     delay(3000);

  
  } else {
    Serial.println("No encontré el sensor de huellas digitales :(");

 while (1) { delay(1);}
  }
}
  
uint8_t readnumber(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
   return num;
  }


  

////////////////////////// Void loop() ///////////////////////
void loop(){
  
 pulsacion = Teclado1.getKey() ;  // Lee la tecla pulsada

 if (inicio==true)
{ Serial.println("menu");
  inicio=false;
}
 if (pulsacion != NO_KEY) {      
 CLAVE[INDICE] = pulsacion;    // almacena en array la tecla presionada
    INDICE++;       // incrementa indice en uno
     Serial.print(pulsacion );
   }

    
  if(INDICE == 4)       // si ya se almacenaron los 6 digitos
  {
    if(!strcmp(CLAVE, CLAVE_MAESTRA))   {  // compara clave ingresada con clave maestra
       Serial.println(" Correcta");    // imprime en monitor serial que es correcta la clave
    accion_1();
     
    }else  {
      Serial.println(" Incorrecta");  // imprime en monitor serial que es incorrecta la clave
    INDICE = 0;
    
  inicio=true;
  }
  
    INDICE = 0;
}


  if(pulsacion == 'B'){accion_3();}
 if(pulsacion == 'C'){accion_2();}
if(pulsacion == 'D'){accion_4();}
 
}  ///////// Fin del void loop(), inician las Funciones///////////////




void accion_1(){ 
  Serial.println("escaneo");

 
     getFingerprintID();
   delay(4000);   //don't ned to run this at full speed.

  getFingerprintIDez();
  delay(4000);   //don't ned to run this at full speed.

  inicio=true;
}

void accion_2(){ 
  Serial.println("CERRAR PUERTA");
    delay(3000);
     inicio=true;
}

void accion_3(){ 
   
 pulsacion = Teclado1.getKey() ;  // Lee la tecla pulsada
  if (pulsacion != 0) {      
 
     Serial.println("eASAFs");
   
 } 
  Serial.println("ESCRIBIR");
 if(pulsacion == '0' )
 {abierto();}
inicio=true;
   }



void accion_4(){ 
  Serial.println("enrolamiento");

  
  Serial.println("¡Listo para registrar una huella digital!");
  Serial.println("Escriba el número de identificación (de 1 a 127) con el que desea guardar este dedo ...");
  id =  readnumber();
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }
  Serial.print("Enrolling ID #");
  Serial.println(id);

  while (!  getFingerprintEnroll() );
      delay(3000);
     inicio=true;
}



void error(){   
      lcd.setCursor(0,1);
      lcd.print("ERROR DE CLAVE    "); 
      inicio=true;
}

void abierto(){  
  
  Serial.println("BORAR");
      delay(3000);
      Serial.println("Escriba el número de identificación (de 1 a 127) que desea eliminar ..");
  uint8_t id = readnumber();
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }

  Serial.print("MEliminando ID #");
  Serial.println(id);
  
  deleteFingerprint(id);
   inicio=true;
 }




uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen tomada");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No se detecta  ningún dedo");
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
 

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de comunicación");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("No encontré una coincidencia");

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

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Esperando que un dedo válido se registre como #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  Serial.println("Quitar el dedo");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  Serial.print("Creando modelo para #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}


uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;
  
  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("¡Eliminado!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }   
}+*+*++*++
