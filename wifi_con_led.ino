/// Librerias para descargar
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "Clave del TOKEN";
char ssid[] = "Nombre de la red wifi"; 
char pass[] = "Contraseña de la red wifi"; 

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass); //comunicacion con  la app Blynk
}

void loop()
{
  Blynk.run();  //conecion con  la app Blynk
}
