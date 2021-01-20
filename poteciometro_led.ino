
int led = 5;        // LED en pin 5
int Poten = A0;        // potenciometro en pin A0
int BRILLO;           

void setup(){
  pinMode(led, OUTPUT);  // pin 5 como salida
  
	// Recuerda que las entradas analogicas no requieren inicializacion
 
}

void loop(){
  BRILLO = analogRead(Poten)/4;  // valor leido de entrada analogica divido por 4 ya que el arduino lee de 0 a 250 y el Potenciómetro es de 100k
  analogWrite(led, BRILLO);    // brillo del LED proporcional al giro del potenciometro
}
