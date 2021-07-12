//////////////// ESCLAVO /////////////
char c;
void setup()
{      

//inicializa la comunicacion serial  
   Serial.begin(9600);
   
//se configura los pines de entrada y salida   
   pinMode(13,OUTPUT);
 
   
// inicializa el estdo de los LEDs   
   digitalWrite(13,LOW);
    
}

void loop() 
{
  if(Serial.available())
  {
    c=Serial.read();
    if(c=='1'){
    digitalWrite(13,HIGH);  
    
    Serial.println("led encendido ");
    }
    else if (c=='a') 
    {
      digitalWrite(13,LOW);
      
    Serial.println("led apagado");
    }
    
  }
}
