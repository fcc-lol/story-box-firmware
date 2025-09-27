#ifndef CONFIG_H
#define CONFIG_H

// LCD CONFIGURATION
const int LCD_COLS = 20;
const int LCD_ROWS = 4;

// LCD WIRING to ESP8266 via I2C
// LCD VCC → 3V3
// LCD GND → GND
// LCD SDA → D2
// LCD SCL → D1

// MEMORY CONFIGURATION
const int MAX_PAGES = 100;

#endif // CONFIG_H
