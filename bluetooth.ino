
/// AT+ORGL   =   Restaurar los valores de fabrica 

////Bluetooth Esclavo

////AT
////AT+NAME=Esclavo
////AT+PSWD=1234
////AT+UART=9600,0,0
////AT+ROLE=0 (Para 0 significa Esclavo y 1 Significa Maestro)
////AT+CMODE=1 (el 1 le permite conectarse con cualquier MAC(Direccion Fisica) y 0 solo le permite conectarse
////con una MAC en particular)
////AT+ADDR (Sentencia para extraer la direccion MAC de este bluetooth)

///MAC:98d3:51:fe2d08
/// 98D3,51,FE2D08



////Bluetooth Maestro

////AT
////AT+NAME=Maestro
////AT+PSWD=1234
////AT+UART=9600,0,0
////AT+ROLE=1 (Para 0 significa Esclavo y 1 Significa Maestro)
////AT+CMODE=0 (el 1 le permite conectarse con cualquier MAC(Direccion Fisica) y 0 solo le permite conectarse con una MAC en particular)
////AT+BIND= ????//Aqui se pone la mac del dispositivo esclavo, recordemos que se debemos de cambiar los ":" por ","


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
   Serial.write(miBT.read());   // leer Bluetooth y envia a monitor serial de Arduino

if (Serial.available())     // si hay informacion disponible desde el monitor serial
   miBT.write(Serial.read());   // leer monitor serial y envia a Bluetooth

}
