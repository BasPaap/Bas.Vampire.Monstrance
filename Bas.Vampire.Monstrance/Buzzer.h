/*
  Bas.Buzzer.h - Library to control a buzzer motor for signaling or special effects.
  Created by Bas Paap, April 2024.
  Released into the public domain.
*/

namespace Bas
{
	// Encapsulate a buzzer motor. If the buzz() method is called the buzzer will be activated for the specified amount of time.
	class Buzzer
	{
	public:
		enum class LogLevel { none = 0, normal };

	private:
		int pinA;
		int pinB;
		unsigned long buzzDuration;
		unsigned long buzzStartTime;
		bool isBuzzing;
		LogLevel logLevel;

	public:
		/// <summary>
		/// Constructs the Buzzer object
		/// <param name="pinA">The first pin the buzzer is connected to.</param>
		/// <param name="pinB">The second pin the buzzer is connected to.</param>
		/// <param name="logLevel">The verbosity of the logging the class outputs to Serial. Default is none.</param>
		/// </summary>
		Buzzer(int pinA, int pinB, LogLevel logLevel = LogLevel::none);

		/// <summary>
		/// Initialize the Buzzer object.
		/// </summary>
		void begin();

		/// <summary>
		/// Updates the Buzzer state. This method should be called once per loop.
		/// </summary>
		void update();

		/// <summary>
		/// Activate the buzzer to start buzzing.
		/// <param name="speed">The speed at which the buzzer will buzz, between 0 and 255.</param>
		/// <param name="duration">The amount of time in milliseconds to buzz.</param>
		/// </summary>
		void buzz(int speed, unsigned long duration);

	};
}

