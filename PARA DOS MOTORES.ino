

int IN4 = 2;			// IN4 a pin digital 2
int IN3 = 3;			// IN3 a pin digital 3
int ENB = 5;			// ENB a pin digital 5
int IN2 = 7;			// IN2 a pin digital 7
int IN1 = 8;			// IN1 a pin digital 8
int ENA = 9;			// ENA a pin digital 9

void setup(){
  pinMode(IN1, OUTPUT);		// IN1 como salida	
  pinMode(IN2, OUTPUT);		// IN2 como salida
  pinMode(ENA, OUTPUT);		// ENA como salida
  pinMode(IN3, OUTPUT);		// IN3 como salida
  pinMode(IN4, OUTPUT);		// IN4 como salida
  pinMode(ENB, OUTPUT);		// ENB como salida
}

void loop(){
  digitalWrite(ENA, HIGH);	// ENA en alto habilita motor A
  digitalWrite(IN1, LOW);	// IN1 en cero logico
  digitalWrite(IN2, HIGH);	// IN2 en uno logico

  digitalWrite(ENB, HIGH);	// ENB en alto habilita motor B
  digitalWrite(IN3, LOW);	// IN3 en cero logico
  digitalWrite(IN4, HIGH);	// IN4 en uno logico
  delay(3000);			// demora de 3 seg.

  digitalWrite(ENA, LOW);	// ENA en bajo deshabilita motor A
  digitalWrite(ENB, LOW);	// ENB en bajo deshabilita motor B
  delay(2000);			// demora de 2 seg.
}
