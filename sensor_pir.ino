int PIR = 2;  // pin 2 del arduino el sensor PIR
int RELE = 3;  //  pin 3 del arduino para el RELE

void setup() 
{
  pinMode(2, INPUT);  // pin 2 como entrada
  pinMode(3, OUTPUT);   // pin 3 como salida
  Serial.begin(9600);
}
void loop() 
{
  if(digitalRead(2) == HIGH)  // si el pin 2 para aun nivel alto 
  {
    digitalWrite(3, LOW); // encender el modulo rele
    Serial.println("Sensor Activado"); // salir en el monitor serial Sensor Activado
  }
  else  // si el sensor no es un nivel alto 
  {
    digitalWrite(3, HIGH); // apagar el modulo rele el modulo rele
    Serial.println("Modo vigilante");  // salir en el monitor serial Modo vigilante
  }
}
