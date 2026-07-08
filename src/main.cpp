#include <Arduino.h>
#include <LiquidCrystal.h>

//LCD Pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Bounce Delay
unsigned long currentTime = 0;
unsigned long prevTime = 0;
unsigned long bounceDelay = 150;

//Button States
int currentButtonState;
int prevButtonState = HIGH;

//Arist
String currentArtist = "";
String prevArtist = "";

String currentSong = "";
String prevSong = "";


//Code is setup to use pin 2

void setup()
{
  // # Columns, # Rows
  lcd.begin(16, 2);

  Serial.begin(9600);
  DDRB &= ~(1 << 2);
  PORTB |= (1 << 2);
}

void loop()
{

  currentTime = millis();

  // saving state
  if ((PINB & (1 << 2)) == 0)
  {
    currentButtonState = LOW;
  }
  else
  {
    currentButtonState = HIGH;
  }

  // Display the artist on to the screen, will be the next step

  if ((currentButtonState == LOW) && (prevButtonState == HIGH) && ((currentTime - prevTime) >= bounceDelay))
  {
    Serial.println("PLAY_PAUSE");
    prevTime = currentTime;
  } else {
    Serial.println("SPOTIFY");
    prevTime = currentTime;
  }

  
  
  



  prevButtonState = currentButtonState;



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
