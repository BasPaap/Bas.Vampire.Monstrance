#include "Buzzer.h"

Bas::Buzzer::Buzzer(int pinA, int pinB, LogLevel logLevel) : pinA{ pinA }, pinB{ pinB }, logLevel { logLevel }
{
}

void Bas::Buzzer::begin()
{
	if (this->logLevel == LogLevel::normal)
	{
		Serial.print("Initializing Buzzer on pins ");
		Serial.print(this->pinA);
		Serial.print(" and ");
		Serial.println(this->pinB);
	}

	pinMode(this->pinA, OUTPUT);
	pinMode(this->pinB, OUTPUT);
	digitalWrite(this->pinA, LOW);
	analogWrite(this->pinB, LOW);
}

void Bas::Buzzer::update()
{
	if (isBuzzing &&
		millis() - buzzStartTime >= buzzDuration)
	{
		if (this->logLevel == LogLevel::normal)
		{
			Serial.print("Stopped buzzing on pin ");
			Serial.print(this->pinA);
			Serial.print(" and ");
			Serial.println(this->pinB);
		}

		isBuzzing = false;
		digitalWrite(this->pinA, LOW);
		analogWrite(this->pinB, LOW);
	}
}

void Bas::Buzzer::buzz(int speed, unsigned long duration)
{
	if (speed > 255)
		speed = 255;

	if (speed < 0)
		speed = 0;

	if (this->logLevel == LogLevel::normal)
	{
		Serial.print("Started buzzing at a speed of ");
		Serial.print(speed);
		Serial.print(" and a duration of ");
		Serial.print(duration);
		Serial.print(" milliseconds on pin ");
		Serial.print(this->pinA);
		Serial.print(" and ");
		Serial.println(this->pinB);
	}

	buzzDuration = duration;
	buzzStartTime = millis();
	isBuzzing = true;
	digitalWrite(this->pinA, LOW);
	analogWrite(this->pinA, speed);
}
