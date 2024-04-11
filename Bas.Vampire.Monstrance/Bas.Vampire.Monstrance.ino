/*
 Name:		Bas.Vampire.Monstrance.ino
 Created:	4/07/2024 12:19:07 PM
 Author:	Bas Paap
*/

#include <Bas.Button.h>
#include "Buzzer.h"

const int lockButtonPin = 2;
const int relicButtonPin = 3;
const int smallBuzzerPinA = 8;
const int smallBuzzerPinB = 9;
const int largeBuzzerPinA = 10;
const int largeBuzzerPinB = 11;
const int smallBuzzerSpeed = 52;
const int largeBuzzerSpeed = 52;
const unsigned long debounceDelay = 50;
const unsigned long smallBuzzDuration = 2000;
const unsigned long largeBuzzDuration = 3000;
const unsigned long delayBeforeKick = 3000;

bool isLockReleased = false;
bool isRelicRemoved = false;

Bas::Button lockButton{ lockButtonPin, debounceDelay, Bas::Button::LogLevel::none };
Bas::Button relicButton{ relicButtonPin, debounceDelay, Bas::Button::LogLevel::none };
Bas::Buzzer smallBuzzer{ smallBuzzerPinA, smallBuzzerPinB, Bas::Buzzer::LogLevel::normal };
Bas::Buzzer largeBuzzer{ largeBuzzerPinA, largeBuzzerPinB, Bas::Buzzer::LogLevel::normal };

void setup() 
{
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial);  // wait for serial port to connect. Needed for native USB port only

    Serial.println("Starting Vampire Monstrance");

    lockButton.begin(onLockButtonPressed, onLockButtonReleased);
    relicButton.begin(onRelicButtonPressed, onRelicButtonReleased);
}

void loop() 
{
    lockButton.update();
    relicButton.update();
    smallBuzzer.update();
    largeBuzzer.update();
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
        smallBuzzer.buzz(smallBuzzerSpeed, smallBuzzDuration);
    }
}

void onRelicButtonReleased()
{
    if (!isRelicRemoved)
    {
        Serial.println("Relic has been removed.");
        isRelicRemoved = true;
        largeBuzzer.buzz(largeBuzzerSpeed, largeBuzzDuration);
    }
}