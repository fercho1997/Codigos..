/*
Ejemplo basico de texto para la pantalla OLED 128x64 I2C con el driver SSD1306.

Este ejemplo es de dominio publico hagan lo que quieran con el :D
Autor: Sergio A. Yañez M.
Año: 2019
Tutorial para el canal AQUILES VAESA 
youtube.com/aqulesvaesa

***** CONEXIONES *****

DISPLAY - ARDUINO
    GND = GND
    VCC = 5V ó 3.3V
    SCL = A5
    SDA = A4

Importante!!! necesitas instalar estas librerias:
https://github.com/adafruit/Adafruit-GFX-Library
https://github.com/adafruit/Adafruit_SSD1306

*/

#include <Adafruit_SSD1306.h>  // incluye la libreria de adafruit para el driver del display OLED

Adafruit_SSD1306 display(128, 64);  // declara la resolucion del display

int cont=0;
int tam=0;
void setup(){                

  delay(100);  // se da una espera de 100ms para que el display inicie correctamente
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // inicia la comunicacion I2C con el display que tiene la direccion 0x3C
  display.setRotation(0);  // se escoje la orientacion del display puede ser 0, 1, 2 o 3
  display.setTextColor(WHITE);  // se le dice a la pantalla que el texto que se va a desplegar es en color blanco 

  display.dim(true); //dejamos el brillo en minimo 

  //esto solo es visible al iniciar el programa:
  
  display.clearDisplay();  // limpia el buffer del display
  display.setTextSize(2);  // cambia tamaño de letra a 2 
  display.setCursor(0, 0); //(x,y) pone el cursor en el origen del display 
  display.println("Iniciando"); //escribe en buffer del display
  display.display(); // muestra la informacion del buffer en la pantalla 
  delay(2000); //pausa de 2 segundos o 2000 milisegundos 
} 

void loop(){

// primera pantalla de presentacion 
  
  display.dim(true); // brillo maximo 
  
  display.clearDisplay();  
  display.setTextSize(1); // selecciona el tamaño de la letra puede ser u entre 1 y 10
  display.setCursor(0, 0);  // (x,y) pone el cursor en el origen del display
  display.println("CANAL AQUILES VAESA"); 
  display.setCursor(0, 30);  // (x,y) pone el cursor mas o menos en la mitad horizontal del display
  display.println("youtube.com/aquilesvaesa");
  display.setCursor(30, 50); //(x,y) 
  display.println(">  Suscribete  <");
  display.display(); 
  delay(5000); //pausa de 5 segundos o 5000 milisegundos


// segundo pantallazo, bajamos el brillo del display 
 
  display.dim(true); //dejamos el brillo en minimo 
  
  display.clearDisplay();  
  display.setTextSize(2);  // cambia tamaño de letra a 2 
  display.setCursor(0, 0);  
  display.println("Escala de letra 2.  Probando texto largo y desborde"); //Por defecto el texto largo se desborda y continua en la siguiente linea
  display.display(); 
  delay(5000);

// tercer pantallazo

  display.clearDisplay();  
  display.setTextWrap(false); // desactiva el desborde de texto
  display.setTextSize(2);  
  display.setCursor(0, 0);  
  display.println("Desborde desactivado con la instruccion display.setTextWrap(false) ...");
  display.display(); 
  delay(5000);

// cuarto pantallazo
  
  display.clearDisplay();  
  display.setTextWrap(true); // activa el desborde de texto
  display.setTextSize(1);  
  display.setCursor(0, 30);  
  display.println("Vamos a desplegar una variable entera en diferentes escalas del 1 al 9 ");
  display.display(); 
  delay(7000);

// pantalla final varia con el incremento de las variables de los ciclos "for" 

  for(int tam = 1; tam < 10; tam++){  // creamos un ciclo con la variable tam (tamaño) que va desde 1 hasta 9
    display.setTextSize(tam); // usa la variable tam para cambiar el tamaño del texto en cada ciclo
      for(int cont=0; cont<10; cont++){ //creamos un ciclo con la variable cont (contador) que va de 0 a 9 y se muestra en la pantalla
        display.clearDisplay();
        display.setCursor(0, 0);  
        display.println(cont); // escribe el valor de la variable en el bufer 
        display.display(); 
        delay(100);
      }

  } 
  
}  // Final de la funcion principal, salta al inicio del "void loop"
