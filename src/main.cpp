#include <Arduino.h>

//time

unsigned long currentTime = 0;
unsigned long prevTime = 0;
unsigned long bounceDelay = 150;


int currentButtonState;
int prevButtonState;


void setup() {
  Serial.begin(9600);
  DDRD &= ~(1<< 2);
  PORTD |= (1 << 2);
}

void loop() {

  currentTime = millis();

//saving state 
  if ((PIND & (1 << 2)) == 0) {
    currentButtonState = LOW;
  } else {
    currentButtonState = HIGH;
  }



  if ((currentButtonState == LOW) && (prevButtonState == HIGH) && ((currentTime - prevTime) >= bounceDelay)) {
    Serial.println("PLAY_PAUSE");
    prevTime = currentTime;
  } else {
    Serial.println("SPOTIFY");
    prevTime = currentTime;
  }

  
  
  



  prevButtonState = currentButtonState;


}
