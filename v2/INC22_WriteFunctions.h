#include <GxEPD.h>
#include <GxGDE0213B1/GxGDE0213B1.h>      // 2.13" b/w

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#include GxEPD_BitmapExamples

#include "Arrow.h"

GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9); // arbitrary selection of 8, 9 selected for default of GxEPD_Class
GxEPD_Class display(io /*RST=9*/ /*BUSY=7*/); // default selection of (9), 7


// Geometry
#define W 250
#define H 122
#define CW 9
#define BAT_W 16
#define BAT_H 9
#define BAT_X 230
#define BAT_Y 4
#define MARGIN_H 4
#define EVED_C 140
#define alert_distance 100
#define screen_dir 1

#define FIRST_BLOCK 18
#define SECOND_BLOCK 169

void drawBatterieLevelIndicator() {
  display.drawLine(BAT_X-1, BAT_Y-1, BAT_X-1, BAT_Y + BAT_H/3  - 1, GxEPD_BLACK);
  display.drawLine(BAT_X-1, BAT_Y, BAT_X-1, BAT_Y + BAT_H, GxEPD_BLACK);
//  display.drawLine(BAT_X-1, BAT_Y + 2*BAT_H/3 + 1, BAT_X-1, BAT_Y + BAT_H + 1, GxEPD_BLACK);
  display.drawLine(BAT_X-1, BAT_Y-1, BAT_X+BAT_W+1, BAT_Y-1, GxEPD_BLACK);
  display.drawLine(BAT_X+BAT_W+1, BAT_Y-1, BAT_X+BAT_W+1, BAT_Y + BAT_H + 1, GxEPD_BLACK);
  display.drawLine(BAT_X-1, BAT_Y + BAT_H + 1, BAT_X+BAT_W+1, BAT_Y + BAT_H + 1, GxEPD_BLACK); 
}

void updateBatterieLevelIndicator(float batterie_percentage) {  

  drawBatterieLevelIndicator();
  display.setTextSize(1);
  if (batterie_percentage>1) batterie_percentage =1;
  display.setFont(&FreeSans9pt7b);
  
  display.fillRect(BAT_X+BAT_W*(1-batterie_percentage)+1, BAT_Y+1, BAT_W*batterie_percentage, BAT_H-1, GxEPD_BLACK);

  int cen = (int)(batterie_percentage);
  int dec = (int)(batterie_percentage*10)-cen*10;
  int uni = (int)(batterie_percentage*100-(int)(batterie_percentage*10)*10);

  display.fillRect(W - BAT_W - 5.3*CW, 0, BAT_W, BAT_H-1, GxEPD_WHITE);
    
  if (cen==1) {
    display.setCursor(W - BAT_W - 6.9*CW, FIRST_BLOCK-MARGIN_H);
    display.print("1");
  }
  if (batterie_percentage>0.1) {
   display.setCursor(W - BAT_W - 5.7*CW, FIRST_BLOCK-MARGIN_H);    
   display.print(dec);
   }
   display.setCursor(W - BAT_W - 4.5*CW, FIRST_BLOCK-MARGIN_H);
   display.print((int)(uni));
   display.setCursor(W - BAT_W - 3.3*CW, FIRST_BLOCK-MARGIN_H);
   display.print("%");  
}

void updateTime(int hours, int minutes) {
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(1);
    display.setCursor(2,FIRST_BLOCK-MARGIN_H);
    display.print(hours);
    display.print(":");
    display.print(minutes);
    // COMSERIAL.println("TIME");
}

