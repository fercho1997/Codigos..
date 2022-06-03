
#include <Keypad.h>     // importa libreria Keypad

bool inicio = false;
bool inicio2 = false;
const byte FILAS = 4;     // define numero de filas
const byte COLUMNAS = 4;    // define numero de columnas
char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinesFilas[FILAS] = {9,8,7,6};   // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {5,4,3,2}; // pines correspondientes a las columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

char TECLA;       // almacena la tecla presionada
char CLAVE[8];        // almacena en un array 6 digitos ingresados
char CLAVE_MAESTRA[7] = "123456";   // almacena en un array la contraseña maestra
byte INDICE = 0;      // indice del array
byte p=0;
String nummero;
int datos [1]={0};

int fin=0;
  
void setup()
{
 Serial.begin(9600);      // inicializa comunicacion serie
 inicio2=true;

}

void loop(){
  TECLA = teclado.getKey();   // obtiene tecla presionada y asigna a variable
//datos[0]=digitalRead(TECLA);
  if (inicio2==true)
{ 
   
  if (TECLA)        // comprueba que se haya presionado una tecla
  {   // incrementa indice en uno

    
 if(TECLA == '1')       // si ya se almacenaron los 6 digitos
  {   // envia a monitor serial la tecla presionada
   Serial.println("1");
   datos[0]=1;
   Serial.print(datos[0]);
   Serial.println("copia"); 
   }
if(TECLA == '2')       // si ya se almacenaron los 6 digitos
  {   // envia a monitor serial la tecla presionada
     Serial.println("2");
      datos[0]=2;
   Serial.print(datos[0]);
     Serial.println("copia"); 
   }
   if(TECLA == '3')       // si ya se almacenaron los 6 digitos
  {   // envia a monitor serial la tecla presionada
     Serial.println("3");
      datos[0]=3;
   Serial.print(datos[0]);
   Serial.println("copia"); 
   }
   if(TECLA == '4')       // si ya se almacenaron los 6 digitos
  { 
      Serial.println("4");// envia a monitor serial la tecla presionada
    datos[0]=4;
   Serial.print(datos[0]);
   Serial.println("copia"); 
   }
   if(TECLA == '5')       // si ya se almacenaron los 6 digitos
  {   // envia a monitor serial la tecla presionada
     Serial.println("5");
    datos[0]=5;
   Serial.print(datos[0]);
   Serial.println("copia"); 
   }
   if(TECLA == '6')       // si ya se almacenaron los 6 digitos
  {   // envia a monitor serial la tecla presionada
     Serial.println("6");
      datos[0]=6;
   Serial.print(datos[0]);
   Serial.println("copia"); 
   }
   if(TECLA == '7')       // si ya se almacenaron los 6 digitos
  {   // envia a monitor serial la tecla presionada
     Serial.println("7");
      datos[0]=7;
   Serial.print(datos[0]);
   Serial.println("copia"); 
   }
   if(TECLA == '8')       // si ya se almacenaron los 6 digitos
  {   // envia a monitor serial la tecla presionada
     Serial.println("8");
      datos[0]=8;
   Serial.print(datos[0]);
   Serial.println("copia"); 
   }
   if(TECLA == '9')       // si ya se almacenaron los 6 digitos
  {   // envia a monitor serial la tecla presionada
    Serial.println("9");
    datos[0]=9;
   Serial.print(datos[0]);
   Serial.println("copia"); 
   }
   
   if(TECLA == '*')       // si ya se almacenaron los 6 digitos
  { for(int i=0;i<=8;i++){
      CLAVE[i]=p;
    }

inicio=true;

    inicio2=false;
}
  }
  
}
/// Serial.print(TECLA);    // envia a monitor serial la tecla presionada

 if (inicio==true)
{ 
 if (TECLA)        // comprueba que se haya presionado una tecla
  {
  
    CLAVE[INDICE] = TECLA;    // almacena en array la tecla presionada
    INDICE++;       // incrementa indice en uno
    Serial.println(TECLA);    // envia a monitor serial la tecla presionada

  }
///EEPROM.put(numero, valor);
    if(TECLA  == '#')       // si ya se almacenaron los 6 digitos
 {
  
    for(int i=1;i<=8;i++){
      
      if(CLAVE [i]!= '#'){
        if(CLAVE[i] == '1' || CLAVE[i] == '2' || CLAVE[i] == '3' || CLAVE[i] == '4' || CLAVE[i] == '5' || CLAVE[i] == '6' || CLAVE[i] == '7' || CLAVE[i] == '8' || CLAVE[i] == '9'){
          Serial.print(CLAVE[i]);
        }
      }
    //  Serial.print(CLAVE[i]);
      
  INDICE = 0;
    inicio=false;
  inicio2=true;
}
 } 
}}
