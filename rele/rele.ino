

int RELE = 2;      //  pin digital 2 de Arduino


void setup(){
  pinMode(2, OUTPUT);  // pin 2 como salida
}

void loop(){
  digitalWrite(2, LOW);  // activacion del modulo de rele 
  delay(5000);      // demora de 5 seg.
  digitalWrite(2, HIGH); // apagado del modulo de rele 
  delay(5000);      // demora de 5 seg.
}
