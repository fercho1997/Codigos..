
int led = 5;        
int Poten = A0;        
int BRILLO;

void setup(){
  pinMode(led, OUTPUT);  
 
}

void loop(){
  BRILLO = analogRead(Poten)/4; 
  analogWrite(led, BRILLO); 
}
