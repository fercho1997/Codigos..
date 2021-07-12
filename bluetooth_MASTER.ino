////////////////// Maestro ////////////
int val = 0;
int botonv= 4;
void setup()
{  
  Serial.begin(9600);
  pinMode(4, INPUT);
}


void loop()
{
 val=digitalRead(4);
if  ((val == HIGH)){
     Serial.write('1');
     
    Serial.println("señal 1");
 }
else {
   Serial.write('a');
   
    Serial.println("señal a");
}
}
