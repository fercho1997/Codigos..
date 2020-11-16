#include <IRremote.h>
int receptor = 11;
int intmag=6;
int ledAmar=5;
int ledverde=4; 
int ledrojo=3;
int rele=2;
int estado=0;


IRrecv irrecv(receptor);
decode_results codigo; //OBJETO CODIGO DE CLASE decode_result, oriundo de IRremote.h
 
void setup(){
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // INICIA LA RECEPCIÓN
   pinMode(6, OUTPUT);
  pinMode(5, INPUT);
 pinMode(4, INPUT);
  pinMode(3, INPUT);
   pinMode(2, OUTPUT);  // pin 2 como salida
}

void loop(){

  if (irrecv.decode(&codigo))
 {
Serial.println(codigo.value, HEX);

  
      if (codigo.value==0x90)//CÓDIGO DEL NÚMERO  PARA ACTIVAR RELE
      {
  {
  
 estado = digitalRead(6);
  if (estado==1)
  {
    Serial.println("cerrado");
     digitalWrite(5,LOW);
     digitalWrite(4,HIGH);
     digitalWrite(3,LOW);
     digitalWrite(2, HIGH);  // desactivar del modulo de rele 
          }
    else{
      Serial.println("Abierto");
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(2, LOW); // activar del modulo de rele 
        irrecv.resume();
     
    }
      }  
 } else{
    irrecv.resume();
 }
  
 if (codigo.value==0x890)//CÓDIGO DEL NÚMERO  PARA DESACTIVAR RELE
      {
           digitalWrite(5,HIGH);
           digitalWrite(4,LOW);
           digitalWrite(3,LOW);
           digitalWrite(2, HIGH);  // desactivar del modulo de rele 
           irrecv.resume();
 }
      
delay(500);

 
   } }
