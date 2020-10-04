int ledverde=3; 
int ledrojo=5;
int botonr=2;  
int botonv= 4;
int botond= 7;
int encender=0;
int anterior=0;
int estado=0;
int val = 0;

void setup(){
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(2, INPUT);
  pinMode(5, INPUT);
}
void loop(){

 //////////////////////////// pulsador que  prende y apaga led  al precional ///////////// 
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
//////////////////////// pulsador que prende por el limete de tiempo ////////////////

 val=digitalRead(4);
if  ((val == HIGH)){
     digitalWrite(5, HIGH);    // Enciende
 delay(2000);
   digitalWrite(5, LOW);
       
 }

 ///////////// pulsador para los dos led /////////
 
  estado = digitalRead(7);
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

 val=digitalRead(7);
if  ((val == HIGH)){
     digitalWrite(5, HIGH);    // Enciende
 delay(2000);
   digitalWrite(5, LOW);
       
 }
 
}
