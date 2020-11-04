#include <IRremote.h>
int receptor = 11;
int led = 3;
int RELE = 4;      //  pin digital 4 de Arduino
IRrecv irrecv(receptor);
decode_results codigo; //OBJETO CODIGO DE CLASE decode_result, oriundo de IRremote.h
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // INICIA LA RECEPCIÓN
  pinMode(led, OUTPUT);// pin 13 como salida 
 pinMode(RELE, OUTPUT);  // pin 4 como salida 
}
 
void loop()
{
 if (irrecv.decode(&codigo))
 {
Serial.println(codigo.value, HEX);

      if (codigo.value==0xE0E048B7)//CÓDIGO DEL NÚMERO  PARA ACTIVAR RELE
      {
           digitalWrite(RELE, LOW);  // activacion del modulo de rele 
      }

      if (codigo.value==0xE0E008F7)//CÓDIGO DEL NÚMERO PARA DESACTIVAR RELE
      {
          digitalWrite(RELE,HIGH );  // Desactivacion del modulo de rele 
      }
 if (codigo.value==0xE0E0E01F)//CÓDIGO DEL NÚMERO CERO PARA ACTIVAR LED
      {
         digitalWrite(led,HIGH); // activacion del LED
      }
 if (codigo.value==0xE0E0D02F)//CÓDIGO DEL NÚMERO  PARA DESACTIVAR LED Y RELE
      {
         digitalWrite(led,LOW); // Desactivacion del LED
         
          digitalWrite(RELE,HIGH );   // Desactivacion del modulo de rele  
      }



    
delay(500);
irrecv.resume();

 }
}
