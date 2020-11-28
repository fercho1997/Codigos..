#include <IRremote.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(2,3,4,5,6,7);
int BUZZER_ACTIVO = 13;  
int ledrojo = 12;
int RECV_PIN = 11;
int BUZZER_ACTIVO2 = 10;
int sensor2 = 9;
int sensor1 = 8;
int encendido = 0;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(13, INPUT);
  pinMode(10, INPUT);
  pinMode(12, OUTPUT);
  
  lcd.begin(16,2);

}



void loop()
{
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    irrecv.resume();
    
    if(results.value==0xFD00FF)
    {
      if(encendido == 0)
      {
        encendido = 1;
      }
      else if(encendido == 1)
      {
        encendido = 0;
      }
    }
  }
 
  
  //lcd.print(encendido)

  if(encendido == 1)
  {
    if((digitalRead(8)==LOW)&&(digitalRead(9)==LOW))
    {
    lcd.setCursor(0,0);
    lcd.print("Sistema Activado  ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    }
    if ((digitalRead(8)==HIGH)&&(digitalRead(9)==LOW))
    {
    lcd.setCursor(0,0);
    lcd.print("Movimiento      ");
    lcd.setCursor(0,1);
    lcd.print("Sensor 1 ON     ");
    digitalWrite(12,HIGH);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(12,LOW);
    digitalWrite(13, LOW);
      
    }
     if ((digitalRead(9)==HIGH)&&(digitalRead(8)==LOW))
    {
    lcd.setCursor(0,0);
    lcd.print("Movimiento      ");
    lcd.setCursor(0,1);
    lcd.print("Sensor 2 ON     ");
    digitalWrite(12,HIGH);
    digitalWrite(10, HIGH);
    delay(500);
    digitalWrite(12,LOW);
    digitalWrite(10, LOW);
    }
  }
  
  else
  { 
    lcd.setCursor(0,0);
    lcd.print("Sistema Apagado");
  }
    }
    
