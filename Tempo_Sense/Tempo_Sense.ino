/*
Name:		Tempo_Sense.ino
Created:	02/03/2019 15:57:04
Author:	@fenixbinario | www.fenixbinario.com

ATTINY - CONNECTION

Attiny85			POWER		DS3231		WS2812
PB4					GND			GND			GND
PB8					VCC			5V			5V 
PB2	PCINT2						SCL
PB0 PCINT0						SDA
PB1 PCNINT1									DATA
*/

//LIBRARY
//#include <TinyDebugKnockBang.h>

#include <USI_TWI_Master.h>
#include <TinyWireM.h>
#include <TinyRTClib.h>
#include <DS3232RTC.h>
#include <Adafruit_NeoPixel.h>
#include <EasyNeoPixels.h>

//PROTOTYPE


// the setup function runs once when you press reset or power the board
void setup() {

	// setSyncProvider() causes the Time library to synchronize with the
	// external RTC by calling RTC.get() every five minutes by default.
	setSyncProvider(RTC.get);

}

// the loop function runs over and over again until power down or reset
void loop() {

	static time_t tLast;

	time_t t = now();
	if (t != tLast) {
		tLast = t;
	}

	float hora = hour(t);
	float minuto =  minute(t);
	float segundo = second(t);
}
