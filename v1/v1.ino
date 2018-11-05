// Mmapping for Teensy LC INC 22,
// BUSY -> 7, RST -> 9, DC -> 8, CS-> 10, CLK -> 13, DIN -> 11


#include "INC22_WriteFunctions.h"



int next_musique = 22;
int prev_musique = 19;
int prin_musique = 21;
int reset_pin = 20;
int reset_count = 0;
int resetInterval = 10000;

int buttonState = 0;     // current state of the button
int lastButtonState = 0; // previous state of the button
int startPressed = 0;    // the time button was pressed
int endPressed = 0;      // the time button was released
int timeHold = 0;        // the time button is hold
int timeReleased = 0;    // the time button is released
int mode = 0;
bool control_musique=false; 
bool starting = true; 
bool charging = true;

volatile float prtc;
volatile float speed_now;
float ratio;
String currentBuffer;
String street_name="Joliot Curie";
String eved_type;
String sortie="A";
String message;
int hours=14;
int minutes=35;
int eved;
int len;
int distance_to_run;
int distance_run;
int distance_accum;
int time_remained;


void setup(void)
{
  pinMode(next_musique, INPUT);
  pinMode(prev_musique, INPUT);
  pinMode(prin_musique, INPUT);
  pinMode(reset_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(next_musique), nextMusique, FALLING);
  attachInterrupt(digitalPinToInterrupt(prev_musique), prevMusique, FALLING);
  attachInterrupt(digitalPinToInterrupt(prin_musique), runMusiqueControl, FALLING);
//  attachInterrupt(digitalPinToInterrupt(reset_pin), drawChargingPage, FALLING);
  Serial.begin(9600);
  display.init(); // enable diagnostic output on Serial
 
  ratio = 0.33;
  display.update();
//  delay(100);
}

void loop()
{
  welcomePage(starting);
  starting = false;
      buttonState = digitalRead(reset_pin);
//    Serial.println(buttonState);
//    Seiral.println("Reset button mouvement detected.")
    // button state changed
    if (buttonState != lastButtonState) { 
      drawChargingPage();
         Serial.println("Reset button mouvement detected.");
        // the button was just pressed
        if (buttonState == HIGH) {
            startPressed = millis();
            Serial.println("Pressed.");
            timeReleased = startPressed - endPressed;
            // the button was just released
        } else {
            endPressed = millis();
            timeHold = endPressed - startPressed;
            Serial.println("Holding Boutton For: ");
            Serial.println(timeHold);        
        }
        resetActionMode(timeHold);
//        resetAction(mode);
    }
    timeHold = 0;
    // save the current state as the last state,
    //for next time through the loop
    lastButtonState = buttonState;
  resetAction(mode);
//  resetBouttonDetect();
//  resetActionMode(timeHold);
//   showPartialUpdate_2();
//  pressTimeReset();
//    showPartialUpdate_2();
//  delay(200);
}

void welcomePage(bool starting)  {
  if (starting==true) {
    drawWelcomePage();
  }
  starting = false;
}

void showPartialUpdate_1()
{ 
  display.updateWindow(0, 0, W, H, true);
  display.setRotation(1.5);
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.updateWindow(0, 0, W, H, false);
  drawBackground();
  updateBatterieLevelIndicator(prtc);
  updateTime(hours, minutes);
  updateEved(sortie, eved, street_name);
}

