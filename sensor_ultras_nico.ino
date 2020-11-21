 
int TRIG = 9;     
int ECHO = 8;     
int ledrojo = 3;    
int ledverde = 2;
int DURACION;
int DISTANCIA;

void setup()
{
  Serial.begin(9600); 
  pinMode(9, OUTPUT);  
  pinMode(8, INPUT);    
  pinMode(3, OUTPUT);   
  pinMode(2, OUTPUT);   
 

}

void loop()
{
  
  digitalWrite(TRIG, HIGH);     
  delay(1);       
  digitalWrite(TRIG, LOW);    
  
  DURACION = pulseIn(8, HIGH);  
          
  DISTANCIA = DURACION / 58.2;    
  Serial.println(DISTANCIA);    
  delay(200);      

  if (DISTANCIA <= 10 && DISTANCIA >= 0){
    digitalWrite(3, HIGH);  
        digitalWrite(2, LOW);    
   }
   else{
digitalWrite(2, HIGH);   
    digitalWrite(3, LOW);   
}
}
