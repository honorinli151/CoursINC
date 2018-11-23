#include "INC22_WriteFunctions.h"



//#define COMSERIAL Serial1 // pour utiliser le bluetooth ou le cable externe
#define COMSERIAL Serial // Pour utiliser le cable usb

IntervalTimer myTimer; // Evenement a interval régulier
volatile float prtc;
float ratio;
String currentBuffer;
String message;
String street_name="Joliot Curie";
String sortie="A";
volatile int hours;
volatile int minutes;
volatile int eved;
volatile int len;
volatile float d_run;
volatile float d_to_run;
volatile float d_reset;
volatile int angle = 90;
volatile float speed_now;

int next_musique = 22;
int prev_musique = 20;
int prin_musique = 21;
int reset_pin = 19;

bool starting = true;
bool control_musique = true;

int buttonState = 0;     // current state of the button
int lastButtonState = 0; // previous state of the button
int startPressed = 0;    // the time button was pressed
int endPressed = 0;      // the time button was released
int timeHold = 0;        // the time button is hold
int mode = 0;
int resetInterval = 10000;

void getDatas() // Fonction de récupération des messages
{ 
  while (COMSERIAL.available()) {    
    char current = COMSERIAL.read();
    if (current=='\r') {}
    else {
      if (current=='\n') {
        message = currentBuffer;
        currentBuffer = String("");        
        ProcessMessage(message);
      }
      else currentBuffer += (String)current;   
    }
  }  
}

void ProcessMessage(String message) {
  noInterrupts();
  if (message[0] == '#') {
    String Command = message.substring(1,5);    
    if (Command=="BATT") {
      prtc = ((float)message.substring(6,9).toInt())/100.0;
    }
    if (Command=="TIME") {
//       COMSERIAL.println(message);
       hours = (message.substring(6, 8).toInt());
       minutes = (message.substring(8,10).toInt());
//       COMSERIAL.println(hours);
//       COMSERIAL.println(minutes);
    }
    if (Command=="SPDC") {
      speed_now = ((float)message.substring(6,9).toInt())/10.0;
//       COMSERIAL.println(speed_now);
    }   
    if (Command=="NAME") {
      len = sizeof(message);
      street_name = message.substring(6,len);
//      COMSERIAL.println(message);
//      COMSERIAL.println(street_name);
    } 
    if (Command=="EVED") {
      eved = (message.substring(6,12).toInt());
//      COMSERIAL.println(message);
//      COMSERIAL.println(eved);
    } 
    if (Command=="EVET") {
      sortie = message.substring(11, 12);
      angle = (message.substring(13, 16).toInt());
//      COMSERIAL.println(sortie);
    } 
    if (Command=="DSTR") {
      d_to_run = ((float)message.substring(6, 12).toInt())/1000;
     }
     if (Command=="DSTP") {
      d_run = ((float)message.substring(6,12).toInt())/1000;
//      COMSERIAL.println(message);
//      COMSERIAL.println(d_run);
    }    
  }
  interrupts();
      
}
void setup(void)
{
  pinMode(reset_pin, INPUT);
  pinMode(prev_musique, INPUT);
  pinMode(next_musique, INPUT);
  pinMode(prin_musique, INPUT);
//  Serial.begin(9600);
//  COMSERIAL.begin(38400); // Ou 9600 selon votre cas
  COMSERIAL.begin(9600);
  myTimer.begin(getDatas, 40000);  // getDatas to run every 0.04 seconds
  display.init(); // enable diagnostic output on Serial
 
  display.update();
  delay(100);

}

void loop()
{
  welcomePage(starting);
  starting = false;
  controlMusique();
  resetButton();
  showPartialUpdate(mode);
}

void showPartialUpdate(int mode)
{ display.updateWindow(0, 0, W, H, true);
  display.setRotation(1); // pour choisir la disposition de l'écran
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.updateWindow(0, 0, W, H, false);
  drawBackground();
  if (mode == 0) {
    updateBatterieLevelIndicator(prtc);
    updateTime(hours, minutes);
    updateSpeed(speed_now);
    updateEved(sortie, eved, street_name, angle);
  }
  if (mode == 1) {
    updateBatterieLevelIndicator(prtc);
    updateTime(hours, minutes);
    updateSpeed(speed_now);
    updateInfoDistance(d_run, d_to_run, d_reset);
  }
}

void nextMusique() {
    if (digitalRead(next_musique)==HIGH) {
    COMSERIAL.println("#NEXT");
    }
}

void prevMusique() {
  if (digitalRead(prev_musique)==HIGH) {
    COMSERIAL.println("#PREV");
  }
}

void runMusiqueControl() {
  if (digitalRead(prin_musique) == HIGH) {
    control_musique = !control_musique;
    COMSERIAL.println(control_musique);
    if (control_musique == false) {
      COMSERIAL.println("#PAUS");
    }
    if (control_musique == true) {
      COMSERIAL.println("#PLAY");
    }
  }
}

void controlMusique() {
  nextMusique();
  prevMusique();
  runMusiqueControl();
}

void reset_distance() {
  d_reset = d_run;
}

void resetButton() {
  buttonState = digitalRead(reset_pin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      startPressed = millis();
    }
    else {
      endPressed = millis();
      timeHold = endPressed - startPressed;
      if (timeHold > resetInterval) {
        reset_distance();
      }
      if (timeHold<=resetInterval && timeHold>0) {
        switch(mode) {
        case 1: mode = 0; break;
        case 0: mode = 1; break;
      }
      }
    }
  }
  lastButtonState = buttonState;
}
