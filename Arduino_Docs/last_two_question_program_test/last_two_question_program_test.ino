//#include <Adafruit_NeoPixel.h>
//
//#define PIN 2 // le nom de la broche d'accès aux WS2812 sur la Teensy
//#define LED_COUNT 2 // le nombre de WS2812 en série
//
//int ledState1 = 0xFF5733;
//int ledState2 = 0xFF5733;
//int State1 = 0xFF5733;
//int State2 = 0xFF00FF;
//int State3 = 0x35C1FD;
//int State4 = 
//long previousMillis = 0;
//int previousMillis1 = 0;
//long interval_1 = 1000;
//long interval_2 = 2000;
//
//// Create an instance of the Adafruit_NeoPixel class called "leds".
//// That'll be what we refer to from here on...
//Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
//
//void setup() {
//  // put your setup code here, to run once:
//  leds.begin();
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  unsigned long currentMillis = millis();
//  if(currentMillis - previousMillis1 > interval_1) {
//    previousMillis1 = currentMillis; 
//    if(ledState1 == State1) {
//      ledState1 = State2;
//    }
//    else {
//      ledState1 = State1;
//    }
//    leds.setPixelColor(1, ledState1);
//    leds.show();
//  }
//  leds.setPixelColor(0, 0xFF, 0x00, 0xFF);  // Also set fourth LED to full red, no green, full blue
//  leds.show();
//}

int led1 = 20;
int led2 = 22;
int led3 = 23;
int inter = 15;
int inter_count = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(inter, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(inter), count, FALLING);
}

void loop() {
  if(inter_count==0){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  if(inter_count==1){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  if(inter_count==2){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }
  if(inter_count==3){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }
}

void count() {
  if(inter_count<4) {
    inter_count += 1;
  }
  else{
    inter_count = 0;
  }
}
