int PIR = 2;
int RELE = 3;

void setup() 
{
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}
void loop() 
{
  if(digitalRead(2) == HIGH)
  {
    digitalWrite(3, LOW);
    Serial.println("Sensor Activado");
  }
  else
  {
    digitalWrite(3, HIGH);
    Serial.println("Modo vigilante");
  }
}
