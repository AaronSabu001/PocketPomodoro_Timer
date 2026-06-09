#include "Open_Sans_Light_13_5_00A1_00BF_7x16.h"
#include "Open_Sans_Light_13_5_0021_003F_6x16.h"
#include "Open_Sans_Light_13_5_0400_045F_8x16.h"
#include "Open_Sans_Light_13_5_2010_2027_1x16.h"

const DCUnicodeFontRef TinyOLEDUnicodeFontOpen_Sans_Light_13_5_Fonts[4] = {
  { 0,  0, &TinyOLEDFontOpen_Sans_Light_13_5_00A1_00BF },
  { 0,  0, &TinyOLEDFontOpen_Sans_Light_13_5_0021_003F },
  { 0,  4, &TinyOLEDFontOpen_Sans_Light_13_5_0400_045F },
  { 0, 32, &TinyOLEDFontOpen_Sans_Light_13_5_2010_2027 }
};

const DCUnicodeFont TinyOLEDUnicodeFontOpen_Sans_Light_13_5 = {
  4, // the space character is a special case, and does not need to be included in the font glyphs.
  4, // number of character ranges in this unicode font
  TinyOLEDUnicodeFontOpen_Sans_Light_13_5_Fonts // the font references
};

#define FONTOPENSANSLIGHT135 (&TinyOLEDUnicodeFontOpen_Sans_Light_13_5)