void updateEved(String sortie, int eved, String street_name, int angle) {

  display.setTextSize(1);
  display.setCursor(60, 40);
  display.print("NEXT: ");
  display.print(street_name);

  display.setTextSize(2);
  if (eved>=10000) {
    display.setCursor(EVED_C-40, 80);
    display.print(eved/1000);
    display.setCursor(EVED_C+20, 80);
    display.print(" km");
  }
  if (eved<10000&&eved>=1000) {
    display.setCursor(EVED_C-20, 80);
    display.print(eved/1000);
    display.setCursor(EVED_C+20, 80);
    display.print(" km");
  }
  if (eved<10000&&eved>=1000) {
    display.setCursor(EVED_C, 80);
    display.print(eved/1000);
    display.setCursor(EVED_C+20, 80);
    display.print(" km");
  }
  if (eved<1000&&eved>=100) {
    display.setCursor(EVED_C-40, 80);
    display.print(eved);
    display.setCursor(EVED_C+20, 80);
    display.print(" m"); 
  }
  if (eved<100&&eved>=10) {
    display.setCursor(EVED_C-20, 80);
    display.print(eved);
    display.setCursor(EVED_C+20, 80);
    display.print(" m"); 
  }
  if (eved<=10) {
    display.setCursor(EVED_C, 80);
    display.print(eved);
    display.setCursor(EVED_C+20, 80);
    display.print(" m"); 
  }
  display.setTextSize(1);
  display.setCursor(90, 110);
  display.print("Exit No. ");
  display.print(sortie);
  if (eved<=alert_distance) {
    if (angle>80 && angle<=100) {
      // display.drawExampleBitmap(gImage_Arrow_up, EVED_C-80, 50, 40, 40, GxEPD_BLACK);
      display.drawExampleBitmap(gImage_Arrow_up, EVED_C-80, 50, 40, 40, GxEPD_WHITE);
    }
    if (angle>0 && angle<=80) {
      display.drawExampleBitmap(gImage_Arrow_right, EVED_C-80, 50, 40, 40, GxEPD_BLACK);
    } 
    if (angle>280 && angle<=360) {
      display.drawExampleBitmap(gImage_Arrow_right, EVED_C-80, 50, 40, 40, GxEPD_BLACK);
    } 
    if (angle>=100 && angle <260) {
      display.drawExampleBitmap(gImage_Arrow_left, EVED_C-80, 50, 40, 40, GxEPD_BLACK);
    }
    if (angle>260 && angle<=280) {
      display.drawExampleBitmap(gImage_Arrow_down, EVED_C-80, 50, 40, 40, GxEPD_BLACK);
    }
  }
  if (eved>alert_distance) {
    display.drawExampleBitmap(gImage_Arrow_up, EVED_C-80, 50, 40, 40, GxEPD_WHITE);
  }
}

void updateSpeed(float speed_now) {
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(1);
    display.setCursor(80,FIRST_BLOCK-MARGIN_H);
    display.print(speed_now, 1);
    display.print(" km/h");
}

void drawWelcomePage() {
  display.updateWindow(0, 0, W, H, true);
  const char* euro_detect = "EuroDetect";
  // display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setRotation(screen_dir);
  display.setCursor(70, 60);
  display.setTextSize(1);
  display.print(euro_detect);
  display.setCursor(80,80);
  display.print("Welcome!");
  // delay(2000);
  // display.fillScreen(GxEPD_WHITE);
}

void welcomePage(bool starting)  {
  if (starting==true) {
    drawWelcomePage();
  }
  starting = false;
}

void updateInfoDistance(float d_run, float d_to_run, float d_reset) {
//  display.setFont(&FreeMonoBold9pt7b);
  display.setTextSize(1);
  display.setCursor(20, 45);
  display.print("Distance run: ");
  display.print(d_run, 3);
  display.print(" km");
  display.setCursor(20, 75);
  display.print("Distance to run: ");
  display.print(d_to_run, 3);
  display.print(" km");
  display.setCursor(20, 105);
  display.print("From last reset: ");
  display.print(d_run-d_reset, 3);
  display.print(" km");
}

void drawBackground() {
  display.fillRect(0, 0, W, H, GxEPD_WHITE);
  display.drawLine(0, FIRST_BLOCK, W, FIRST_BLOCK, GxEPD_BLACK); // premiere ligne horizontale
  drawBatterieLevelIndicator();
}