void showPartialUpdate_2() {
    display.updateWindow(0, 0, W, H, true);
    display.setRotation(1.5);
    display.setFont(&FreeSans9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.updateWindow(0, 0, W, H, false);
    drawBackground();
    updateBatterieLevelIndicator(prtc);
    updateTime(hours, minutes);
    updateInfoDistance(distance_to_run,distance_run,time_remained,distance_accum);
}

void ProcessMessage(String message) {
  
  if (message[0] == '#') {
    String Command = message.substring(1,5);    
    if (Command=="BATT") {
      prtc  = ((float)message.substring(6,9).toInt())/100.0;
      Serial.println(prtc);  
    }
    if (Command=="CLEA") {
      display.update(); // Si vous avez besoin de rendre l'écran un peu plus propre
    } 
    if (Command=="TIME") {
       hours = (message.substring(6, 8).toInt());
       minutes = (message.substring(8,10).toInt());
       Serial.println(hours);
       Serial.println(minutes);
    }
    if (Command=="SPDC") {
      speed_now = ((float)message.substring(6,9).toInt())/10;
      display.println(speed_now);
    }
//    if (Command=="DSTR") {
//      distance_to_run = ((float)message.substring(6, 11).toInt);
//      display.println(distance_to_run);
//    }
//    if (Command=="DSTP") {
//      distance_run = ((float)message.substring(6,11).toInt());
//      display.println(distance_run);
//    }
//    if (Command=="ETAM") {
//      time_remained = ((float)message.substring(6,9).toInt());
//      display.println(time_remained);
//    }
//    if (Command=="TEMP") {
//      temp = ((float)message.substring(7,9).toInt());
//      signe = message.substring(6,7);
//      display.println(temp);
//    }    
    if (Command=="NAME") {
      len = sizeof(message);
      street_name = message.substring(7,len);
      Serial.println(eved);
    } 
    if (Command=="EVED") {
      eved = (message.substring(7,12).toInt());
      Serial.println(eved);
    } 
    if (Command=="EVET") {
      eved_type = message.substring(7,11);
      sortie = message.substring(12, 13);
      Serial.println(eved);
      Serial.println(sortie);
    } 
  }
      
}

//void resetBouttonDetect() {
//    // read the pushbutton input pin:
//    buttonState = digitalRead(reset_pin);
////    Serial.println(buttonState);
////    Seiral.println("Reset button mouvement detected.")
//    // button state changed
//    if (buttonState != lastButtonState) {
//         Serial.println("Reset button mouvement detected.");
//        // the button was just pressed
//        if (buttonState == HIGH) {
//            startPressed = millis();
//            Serial.println("Pressed.");
//            timeReleased = startPressed - endPressed;
//            // the button was just released
//        } else {
//            endPressed = millis();
//            timeHold = endPressed - startPressed;
//            Serial.println("Holding Boutton For: ");
//            Serial.println(timeHold);        
//        }
//        resetActionMode(timeHold);
////        resetAction(mode);
//    }
//    // save the current state as the last state,
//    //for next time through the loop
//    lastButtonState = buttonState;
//}

void runMusiqueControl() {
    control_musique = !control_musique;
    controlMusique(control_musique);
    Serial.println("Music contorlling...");
}

void resetActionMode(int timeHold) {
    if (timeHold>=resetInterval) {
        mode = 2;
    }
    if (timeHold > 0 && timeHold < resetInterval) {
      Serial.println("Mode Original");
      Serial.println(mode);
      switch(mode) {
        case 1: mode = 0; break;
        case 0: mode = 1; break;
        case 2: mode = 1; break;
      }
      Serial.println("Mode changed.");
      Serial.println(mode);
//      Serial.println(timeHold);
      }
}

void resetAction(int mode) {
  Serial.println("Mode in resetAction");
  Serial.println(mode);
    if (mode==0) {
        showPartialUpdate_1();
    }
    if (mode==1) {
        // display.fillRect(0, 0, W, H, GxEPD_WHITE);
        showPartialUpdate_2();
//        delay(3000);
        // display.fillRect(0, 0, W, H, GxEPD_WHITE);
//        mode = 0;
    }
    if (mode==2) {
        distance_accum = distance_run;
        distance_run = 0;
        mode = 1;
    }
}

// TODO: Detect boutton mouvement

void serialEvent() {
  while (Serial.available()) {
    char current = Serial.read();
    Serial.write(current);
    if (current=='\r') {}
    else {
      if (current=='\n') {
        message = currentBuffer;
        currentBuffer = String("");
        Serial.println(message);
        ProcessMessage(message);
      }
      else currentBuffer += (String)current;   
    }
    //delay(1);
  }
}
