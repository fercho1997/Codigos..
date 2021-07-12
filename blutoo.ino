/// AT = verificar que todo esté bien 
/// AT+NAME? = preguntar el nombre del modulo 
/// AT+MANE= (El nombre que tu quieras)        =  escoger el nombre del modulo 
/// AT+PSWD=(Clave que tu quieras)      =   Cambiar la clave del modulo 
/// AT+AURT?  =   Mostrar los parámetros de comunicación 
/// AT+ROLE?  =   Mirar si esta en modo esclavo o maestro
/// AT+ROLE=(1,0)   = Colocar el modulo en 1 maestro 0 esclavo 
/// AT+ORGL   =   Restaurar los valores de fabrica 
/// AT+RESET  =   Volver a modo usuario listo para utilizaar 


#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales
        // para comunicacion serie

SoftwareSerial miBT(10, 11);  // pin 11 como RX, pin 10 como TX

void setup(){
  Serial.begin(9600);   // comunicacion de monitor serial a 9600 bps
  Serial.println("Listo");  // escribe Listo en el monitor
  miBT.begin(38400);    // comunicacion serie entre Arduino y el modulo a 38400 bps
}

void loop(){
if (miBT.available())       // si hay informacion disponible desde modulo
   Serial.write(miBT.read());   // lee Bluetooth y envia a monitor serial de Arduino

if (Serial.available())     // si hay informacion disponible desde el monitor serial
   miBT.write(Serial.read());   // lee monitor serial y envia a Bluetooth

}
