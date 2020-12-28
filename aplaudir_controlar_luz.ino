

int Mosonido = 2;       // pin 2 modulo de sonido 
int rele = 3;        // pin 3 control del rele
int estado=0;     // comparar si mi estado es alto o bajo
int encender=0;    // si mi estado es alto encender el rele 
int anterior=0;    // nos regresa al estado de apagdao 

void setup(){
  pinMode(2, INPUT);      // pin 2 como entrada
  pinMode(3, OUTPUT);     // pin 3 como salida
}


void loop(){
 
 estado = digitalRead(2);

 if (estado && anterior == 0) { // si el estado es 0 se enciende el rele
   encender = 1 - encender;   // si mi estado ya esta 1 yama la funcion de encender 
   delay (30); 
 }
 anterior = estado;

 if (encender)   // funcion llamada cuando es 1 
 {
 digitalWrite (3, HIGH); // encender el modulo rele

 }
  else {    // funcion llamada cuando es diferente a 1
  digitalWrite (3, LOW);  // apagar el modulo rele el modulo rele

  }
 }
