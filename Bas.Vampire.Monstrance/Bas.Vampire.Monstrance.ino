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
const int smallBuzzerSpeed = 1;
const int largeBuzzerSpeed = 127;
const unsigned long debounceDelay = 1000;
const unsigned long smallBuzzDuration = 1000;
const unsigned long largeBuzzDuration = 3000;
const unsigned long timeOutDuration = 10000;

bool isLockReleased = false;
unsigned long lockReleasedTime;

bool isRelicRemoved = false;
unsigned long relicRemovedTime;

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
    Serial.println("Lock has been closed.");
    SetLockReleased(false);
}

void onRelicButtonPressed()
{
    Serial.println("Relic has been replaced.");
    SetRelicRemoved(false);
}

void onLockButtonReleased()
{
    if (!isLockReleased)
    {
        Serial.println("Lock has been released.");
        SetLockReleased();
        smallBuzzer.buzz(smallBuzzerSpeed, smallBuzzDuration);
    }
}

void onRelicButtonReleased()
{
    if (!isRelicRemoved)
    {
        Serial.println("Relic has been removed.");
        SetRelicRemoved();
        largeBuzzer.buzz(largeBuzzerSpeed, largeBuzzDuration);
    }
}

void SetLockReleased(bool isReleased = true)
{
    isLockReleased = isReleased;
    lockReleasedTime = isReleased ? millis() : 0;
}

void SetRelicRemoved(bool isRemoved = true)
{
    isRelicRemoved = isRemoved;
    relicRemovedTime = isRemoved ? millis() : 0;
}