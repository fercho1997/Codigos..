
#include <OLED_I2C.h>

OLED  myOLED(D2, D1);
extern uint8_t SmallFont[];


void setup()
{
  myOLED.begin();
  myOLED.setFont(SmallFont);

}

void loop()
{
    
  myOLED.clrScr();
  myOLED.print("Gracias por ver ", LEFT, 3);
   myOLED.print("este video y", LEFT, 13);
  myOLED.print("suscribete:", CENTER, 30);
  myOLED.print("MUNDO NV", CENTER, 40);
  myOLED.update();
  delay (4000);
  

  
  myOLED.clrScr();
  myOLED.print("Solo hace falta", 2, 1);
  myOLED.print("que tu empieces", 2, 15);
  myOLED.print("a programa", 2, 30);
  myOLED.update();
  delay (4000);
}
