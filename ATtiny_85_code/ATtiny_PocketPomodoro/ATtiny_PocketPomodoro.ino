#include <uRTCLib.h>
#include <TinyWireM.h>
#include <Tiny4kOLED.h>

uRTCLib rtc(0x68);

// OPTIMIZATION: 3-letter abbreviations remove invisible null-zero padding in Flash
const char daysOfTheWeek[7][10] PROGMEM = { "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY" };
const char monthsOfTheYear[12][4] PROGMEM = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

int8_t lastSecond = -1;
int8_t lastButtonVal = -1;
int8_t lastRTCSecond = -1; 

unsigned long lastRTCFetch = 0; 

uint8_t current_h = 0;
uint8_t current_m = 0;
uint8_t current_s = 0;
uint8_t current_month = 0;
uint8_t current_day = 0;
uint8_t current_dayOfWeek = 0;

#define BUTTON_PIN A3
#define BUZZER_PIN 4  

#define THRESHOLD_1 81   
#define THRESHOLD_2 228  
#define THRESHOLD_3 337  
#define THRESHOLD_4 419  
#define THRESHOLD_5 600  
#define THRESHOLD_NONE 800 

uint8_t currentMode = 0; 

unsigned long lastBlinkTime = 0;
const uint16_t blinkInterval = 500; 
bool blinkState = true;        
bool forceRedraw = false;      

uint16_t workTimer = 10;
uint16_t restTimer = 5;
uint16_t timerVal = 0;
bool workMode = true;
bool timerMode = false;
bool lastTimerMode = false;

bool use12HourFormat = true;

// --- Custom 8x16 OLED Icons ---
const uint8_t icon_play[] PROGMEM = {
  0x00, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00,
  0x00, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00
};

const uint8_t icon_pause[] PROGMEM = {
  0x00, 0x00, 0xFE, 0xFE, 0x00, 0xFE, 0xFE, 0x00,
  0x00, 0x00, 0x7F, 0x7F, 0x00, 0x7F, 0x7F, 0x00
};

// --- Auto-Repeat Button Variables ---
unsigned long buttonPressTime = 0; 
unsigned long lastRepeatTime = 0;  
const uint16_t HOLD_DELAY = 800;        
const uint8_t REPEAT_RATE = 150;        
bool handledLongPress = false; 
bool mute = false;

uint8_t reps = 0;

// OPTIMIZATION: Pass-by-reference (&) helper function for setting time
void adjustTime(uint8_t &val, uint8_t limit, uint8_t btn) {
  if (btn == 2) val = (val >= limit) ? 0 : val + 1; // Up
  else          val = (val == 0) ? limit : val - 1; // Down
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  
  URTCLIB_WIRE.begin();
  // rtc.set(0, 56, 12, 2, 14, 4, 25);

  oled.begin(128, 64, sizeof(tiny4koled_init_defaults), tiny4koled_init_defaults);
  oled.enableChargePump();
  oled.setRotation(1);
  oled.setFont(FONT8X16);
  oled.on();
  oled.clear();
 
  timerVal = workTimer;
  updateTimer();
}

void printSpaces(uint8_t count) {
  for (uint8_t i = 0; i < count; i++) {
    oled.write(' '); 
  }
}

void loop() {
  if (currentMode == 0) {
    if (millis() - lastRTCFetch >= 100) {
      rtc.refresh();
      lastRTCFetch = millis();
      int8_t realRTCSecond = rtc.second();

      if (realRTCSecond != lastRTCSecond) {
        if (timerMode) { 
          if (timerVal > 0) {
            timerVal -= 1;
          } else {
            if (workMode == true) {
              victoryChime(); 
              workMode = false;
              timerVal = restTimer;
            } else {
              workAlertChime(); 
              updateReps();
              workMode = true;
              timerVal = workTimer;
            } 
          } 
        } 
        
        lastRTCSecond = realRTCSecond;
        forceRedraw = true; 
      } 

      current_h = rtc.hour();
      current_m = rtc.minute();
      current_s = realRTCSecond;

      current_month = rtc.month();
      current_day = rtc.day();
      current_dayOfWeek = rtc.dayOfWeek();
    }
  }

  uint8_t btn = readDPad();
  bool triggerAction = false;

  if (btn != 0) {
    if (btn != lastButtonVal) {
      triggerAction = true;
      buttonPressTime = millis();
      lastRepeatTime = millis();
      handledLongPress = false; 
    } else {
//      if (btn == 1 && !handledLongPress) {
//        if (millis() - buttonPressTime >= 3000) {
//          mute = !mute;            
//          handledLongPress = true; 
//          forceRedraw = true;      
//        }
//      }
      if (btn == 5 && !handledLongPress) {
        if (millis() - buttonPressTime >= 3000) {
          workMode = true;
          timerVal = workTimer;
          reps = 0;
          
          oled.setFont(FONT6X8);
          oled.setCursor(2, 7);
          printSpaces(13); 
          oled.setFont(FONT8X16); 
          
          handledLongPress = true;
          forceRedraw = true; 
        }
      }
      
      if (millis() - buttonPressTime >= HOLD_DELAY) {
        if (btn == 2 || btn == 4) { 
          if (millis() - lastRepeatTime >= REPEAT_RATE) {
            triggerAction = true;
            lastRepeatTime = millis();
          }
        }
      }
    }
  }

  if (triggerAction) {
    if (btn != lastButtonVal && btn != 5 && !mute) {
      beep(); 
    }
    
    if (btn == 1) {
      if (currentMode == 0) {
        currentMode = 1;
        lastTimerMode = timerMode;
        timerMode = false; 
      } else {
        currentMode++;
        if (currentMode > 3) {
          currentMode = 0; 
          rtc.set(current_s, current_m, current_h, current_dayOfWeek, current_day, current_month, rtc.year());
          timerMode = lastTimerMode; 
        }
      }
      forceRedraw = true;
    }
    else if (btn == 2 || btn == 4) {
      // OPTIMIZATION: Consolidated logic using the pointer helper function
      if (currentMode == 1) adjustTime(current_h, 23, btn);
      else if (currentMode == 2) adjustTime(current_m, 59, btn);
      else if (currentMode == 3) adjustTime(current_s, 59, btn);
      forceRedraw = true; 
    }
    else if (btn == 3) {
      if (currentMode != 0) {
        use12HourFormat = !use12HourFormat; // Toggle AM/PM when setting hours!
        oled.setCursor(24, 1);
        printSpaces(1);
        oled.setCursor(89, 1);
        printSpaces(1);
      } else {
        timerMode = !timerMode; // Standard play/pause
      }
      forceRedraw = true; 
    }
    else if (btn == 5) {
      mute = !mute;
    }
  }
  
  lastButtonVal = btn;

  if (currentMode != 0) {
    if (millis() - lastBlinkTime >= blinkInterval) {
      blinkState = !blinkState;
      lastBlinkTime = millis();
      forceRedraw = true;
    }
  } else {
    blinkState = true;
  }

  if (current_s != lastSecond || forceRedraw) {
    updateClock(current_h, current_m, current_s);
    lastSecond = current_s;
    forceRedraw = false;
    
    updateTimer(); 
  }
}

