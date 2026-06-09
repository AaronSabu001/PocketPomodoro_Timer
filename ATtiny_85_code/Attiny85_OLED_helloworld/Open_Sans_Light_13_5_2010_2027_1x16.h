/*
  Open_Sans_Light_13_5_2010_2027
  Datacute Proportional Font 
  24 characters: U+2010 8208 ‐ to U+2027 8231 ‧
  Width: typically 1 pixels wide including 1 pixel spacing between characters
  Height: 16 pixels, 2 pages (bottom 0 rows are always blank)
  Total bytes: 75 * 2 + 24 + 2 * 2 + 11 = 189

  Converted by Datacute TinyOLED Font Converter
  Source Information:
    Manufacturer: Ascender Corporation
    Version: Version 1.10
    Vendor URL: http://www.ascendercorp.com/
    Trademark: Open Sans is a trademark of Google and may be registered in certain jurisdictions.
    Copyright: Digitized data copyright © 2010-2011, Google Corporation.
    Licence: Licensed under the Apache License, Version 2.0


  To use:

#include "Open_Sans_Light_13_5_2010_2027_1x16.h"
const DCfont *currentFont = FONTOPENSANSLIGHT13520102027;
const DCUnicodeFont *currentUnicodeFont = &TinyOLEDUnicodeFontOpen_Sans_Light_13_5_2010_2027;

*/

#include <avr/pgmspace.h>
const uint8_t ssd1306xled_fontOpen_Sans_Light_13_5_2010_2027 [] PROGMEM = {
  // U+2010 8208 ‐
  // U+2011 8209 ‑
  // U+2012 8210 ‒
  0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02, // U+2013 8211 –
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02, // U+2014 8212 —
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02, // U+2015 8213 ―
  // U+2016 8214 ‖
  0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0, // U+2017 8215 ‗
  0x20,0x18,0x00,0x00, // U+2018 8216 ‘
  0x30,0x08,0x00,0x00, // U+2019 8217 ’
  0x00,0x00,0x60,0x10, // U+201A 8218 ‚
  0x08,0x30,0x00,0x00, // U+201B 8219 ‛
  0x30,0x08,0x20,0x18,0x00,0x00,0x00,0x00, // U+201C 8220 “
  0x30,0x08,0x20,0x18,0x00,0x00,0x00,0x00, // U+201D 8221 ”
  0x00,0x00,0x00,0x00,0x60,0x10,0x40,0x30, // U+201E 8222 „
  // U+201F 8223 ‟
  0x20,0x20,0xfc,0x20,0x20,0x00,0x00,0x1f,0x00,0x00, // U+2020 8224 †
  0x20,0x20,0xfc,0x20,0x20,0x02,0x02,0x1f,0x02,0x02, // U+2021 8225 ‡
  0x80,0x80,0x01,0x01, // U+2022 8226 •
  // U+2023 8227 ‣
  // U+2024 8228 ․
  // U+2025 8229 ‥
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x00,0x10, // U+2026 8230 …
  // U+2027 8231 ‧
};
const uint8_t TinyOLEDFontOpen_Sans_Light_13_5_2010_2027_widths [] PROGMEM = {
  0,0,0,5,12,12,0,6,2,2,2,2,4,4,4,0,
  5,5,2,0,0,0,8,0
  };

const uint16_t TinyOLEDFontOpen_Sans_Light_13_5_2010_2027_widths_16s [] PROGMEM = {
  0+0+0+5+12+12+0+6+2+2+2+2+4+4+4+0,
  5+5+2+0+0+0+8+0
  };
const DCfont TinyOLEDFontOpen_Sans_Light_13_5_2010_2027 = {
  (uint8_t *)ssd1306xled_fontOpen_Sans_Light_13_5_2010_2027,
  0, // character width in pixels 0 for proportional fonts
  2, // character height in pages (8 pixels)
  16,39, // first and last low byte defining range of included character codepoints
  (uint16_t *)TinyOLEDFontOpen_Sans_Light_13_5_2010_2027_widths_16s,
  (uint8_t *)TinyOLEDFontOpen_Sans_Light_13_5_2010_2027_widths,
  1 // spacing
  };
#define FONTOPENSANSLIGHT13520102027 (&TinyOLEDFontOpen_Sans_Light_13_5_2010_2027)
