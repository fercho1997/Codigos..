#include <Adafruit_Fingerprint.h>


#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// el pin n.º 2 está ENTRADA desde el sensor (cable Amarillo)
// el pin n. ° 3 está FUERA de arduino (cable BLANCO)
// Configure el puerto serie para usar softwareserial para los pines 2 y 3 ..
SoftwareSerial mySerial(2, 3);

#else
#define mySerial Serial1

#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

int cont=1;
bool inicio = false;

int ButtGuardar=4;
int buttonG=0;

int ButtBorrar=5;
int buttonB=0;

int green_led = 8;      //Led indica puerta abierta 

void setup()
{
  Serial.begin(9600);

 pinMode(ButtGuardar,INPUT);
 pinMode(ButtBorrar,INPUT);
 digitalWrite(green_led,LOW); 
  
  while (!Serial);  
  delay(100);
  Serial.println("\n\n Inscripción del sensor de huellas dactilares de Adafruit");

  //establecer la tasa de datos para el puerto serie del sensor
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Sensor de huellas dactilares encontrado!");
    inicio=true; 
  } else {
    Serial.println("No encontré el sensor de huellas dactilares :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Lectura de parámetros del sensor"));
  finger.getParameters();
  Serial.print(F("Estado: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("sistema ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacidad: ")); Serial.println(finger.capacity);
  Serial.print(F("Nivel de seguridad: ")); Serial.println(finger.security_level);
  Serial.print(F("Dirección del dispositivo: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Longitud del paquete: ")); Serial.println(finger.packet_len);
  Serial.print(F("Tasa de baudios: ")); Serial.println(finger.baud_rate);

 finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("El sensor no contiene datos de huellas dactilares. Ejecute el ejemplo de 'inscripción'..");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("El sensor contiene"); Serial.print(finger.templateCount); Serial.println("plantillas");
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

void loop()                  
{
  if (inicio==true)
{ Serial.println("menu");
Serial.println("pulse el boton 1 para guardar nuevas huellas digitales");
Serial.println("pulse el boton 2 para borrar huellas de la base de datos");
  inicio=false;
}

////////////////////////////////Guardar nuevas huellas digitales/////////////////////////////////////////
int buttonG= digitalRead(ButtGuardar);
  if (buttonG==0&&inicio==false)
  {
  Serial.println("Listo para inscribir una huella digital!");
  //Serial.println("Escriba el número de ID (del 1 al 127) que desea guardar para este dedo como...");
  Serial.println("huella de usuario principal");
 // id = readnumber();
 id =cont;
  if (id == 0) {// ID #0 No permitido, intente de nuevo!
     return;
  }
  
  Serial.print("inscribiendo ID #");
  Serial.println(id);

  while (!  getFingerprintEnroll() );
  inicio=true;
   id=id+1;
   cont=cont+1;
  }
////////////////////////////////////////Para borrar huellas digitales/////////////////////////////////////////////////////
buttonB=digitalRead(ButtBorrar);
if (buttonB==0&&inicio==false)
  {
 Serial.println("Escriba el número de identificación (del 1 al 127) que desea eliminar...");
  uint8_t id = readnumber();
  if (id == 0) {// ID #0 No permitido, intente de nuevo!
     return;
  }

  Serial.print("Borrando identificación ID #");
  Serial.println(id);

  deleteFingerprint(id);
  inicio=true; 
  }
////////////////////////////////////////Para identificar huellas/////////////////////////////////////////////////////
 getFingerprintID();
  delay(50);          // no es necesario ejecutar esto a toda velocidad.
}


////////////////////////////////////////FUNCION para guardar huellas//////////////////////////////////////////////////////
uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Esperando un dedo válido para inscribirme como #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen tomada");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("error de imagen");
      break;
    default:
      Serial.println("Error desconocido");
      break;
    }
  }

  // OK éxito!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagen demasiado desordenado");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("No se pudieron encontrar las características de la huella digital");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("No se pudieron encontrar las características de la huella digital");
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
  Serial.println("Vuelva a colocar el mismo dedo");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen tomada");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("error de imagen");
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
      Serial.println("Imagen demasiado desordenado");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("No se pudieron encontrar las características de la huella digital");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("No se pudieron encontrar las características de la huella digital");
      return p;
    default:
      Serial.println("Error desconocido");
      return p;
  }

  // OK converted!
  Serial.print("Creando modelo para #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Creando modelo para");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de comunicación");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Las huellas dactilares no coinciden");
    return p;
  } else {
    Serial.println("Error desconocido");
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Almacenado!");


    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("error de comunicacion");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("No se pudo almacenar en esa ubicación");
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
////////////////////////////////////////FUNCION para borrar huellas digitales//////////////////////////////////////////
uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;

  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Eliminado!");
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
////////////////////////////////////////FUNCION para identificar huellas //////////////////////////////////////////////////
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen tomada");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("Ningún dedo detectado");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("error de imagen");
      return p;
    default:
      Serial.println("Error desconocido");
      return p;
  }

  // OK éxito!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagen demasiado desordenado");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("No se pudieron encontrar las características de la huella digital");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("No se pudieron encontrar las características de la huella digital");
      return p;
    default:
      Serial.println("Error desconocido");
      return p;
  }

  // OK convertido!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Encontrado una coincidencia de impresión!");
//acciones de cerradura////////////////////////
   digitalWrite(green_led,HIGH);    //Green LED turned ON, shows door OPEN
  
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

  // encontrado una coincidencia!
  Serial.print("EncontradoID #"); Serial.print(finger.fingerID);
  Serial.print("con confianza de"); Serial.println(finger.confidence);

  return finger.fingerID;
}

// devuelve -1 si falla, de lo contrario devuelve ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // encontrado una coincidencia!
  Serial.print("Encontrado ID #"); Serial.print(finger.fingerID);
  Serial.print(" con confianza de"); Serial.println(finger.confidence);
  return finger.fingerID;
}
