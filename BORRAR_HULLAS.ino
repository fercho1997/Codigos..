

#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(10, 11);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  Serial.begin(9600);
  while (!Serial);  
  delay(100);
  Serial.println("SUSCRIBETE A MUNDO NV");

  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Sensor de huellas digitales encontrado!");
  } else {
    Serial.println("No encontré el sensor de huellas digitales :(");
    while (1);
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
  Serial.println("Escriba el número de identificación (de 1 a 127) que desea eliminar ..");
  uint8_t id = readnumber();
  if (id == 0) {
     return;
  }

  Serial.print("Eliminando ID #");
  Serial.println(id);
  
  deleteFingerprint(id);
}

uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;
  
  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
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
}
