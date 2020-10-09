int ledverde=4; 
int ledrojo=3;
int botonr=5; 
int estado=0;

void setup(){
  pinMode(5, OUTPUT);
 pinMode(4, INPUT);
  pinMode(3, INPUT);
}

void loop(){
  
 estado = digitalRead(5);
  if (estado==1)
  {
    digitalWrite(4,HIGH);
       digitalWrite(3,LOW);
     }
    else{
      digitalWrite(3,HIGH);
       digitalWrite(4,LOW);
    }
 
  }
  
  
