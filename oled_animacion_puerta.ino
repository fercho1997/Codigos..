#include <Adafruit_GFX.h>  // Incluir librerias
#include <Adafruit_SSD1306.h>  // Incluir librerias
#include <SPI.h>
#include <Wire.h>
Adafruit_SSD1306 display;  

// IMAGEN NUEMRO 1
static const uint8_t ico [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xa1, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x1d, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x04, 0xff, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0xcf, 0x8d, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 
  0xf4, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1e, 0x00, 0x3f, 0xc4, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x88, 0x7e, 0x44, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x83, 0xcb, 0xfc, 0x44, 0xcf, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1f, 0xdf, 0xc4, 
  0x44, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x70, 0x7e, 0xfc, 0xc4, 0x44, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0x83, 0xf0, 0xec, 0x44, 0x44, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x3e, 0x04, 0xcc, 0x44, 0x44, 0xcf, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc1, 0xf8, 0x3e, 0xcc, 0x44, 
  0x44, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf7, 
  0xc1, 0xc2, 0xcc, 0x44, 0x44, 0xcf, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0x07, 0x02, 0xcc, 0x44, 0x44, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x38, 0x02, 0xcc, 0x44, 0x44, 0xcf, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf3, 0xe1, 0x52, 0xcc, 0x44, 
  0x44, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0xf3, 
  0x01, 0x82, 0xcc, 0x44, 0x44, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x21, 0xf2, 0x2d, 0x82, 0xfc, 0x44, 0x44, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xad, 0xf2, 0x78, 0x1e, 0xfc, 0x4c, 0x44, 0xdf, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xb5, 0xf2, 0x50, 0x7e, 0xfc, 0x4c, 
  0x44, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x61, 0xf2, 
  0x03, 0x80, 0xfc, 0xc4, 0x47, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xb5, 0xa7, 0xf2, 0x0c, 0x00, 0xcc, 0xc4, 0x6f, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x2d, 0xf3, 0x70, 0x00, 0xcc, 0xc4, 0xff, 0x8f, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb4, 0x6f, 0xf3, 0x80, 0x00, 0xcc, 0xcf, 
  0xfc, 0x03, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd5, 0xff, 0xf0, 
  0x00, 0x00, 0xcc, 0xff, 0x84, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x87, 0xfe, 0x70, 0x00, 0x00, 0xcc, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0xf9, 0xe0, 0x00, 0x00, 0xcf, 0xf8, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xcf, 0x80, 0x00, 0x00, 0xdf, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x3e, 0x00, 
  0x00, 0x00, 0xfc, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


// IMAGEN NUEMRO 2
static const uint8_t icon [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xa1, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x1d, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 0x08, 0x8f, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x11, 0x08, 0x9f, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 
  0xff, 0xff, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0c, 0x22, 0x11, 0x8c, 0xcf, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x22, 0x11, 0x8c, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x22, 0x11, 0x8c, 0xcf, 0x8d, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x22, 0x11, 
  0x8c, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1e, 0x22, 0x11, 0x8c, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0xa2, 0x11, 0x8c, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x83, 0xe2, 0x11, 0x8c, 0xcf, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1f, 0xe2, 0x11, 
  0x8c, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x70, 0x7e, 0xe2, 0x11, 0x8c, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0x83, 0xf0, 0xe2, 0x11, 0x8c, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x3e, 0x04, 0xe2, 0x11, 0x8c, 0xcf, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc1, 0xf8, 0x3e, 0xf2, 0x11, 
  0x8c, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf7, 
  0xc1, 0xc2, 0xe2, 0x11, 0x8c, 0xcf, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0x07, 0x02, 0xe2, 0x11, 0x8c, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x38, 0x02, 0xe2, 0x19, 0x8c, 0xcf, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf3, 0xe1, 0x52, 0xe2, 0x11, 
  0x8c, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0xf3, 
  0x01, 0x82, 0xe2, 0x11, 0x8c, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x21, 0xf2, 0x2d, 0x82, 0xe2, 0x11, 0x8c, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xad, 0xf2, 0x78, 0x1e, 0xf3, 0x99, 0x8c, 0xdf, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xb5, 0xf2, 0x50, 0x7e, 0xff, 0xff, 
  0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x61, 0xf2, 
  0x03, 0x80, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xb5, 0xa7, 0xf2, 0x0c, 0x00, 0xe2, 0x11, 0x08, 0x8f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x2d, 0xf3, 0x70, 0x00, 0xc0, 0x01, 0x08, 0x0f, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb4, 0x6f, 0xf3, 0x80, 0x00, 0xc0, 0x00, 
  0x00, 0x03, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd5, 0xff, 0xf0, 
  0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x87, 0xfe, 0x70, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0xf9, 0xe0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xcf, 0x80, 0x00, 0x00, 0xc0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x3e, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

 
// IMAGEN NUEMRO 3 
static const uint8_t icono [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x10, 0x00, 0x01, 0xa1, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x3f, 0xf1, 0x00, 0x0e, 0x1d, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x23, 0xff, 
  0x08, 0x0f, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x06, 0x21, 0x3f, 0xe8, 0x8f, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x21, 0x19, 0xfe, 0x8f, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x21, 0x11, 0x9f, 0xdf, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x21, 0x11, 
  0x8d, 0xff, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x06, 0x21, 0x11, 0x8c, 0xff, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x21, 0x11, 0x8c, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x21, 0x11, 0x8c, 0xcf, 0x8d, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe1, 0x11, 
  0x8c, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1f, 0xe1, 0x11, 0x8c, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0xe1, 0x11, 0x8c, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x83, 0xe1, 0x11, 0x8c, 0xcf, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1f, 0xe1, 0x11, 
  0x8c, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x70, 0x7e, 0xe1, 0x11, 0x8c, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0x83, 0xf0, 0xe1, 0x11, 0x8c, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x3e, 0x04, 0xe1, 0x11, 0x8c, 0xcf, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc1, 0xf8, 0x3e, 0xf1, 0x11, 
  0x8c, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf7, 
  0xc1, 0xc2, 0xf9, 0x11, 0x8c, 0xcf, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0x07, 0x02, 0xdf, 0xd1, 0x8c, 0xcf, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x38, 0x02, 0xc1, 0xff, 0x8c, 0xcf, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf3, 0xe1, 0x52, 0xc0, 0x3f, 
  0xec, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0xf3, 
  0x01, 0x82, 0xc0, 0x13, 0xfc, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x21, 0xf2, 0x2d, 0x82, 0xc0, 0x01, 0x0f, 0xdf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xad, 0xf2, 0x78, 0x1e, 0xc0, 0x01, 0x09, 0xff, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xb5, 0xf2, 0x50, 0x7e, 0xc0, 0x00, 
  0x08, 0x9f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x61, 0xf2, 
  0x03, 0x80, 0xc0, 0x00, 0x00, 0x8f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xb5, 0xa7, 0xf2, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x2d, 0xf3, 0x70, 0x00, 0xc0, 0x00, 0x00, 0x0f, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb4, 0x6f, 0xf3, 0x80, 0x00, 0xc0, 0x00, 
  0x00, 0x03, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd5, 0xff, 0xf0, 
  0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x87, 0xfe, 0x70, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0xf9, 0xe0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xcf, 0x80, 0x00, 0x00, 0xc0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x3e, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

  
// IMAGEN NUEMRO 4
static const uint8_t iconos [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf1, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x79, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0e, 0x4f, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x4f, 0xa0, 0x01, 0xa1, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x49, 0xf0, 0x0e, 0x1d, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x49, 
  0xfc, 0x4f, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0e, 0xc9, 0x9e, 0x4f, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc9, 0x93, 0xcf, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc9, 0x93, 0xff, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc9, 
  0x92, 0x7f, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0xc9, 0x92, 0x7f, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xc9, 0x92, 0x6f, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x49, 0x92, 0x6f, 0x8d, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x49, 
  0x92, 0x6f, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1e, 0x0e, 0x49, 0x92, 0x6f, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x8e, 0x49, 0x92, 0x6f, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x83, 0xce, 0xc9, 0x92, 0x6f, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1f, 0xc3, 0xc9, 
  0x92, 0x6f, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x70, 0x7e, 0xc0, 0xf9, 0x92, 0x6f, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0x83, 0xf0, 0xc0, 0xf9, 0x92, 0x6f, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x3e, 0x04, 0xc0, 0x1f, 0x92, 0x6f, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc1, 0xf8, 0x3e, 0xc0, 0x0f, 
  0x92, 0x6f, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf7, 
  0xc1, 0xc2, 0xc0, 0x01, 0xf2, 0x6f, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0x07, 0x02, 0xc0, 0x01, 0x72, 0x6f, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x38, 0x02, 0xc0, 0x01, 0x3e, 0x6f, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf3, 0xe1, 0x52, 0xc0, 0x01, 
  0x1e, 0x6f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0xf3, 
  0x01, 0x82, 0xc0, 0x00, 0x07, 0xef, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x21, 0xf2, 0x2d, 0x82, 0xc0, 0x00, 0x02, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xad, 0xf2, 0x78, 0x1e, 0xc0, 0x00, 0x00, 0x7f, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xb5, 0xf2, 0x50, 0x7e, 0xc0, 0x00, 
  0x00, 0x5f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x61, 0xf2, 
  0x03, 0x80, 0xc0, 0x00, 0x00, 0x4f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xb5, 0xa7, 0xf2, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x2d, 0xf3, 0x70, 0x00, 0xc0, 0x00, 0x00, 0x0f, 0x8f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb4, 0x6f, 0xf3, 0x80, 0x00, 0xc0, 0x00, 
  0x00, 0x03, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd5, 0xff, 0xf0, 
  0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x87, 0xfe, 0x70, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0xf9, 0xe0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xcf, 0x80, 0x00, 0x00, 0xc0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x3e, 0x00, 
  0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void setup()  
{                
   
// COMUNICACION, COLOR, TAMAÑO DE LETRA
  delay(100);  //Este retraso es necesario para que la pantalla se inicialice
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Inicializar la pantalla con la dirección I2C de 0x3C
  display.clearDisplay();  // limpiar pantalla
  display.setTextColor(WHITE);  // color
  display.setRotation(0);  // tamaño de letra
  display.setTextWrap(false);  
  display.dim(0); // Establecer brillo (0 es máximo y 1 es un poco tenue)



}  






void loop()
{
/////////////// IMAGEN NUEMRO 1  /////////////////////

  display.clearDisplay();  // // limpiar pantalla
 display.setTextSize(0); // tamaño de letra
 display.setCursor(0, 0);  // (x,y)
  display.println("Abriendo");
   display.setCursor(0,10);  // (x,y)
  display.println("Bienvenido");
  display.setCursor(0, 20);  // (x,y)
  display.println("Entra");
  display.drawBitmap(0,0,ico,160,40,WHITE);
  display.display();  // Print everything we set previousl

 ///////////////// IMAGEN NUEMRO 2 ///////////////////

  display.clearDisplay();  // // limpiar pantalla
 display.setTextSize(0); // tamaño de letra
 display.setCursor(0, 0);  // (x,y)
  display.println("Abriendo");
   display.setCursor(0,10);  // (x,y)
  display.println("Bienvenido");
  display.setCursor(0, 20);  // (x,y)
  display.println("Entra");
  display.drawBitmap(0,0,icon,160,40,WHITE);
  display.display();  // Print everything we set previousl
 
  ///////////////// IMAGEN NUEMRO 3 //////////////////////

  display.clearDisplay();  // // limpiar pantalla
 display.setTextSize(0); // tamaño de letra
 display.setCursor(0, 0);  // (x,y)
  display.println("Abriendo");
   display.setCursor(0,10);  // (x,y)
  display.println("Bienvenido");
   display.setCursor(0, 20);  // (x,y)
  display.println("Entra");
  display.drawBitmap(0,0,icono,160,40,WHITE);
  display.display();  // Print everything we set previousl
 
  ///////////////// IMAGEN NUEMRO 4 //////////////////////
  
  display.clearDisplay();  // // limpiar pantalla
 display.setTextSize(0); // tamaño de letra
 display.setCursor(0, 0);  // (x,y)
  display.println("Abriendo");
  display.setCursor(0,10);  // (x,y)
  display.println("Bienvenido");
   display.setCursor(0, 20);  // (x,y)
  display.println("Entra");
  display.drawBitmap(0,0,iconos,160,40,WHITE);
  display.display();  // Print everything we set previousl
 delay(3000) ;

  ///////////////// IMAGEN NUEMRO 4 //////////////////////
  
  display.clearDisplay();  // // limpiar pantalla
 display.setTextSize(0); // tamaño de letra
 display.setCursor(0, 0);  // (x,y)
  display.println("Cerrar");
 display.setCursor(0,10);  // (x,y)
  display.println("Cuidate");
  display.setCursor(0, 20);  // (x,y)
  display.println("chao");
  display.drawBitmap(0,0,iconos,160,40,WHITE);
  display.display();  // Print everything we set previousl
  
 ///////////////// IMAGEN NUEMRO 3 //////////////////////
  
 display.clearDisplay();  // // limpiar pantalla
 display.setTextSize(0); // tamaño de letra
 display.setCursor(0, 0);  // (x,y)
  display.println("Cerrar");
   display.setCursor(0,10);  // (x,y)
  display.println("Cuidate");
  display.setCursor(0, 20);  // (x,y)
  display.println("chao");
  display.drawBitmap(0,0,icono,160,40,WHITE);
  display.display();  // Print everything we set previousl

  ///////////////// IMAGEN NUEMRO 2 //////////////////////
  
  display.clearDisplay();  // // limpiar pantalla
 display.setTextSize(0); // tamaño de letra
 display.setCursor(0, 0);  // (x,y)
  display.println("Cerrar");
  display.setCursor(0,10);  // (x,y)
  display.println("Cuidate");
   display.setCursor(0, 20);  // (x,y)
  display.println("chao");
  display.drawBitmap(0,0,icon,160,40,WHITE);
  display.display();  // Print everything we set previousl

 ///////////////// IMAGEN NUEMRO 1 //////////////////////
  
  display.clearDisplay();  // // limpiar pantalla
 display.setTextSize(0); // tamaño de letra
 display.setCursor(0, 0);  // (x,y)
  display.println("Cerrar");
   display.setCursor(0,10);  // (x,y)
  display.println("Cuidate");
   display.setCursor(0, 20);  // (x,y)
  display.println("chao");
  display.drawBitmap(0,0,ico,160,40,WHITE);
  display.display();  // Print everything we set previousl
   delay(3000) ;
}
