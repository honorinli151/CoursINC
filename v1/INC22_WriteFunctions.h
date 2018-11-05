#include <GxEPD.h>
#include <GxGDE0213B1/GxGDE0213B1.h>      // 2.13" b/w

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>


#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>


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
#define EVED_C 125

#define FIRST_BLOCK 18



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
//    display.setRotation()
    display.setCursor(2,FIRST_BLOCK-MARGIN_H);
    display.print(hours);
    display.print(":");
    display.print(minutes);
}

void nextMusique() {
    Serial.println("#NEXT");
    Serial.println("NEXT Musique.");
}

void prevMusique() {
    Serial.println("#PREV");
    Serial.println("Previous Musique.");
}

void controlMusique(bool control_musique) {
  if (control_musique == false) {
    Serial.println("#PAUS");
  }
  if (control_musique == true) {
    Serial.println("#PLAY");
  }
} 

void updateEved(String sortie, int eved, String street_name) {

  display.setTextSize(1);
  display.setCursor(60, 40);
  display.print("NEXT: ");
  display.print(street_name);

  display.setTextSize(2);
  if (eved>=10000) {
    display.setCursor(EVED_C-40, 80);
    display.print(eved/1000);
    display.setCursor(EVED_C, 80);
    display.print(" km");
  }
  if (eved<10000&&eved>=1000) {
    display.setCursor(EVED_C-20, 80);
    display.print(eved/1000);
    display.setCursor(EVED_C, 80);
    display.print(" km");
  }
  if (eved<10000&&eved>=1000) {
    display.setCursor(EVED_C-20, 80);
    display.print(eved/1000);
    display.setCursor(EVED_C, 80);
    display.print(" km");
  }
  if (eved<1000&&eved>=100) {
    display.setCursor(EVED_C-60, 80);
    display.print(eved/1000);
    display.setCursor(EVED_C, 80);
    display.print(" m"); 
  }
  if (eved<100&&eved>=10) {
    display.setCursor(EVED_C-40, 80);
    display.print(eved/1000);
    display.setCursor(EVED_C, 80);
    display.print(" m"); 
  }
  if (eved<=10) {
    display.setCursor(EVED_C-20, 80);
    display.print(eved/1000);
    display.setCursor(EVED_C, 80);
    display.print(" m"); 
  }
  display.setTextSize(1);
  display.setCursor(90, 110);
  display.print("Exit No. ");
  display.print(sortie);
}

void drawWelcomePage() {
  display.updateWindow(0, 0, W, H, true);
  const char* euro_detect = "EuroDetect";
  // display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setRotation(1.5);
  display.setCursor(70, 60);
  display.setTextSize(1);
  display.print(euro_detect);
  display.setCursor(80,70);
  display.print("Welcome!");
  // delay(2000);
  // display.fillScreen(GxEPD_WHITE);
}

void drawChargingPage() {
  display.updateWindow(0, 0, W, H, true);
  const char* euro_detect = "EuroDetect";
  // display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setRotation(1.5);
  display.setCursor(70, 60);
  display.setTextSize(1);
  display.updateWindow(0, 0, W, H, false);
//  display.fillRect(0, 0, W, H, GxEPD_WHITE);
//  display.print(euro_detect);
  display.setCursor(80,10);
  display.print("Charging...");
  // delay(2000);
  // display.fillScreen(GxEPD_WHITE);
}
void updateInfoDistance(int distance_to_run, int distance_run,int time_remained,int distance_accum) {
  display.setCursor(40, 45);
  display.print("Distance covered: ");
  display.print(distance_run);
  display.print(" m");
  display.setCursor(40, 75);
  display.print("Distance to cover: ");
  display.print(distance_to_run);
  display.print(" m");
  display.setCursor(40, 105);
  display.print("From last reset: ");
  display.print(distance_accum);
  display.print(" m");
}

void drawBackground() {
  display.fillRect(0, 0, W, H, GxEPD_WHITE);
  display.drawLine(0, FIRST_BLOCK, W, FIRST_BLOCK, GxEPD_BLACK); // premiere ligne horizontale
  drawBatterieLevelIndicator();
}