void updateClock(uint8_t h, uint8_t m, uint8_t s) {
  oled.setCursor(32, 1);

  uint8_t display_h = h;
  bool isPM = false;

  // --- VERY CHEAP 12-HOUR MATH ---
  if (use12HourFormat) {
    oled.setCursor(24, 1);
    if (h >= 12) {
      isPM = true;
      if (h > 12) display_h = h - 12; // Converts 13-23 to 1-11
    }
    if (h == 0) display_h = 12;       // Converts Midnight (0) to 12
  }

  // Print Hours
  if (currentMode == 1 && !blinkState) printSpaces(2);
  else printTwoDigits(display_h); // <--- Use the intercepted variable here!

  oled.write(':'); 

  // Print Minutes
  if (currentMode == 2 && !blinkState) printSpaces(2);
  else printTwoDigits(m);

  oled.write(':'); 

  // Print Seconds
  if (currentMode == 3 && !blinkState) printSpaces(2);
  else printTwoDigits(s);

  // --- PRINT AM / PM ---
  if (use12HourFormat) {
    oled.setFont(FONT6X8); 
    oled.setCursor(90, 2); 
    
    if (isPM) oled.write('P'); 
    else oled.write('A');      
    
    oled.write('M');
    oled.setFont(FONT8X16); 
  } else {
    printSpaces(2); // Erase AM/PM if switched back to 24-hour
  }

  oled.setFont(FONT6X8);
  oled.setCursor(2, 0);
  
  oled.print((const __FlashStringHelper*)daysOfTheWeek[current_dayOfWeek - 1]);
  printSpaces(2);

  oled.setCursor(86, 0);
  printTwoDigits(current_day);
  oled.write(' ');
  oled.print((const __FlashStringHelper*)monthsOfTheYear[current_month - 1]);
  oled.setFont(FONT8X16);
}

void printTwoDigits(uint8_t number) {
  if (number < 10) {
    oled.write('0');
  }
  oled.print(number);
}

void updateTimer() {
  oled.setCursor(18, 4);
  
  if (workMode) oled.print(F("Work "));
  else oled.print(F("Rest "));
  
  if (timerMode) oled.bitmap(55, 4, 63, 6, icon_play);
  else oled.bitmap(55, 4, 63, 6, icon_pause);
  
  oled.setCursor(70, 4); 

  uint8_t displayMin = 0;
  uint16_t displaySec = timerVal; 
  while (displaySec >= 60) {
    displaySec -= 60;
    displayMin++;
  }
  
  printTwoDigits(displayMin); 
  oled.write(':'); 
  printTwoDigits((uint8_t)displaySec); 

  printSpaces(2);
  
  oled.setFont(FONT6X8);
  oled.setCursor(120, 7);
  if (mute) oled.write('M'); 
  else oled.write(' ');      
  oled.setFont(FONT8X16);
}

uint8_t readDPad() {
  int adcValue = analogRead(BUTTON_PIN);

  if (adcValue > THRESHOLD_NONE) return 0; 
  if (adcValue < THRESHOLD_1)    return 1; 
  if (adcValue < THRESHOLD_2)    return 2; 
  if (adcValue < THRESHOLD_3)    return 3; 
  if (adcValue < THRESHOLD_4)    return 4; 
  if (adcValue < THRESHOLD_5)    return 5; 

  return 0; 
}

void playNote(unsigned int delayTime, unsigned int cycles) {
  if (mute) return;
  for (unsigned int i = 0; i < cycles; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(delayTime);
  }
}

void beep() {
  playNote(125, 120);
}

void workAlertChime() {
  playNote(250, 160); 
  delay(80);
  playNote(250, 160);
}

void victoryChime() {
  playNote(956, 52);  
  delay(20);
  playNote(758, 66);  
  delay(20);
  playNote(638, 78);  
  delay(20);
  playNote(478, 262); 
}

void updateReps() {
  reps = (reps < 6) ? reps + 1 : 0;

  oled.setFont(FONT6X8);
  
  oled.setCursor(2, 7);
  printSpaces(13); 
  
  oled.setCursor(2, 7); 
  
  for (unsigned int i = 0; i < reps; i++) {
    oled.write('X'); 
    oled.write(' ');
  }
  
  oled.setFont(FONT8X16);
}
