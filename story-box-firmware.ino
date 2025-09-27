#include <Wire.h>
#include <hd44780.h>                      
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "config.h"
#include "data.h"

hd44780_I2Cexp lcd;

int currentPage = 0;
unsigned long lastPageSwitch = 0;
unsigned long currentPageInterval = 10000; // Will be updated from page data

void loadData();
void showCurrentPage();

void setup() {
  Serial.begin(115200);
  Serial.println("Starting up...");

  int status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) {
    Serial.print("LCD init failed, status: ");
    Serial.println(status);
    while (1);
  }
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Welcome to Story Box");
  lcd.setCursor(0, 1);
  delay(2000);

  loadData();
  
  Serial.println("Ready to display content...");
}

void loop() {
  unsigned long now = millis();
  
  if (now - lastPageSwitch > currentPageInterval) {
    currentPage++;
    if (currentPage >= TOTAL_PAGES) {
      currentPage = 0;
    }
    showCurrentPage();
    lastPageSwitch = now;
  }
}

void loadData() {
  Serial.printf("Loading %d pages...\n", TOTAL_PAGES);
  
  currentPage = 0;
  showCurrentPage();
  lastPageSwitch = millis();
  
  Serial.println("Data loaded successfully");
}

void showCurrentPage() {
  if (TOTAL_PAGES == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No data available");
    return;
  }

  PageData currentPageData = PAGES[currentPage];

  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print(currentPageData.line1);
  
  lcd.setCursor(0, 1);
  lcd.print(currentPageData.line2);
  
  lcd.setCursor(0, 2);
  lcd.print(currentPageData.line3);
  
  lcd.setCursor(0, 3);
  lcd.print(currentPageData.line4);

  currentPageInterval = currentPageData.duration * 1000UL;

  Serial.printf("Displayed page %d/%d (duration %ds): %s\n", 
                currentPage + 1, TOTAL_PAGES, 
                currentPageData.duration, currentPageData.line1);
}