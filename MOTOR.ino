
int IN2 = 7;      // IN2 a pin digital 7
int IN1 = 8;      // IN1 a pin digital 8
int ENA = 9;      // ENA a pin digital 9

void setup(){
   pinMode(IN1, OUTPUT);   // IN1 como salida
  pinMode(IN2, OUTPUT);   // IN2 como salida
  pinMode(ENA, OUTPUT);   // ENA como salida
}

void loop(){
  
  digitalWrite(ENA, HIGH);  // habilita motor A (giro en un sentido)"ATRAS"
  digitalWrite(IN1, LOW); // IN1 a 0
  digitalWrite(IN2, HIGH);  // IN2 a 1
  delay(3000);      // demora de 3 seg.

  digitalWrite(ENA, LOW); // ENA en 0 para deshabilitar motor
  delay(2000);      // demora de 2 seg.

  digitalWrite(ENA, HIGH);  // habilita motor A (giro en sentido contrario)"ADELANTE"
  digitalWrite(IN1, HIGH);  // IN1 a 1
  digitalWrite(IN2, LOW); // IN2 a 0
  delay(3000);      // demora de 3 seg

  digitalWrite(ENA, LOW); // ENA en 0 para deshabilitar motor
  delay(2000);      // demora de 2 seg.
}
