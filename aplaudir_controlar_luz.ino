

int Mosonido = 2;       
int rele = 3;        
int estado=0;
int encender=0;
int anterior=0;

void setup(){
  pinMode(2, INPUT);      // pin 2 como entrada
  pinMode(3, OUTPUT);     // pin 3 como salida
}


void loop(){
   estado = digitalRead(2);

 if (estado && anterior == 0) {
   encender = 1 - encender; 
   delay (30); 
 }
 anterior = estado;

 if (encender)
 {
 digitalWrite (3, HIGH); 

 }
  else {
  digitalWrite (3, LOW);

  }
 }
