#include "Buzzer.h"

Bas::Buzzer::Buzzer(int pin, LogLevel logLevel) : pin{ pin }, logLevel{ logLevel }
{
}

void Bas::Buzzer::begin()
{
	if (this->logLevel == LogLevel::normal)
	{
		Serial.print("Initializing Buzzer on pin ");
		Serial.println(this->pin);
	}

	pinMode(this->pin, OUTPUT);
	digitalWrite(this->pin, LOW);
}

void Bas::Buzzer::update()
{
	if (isBuzzing &&
		millis() - buzzStartTime >= buzzDuration)
	{
		if (this->logLevel == LogLevel::normal)
		{
			Serial.print("Stopped buzzing on pin ");
			Serial.println(this->pin);
		}

		isBuzzing = false;
		digitalWrite(this->pin, LOW);
	}
}

void Bas::Buzzer::buzz(unsigned long duration)
{
	if (this->logLevel == LogLevel::normal)
	{
		Serial.print("Started buzzing for ");
		Serial.print(duration);
		Serial.print(" milliseconds on pin ");
		Serial.println(this->pin);
	}

	buzzStartTime = millis();
	isBuzzing = true;
	digitalWrite(this->pin, HIGH);
}
