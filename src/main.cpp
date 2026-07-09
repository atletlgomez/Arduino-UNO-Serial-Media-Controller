#include <Arduino.h>
#include <LiquidCrystal.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 7

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

unsigned long lastRemoteTime = 0;
const unsigned long remoteButtonDelay = 300;

String currentArtist = "";
String currentSong = "";

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  DDRB &= ~(1 << 2);
  PORTB |= (1 << 2);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    if (millis() - lastRemoteTime >= remoteButtonDelay) {
      switch (IrReceiver.decodedIRData.command) {
        case 0x40:
          Serial.println("PLAY_PAUSE");
          break;
        case 0x43:
          Serial.println("NEXT");
          break;
        case 0x44:
          Serial.println("PREV");
          break;
        case 0x46:
          Serial.println("VOL+");
          break;
        case 0x15:
          Serial.println("VOL-");
          break;
      }
      lastRemoteTime = millis();
    }

    IrReceiver.resume();
  }

  if (Serial.available() > 0) {
    currentArtist = Serial.readStringUntil('\n');
    currentSong = Serial.readStringUntil('\n');

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(currentSong);
    lcd.setCursor(0, 1);
    lcd.print(currentArtist);
  }
}
