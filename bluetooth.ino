/// AT = verificar que todo esté bien 
/// AT+NAME? = preguntar el nombre del modulo 
/// AT+MANE= (El nombre que tu quieras)        =  escoger el nombre del modulo 
/// AT+PSWD=(Clave que tu quieras)      =   Cambiar la clave del modulo 
/// AT+AURT?  =   Mostrar los parámetros de comunicación 
/// AT+ROLE?  =   Mirar si esta en modo esclavo o maestro
/// AT+ROLE=(1,0)   = Colocar el modulo en 1 maestro 0 esclavo 
/// AT+ORGL   =   Restaurar los valores de fabrica 
/// AT+RESET  =   Volver a modo usuario listo para utilizaar 

#include <SoftwareSerial.h> 
SoftwareSerial miBT(10, 11);  
void setup(){
  Serial.begin(9600);   
  Serial.println("Comprobar comandos AT");  
  miBT.begin(38400);   
}
void loop(){
if (miBT.available())       
   Serial.write(miBT.read());   
if (Serial.available())    
   miBT.write(Serial.read());   
}
