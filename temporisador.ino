

#include <Wire.h>    // incluye libreria para interfaz I2C
#include <RTClib.h>   // incluye libreria para el manejo del modulo RTC

RTC_DS3231 rtc;     // crea objeto del tipo RTC_DS3231



int RELE = 2;      //  pin digital 2 de Arduino

void setup () {
 Serial.begin(9600);    // inicializa comunicacion serie a 9600 bps
 pinMode(2, OUTPUT);   // pin 3 como salida

 if (! rtc.begin()) {       // si falla la inicializacion del modulo
 Serial.println("Modulo RTC no encontrado !");  // muestra mensaje de error
 while (1);         // bucle infinito que detiene ejecucion del programa
 }
 rtc.adjust(DateTime(__DATE__, __TIME__)); // funcion que permite establecer fecha y horario
            // al momento de la compilacion. Comentar esta linea
}           // y volver a subir para normal operacion


void loop () {
 DateTime fecha = rtc.now();        // funcion que devuelve fecha y horario en formato
              // DateTime y asigna a variable fecha


 Serial.print(fecha.day());       // funcion que obtiene el dia de la fecha completa
 Serial.print("/");         // caracter barra como separador
 Serial.print(fecha.month());       // funcion que obtiene el mes de la fecha completa
 Serial.print("/");         // caracter barra como separador
 Serial.print(fecha.year());        // funcion que obtiene el año de la fecha completa
 Serial.print(" ");         // caracter espacio en blanco como separador
 Serial.print(fecha.hour());        // funcion que obtiene la hora de la fecha completa
 Serial.print(":");         // caracter dos puntos como separador
 Serial.print(fecha.minute());        // funcion que obtiene los minutos de la fecha completa
 Serial.print(":");         // caracter dos puntos como separador
 Serial.println(fecha.second());      // funcion que obtiene los segundos de la fecha completa
 
 delay(1000);           // demora de 1 segundo


 if ( fecha.hour() == 17 && fecha.minute() == 00 ){ // si hora = 15 y minutos = 30
   
     digitalWrite(2, HIGH); // apagado del modulo de rele 
      Serial.println( "Rele apagado" );     // muestra texto en monitor serie
     
    }             // para evitar ingresar mas de una vez
  

  
  if ( fecha.hour() == 17 && fecha.minute() == 30 ){ // si hora = 14 y minutos = 30

   digitalWrite(2, LOW);  // activacion del modulo de rele 
      Serial.println( "Rele encendido" );   // muestra texto en monitor serie
     
    }             // para evitar ingresar mas de una vez
  
  
 if ( fecha.hour() == 17 && fecha.minute() == 31 ){ // si hora = 15 y minutos = 30
    
     digitalWrite(2, HIGH); // apagado del modulo de rele 
      Serial.println( "Rele apagado" );     // muestra texto en monitor serie
    
    }             // para evitar ingresar mas de una vez
  


  if ( fecha.hour() == 17 && fecha.minute() == 32 ){ // si hora = 14 y minutos = 30
  
   digitalWrite(2, LOW);  // activacion del modulo de rele 
      Serial.println( "Rele encendido" );   // muestra texto en monitor serie
   
    }             // para evitar ingresar mas de una vez
  

 if ( fecha.hour() == 17 && fecha.minute() == 33 ){ // si hora = 15 y minutos = 30
    
     digitalWrite(2, HIGH); // apagado del modulo de rele 
      Serial.println( "Rele apagado" );     // muestra texto en monitor serie
   
    }             // para evitar ingresar mas de una vez
  
  
  if ( fecha.hour() == 17 && fecha.minute() == 34 ){ // si hora = 14 y minutos = 30
   
   digitalWrite(2, LOW);  // activacion del modulo de rele 
      Serial.println( "Rele encendido" );   // muestra texto en monitor serie
     
    }             // para evitar ingresar mas de una vez
  

 if ( fecha.hour() == 17 && fecha.minute() == 35 ){ // si hora = 15 y minutos = 30
    
     digitalWrite(2, HIGH); // apagado del modulo de rele 
      Serial.println( "Rele apagado" );     // muestra texto en monitor serie
     
    }             // para evitar ingresar mas de una vez
  
  
  if ( fecha.hour() == 18 && fecha.minute() == 00 ){ // si hora = 14 y minutos = 30
    
   digitalWrite(2, LOW);  // activacion del modulo de rele 
      Serial.println( "Rele encendido" );   // muestra texto en monitor serie
    
    }             // para evitar ingresar mas de una vez
  

 if ( fecha.hour() == 22 && fecha.minute() == 00 ){ // si hora = 15 y minutos = 30
  
     digitalWrite(2, HIGH); // apagado del modulo de rele 
      Serial.println( "Rele apagado" );     // muestra texto en monitor serie
      
    }             // para evitar ingresar mas de una vez
  

 }
