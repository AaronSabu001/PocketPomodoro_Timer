/*
 * Tiny4kOLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x32 displays
 *
 * Based on ssd1306xled, re-written and extended by Stephen Denne
 * from 2017-04-25 at https://github.com/datacute/Tiny4kOLED
 *
 */

#include <TinyWireM.h>
// 3868 + 111 vs 3722 + 100
#define TINY4KOLED_NO_PRINT
#include <Tiny4kOLED.h>

// ============================================================================

// Fonts that come with Tiny4kOLED
//const DCfont *currentFont = FONT6X8;
//const DCfont *currentFont = FONT6X8P;
//const DCfont *currentFont = FONT8X16;
//const DCfont *currentFont = FONT8X16P;
//const DCfont *currentFont = FONT8X16DIGITS;

// Fonts from this TinyOLED-Fonts library

// 2386 bytes in font + 3184 bytes for the program = 5570 byte total
#include "Open_Sans_Light_13_5_Unicode.h"
const DCUnicodeFont *currentFont = FONTOPENSANSLIGHT135;
#define SAMPLE "Hello World! 12345"

// 801 bytes in font + 3124 bytes for the program = 3856 byte total
//#include "Sansita_Swashed_Light_31_3_Unicode.h"
//const DCUnicodeFont *currentFont = FONTSANSITASWASHEDLIGHT313;
//#define SAMPLE "23:59:45\n+17/08-"

// 2336 bytes in font + 3124 bytes for the program = 5460 byte total
//#include "Unifont_Medium_16_Unicode.h"
//const DCUnicodeFont *currentFont = FONTUNIFONTMEDIUM16;
//#define SAMPLE "Кириллические\nшрифты.\n«Приветствую\nмир»"

// ============================================================================

uint8_t currentCharacter;

void setup() {
  // put your setup code here, to run once:

  oled.begin(128, 64, sizeof(tiny4koled_init_defaults), tiny4koled_init_defaults);
  oled.enableChargePump();
  oled.setRotation(1);
  //oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  
  //oled.setUnicodeFont(currentFont);
  oled.setFont(FONT8X16);
  
  drawScreen();
  oled.on();
  //oled.switchRenderFrame();
}

void loop() {
  delay(1000);
}

void drawScreen() {
  oled.clear();
  oled.setCursor(2, 0);
#ifndef TINY4KOLED_NO_PRINT
  oled.println(F(SAMPLE));
#else
  PGM_P p = reinterpret_cast<PGM_P>(F(SAMPLE));
  while (1) {
    byte c = pgm_read_byte(p++);
    if (c == 0) break;
    oled.write(c);
  }
#endif
}
