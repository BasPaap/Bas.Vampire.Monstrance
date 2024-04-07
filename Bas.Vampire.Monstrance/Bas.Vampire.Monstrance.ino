/*
 Name:		Bas.Vampire.Monstrance.ino
 Created:	4/07/2024 12:19:07 PM
 Author:	Bas Paap
*/

#include <Bas.Button.h>
#include <Bas.SolenoidKicker.h>
#include "Buzzer.h"

const int lockButtonPin = 2;
const int relicButtonPin = 3;
const int smallBuzzerPin = 4;
const int largeBuzzerPin = 5;
const int kickerPin = 6;
const unsigned long kickDuration = 500;
const unsigned long debounceDelay = 50;
const unsigned long smallBuzzDuration = 2000;
const unsigned long largeBuzzDuration = 3000;
const unsigned long delayBeforeKick = 3000;

bool isLockReleased = false;
bool isRelicRemoved = false;
unsigned long relicRemovalTime;
bool hasKicked = false;

Bas::Button lockButton{ lockButtonPin, debounceDelay, Bas::Button::LogLevel::normal };
Bas::Button relicButton{ relicButtonPin, debounceDelay, Bas::Button::LogLevel::normal };
Bas::Buzzer smallBuzzer{ smallBuzzerPin, Bas::Buzzer::LogLevel::normal };
Bas::Buzzer largeBuzzer{ largeBuzzerPin, Bas::Buzzer::LogLevel::normal };
Bas::SolenoidKicker kicker{ kickerPin, kickDuration, Bas::SolenoidKicker::LogLevel::normal };

void setup() 
{
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial);  // wait for serial port to connect. Needed for native USB port only

    lockButton.begin(onLockButtonPressed, onLockButtonReleased);
    relicButton.begin(onRelicButtonPressed, onRelicButtonReleased);
    kicker.begin();
}

void loop() 
{
    lockButton.update();
    relicButton.update();
    kicker.update();
  
    if (isRelicRemoved && !hasKicked)
    {
        if (millis() - (relicRemovalTime + largeBuzzDuration) >= delayBeforeKick)
        {
            Serial.println("delayBeforeKick has passed, time to kick.");
            hasKicked = true;
            kicker.kick();
        }
    }
}

void onLockButtonPressed()
{
    // Do nothing.
}

void onRelicButtonPressed()
{
    // Do nothing.
}

void onLockButtonReleased()
{
    if (!isLockReleased)
    {
        Serial.println("Lock has been released.");
        isLockReleased = true;
        smallBuzzer.buzz(smallBuzzDuration);
    }
}

void onRelicButtonReleased()
{
    if (!isRelicRemoved)
    {
        Serial.println("Relic has been removed.");
        isRelicRemoved = true;
        relicRemovalTime = millis();
        largeBuzzer.buzz(largeBuzzDuration);
    }
}