#include "Keyboard.h"
#include "Mouse.h"

const int aButton = 2;
const int bButton = 3;
const int xLed = 5;

bool _led = false;
bool nado = false;

const unsigned long nextStep = 1000;
unsigned long nextMillis = 0;
unsigned long currentMillis = 0;
unsigned long _next = 0;

int stage=0;

void setup() { // initialize the buttons' inputs:
  pinMode(aButton, INPUT);
  pinMode(bButton, INPUT);
  pinMode(xLed, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
}


void loop() {
  currentMillis = millis();
  if (currentMillis > _next)
  {
    digitalWrite(LED_BUILTIN, _led ?  HIGH : LOW);
    _led = ! _led;
    _next = currentMillis + nextStep;
  }

  if (currentMillis > nextMillis && nado){
    ++stage;
    switch (stage){
      case 1:
      Keyboard.write('k');
      nextMillis=currentMillis + nextStep * 4;
      break;
      case 2:
      Keyboard.write('k');
      nextMillis=currentMillis + nextStep * 4;
      break;
      case 3:
      Keyboard.write('k');
      nextMillis=currentMillis + nextStep * 4;
      break;
      case 4:
      Keyboard.write('k');
      nextMillis=currentMillis + nextStep * 4;
      break;
      case 5:
      Keyboard.write('k');
      nextMillis=currentMillis + nextStep * 4;
      break;
      case 6:
      Keyboard.write('k');
      nextMillis=currentMillis + nextStep * 4;
      break;
      case 7:
      Keyboard.write('k');
      nextMillis=currentMillis + nextStep * 4;
      break;
      case 8:
      Keyboard.write('e');
      nextMillis=currentMillis + nextStep / 2;
      break;
      case 9:
      Mouse.click(MOUSE_LEFT);
      nextMillis=currentMillis + nextStep * 4;
      stage=0;
      break;
      default:
      stage=0;
      nextMillis=currentMillis + nextStep;
      break;
      }
    }

  if (digitalRead(aButton) == HIGH) {
    digitalWrite(xLed, HIGH);
    nado = true;
    stage=0;
  }

  if (digitalRead(bButton) == HIGH) {
    digitalWrite(xLed, LOW);
    nado = false ;
    stage=0;
  }
//  Keyboard.write('k');


}
