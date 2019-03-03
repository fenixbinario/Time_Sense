/*
Name:		Tempo_Sense.ino
Created:	02/03/2019 15:57:04
Author:	@fenixbinario | www.fenixbinario.com

Address 0x00-0x12 for DS3231
ATTINY - CONNECTION
							
Attiny85			POWER		DS3231		WS2812
PB4					GND			GND			GND
PB8					VCC			5V			5V 
PB2	PCINT2						SCL
PB0 PCINT0						SDA
PB1 PCNINT1									DATA
*/
//EARTH HOURS
enum Hours : byte {Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Eleven, Twleve, Thirteen, Fourteen, Fifteen, Sixteen, Seventeen, Eighteen, Nineteen, Twenty, TwentyOne, TwentyTwo, TwentyThree}hours;

//LED INDICATOR
enum ErrorSystem : byte
{
	WORK,
	TIME_COMPILE, 
	TIME_SET, 
	TIME_GET,
	TIME_CHANGE,
}status;

//LIBRARY
//#include <TinyDebugKnockBang.h>

#include <DS3232RTC.h>
#include <EasyNeoPixels.h>


//PROTOTYPE
time_t compileTime(void);				//Function to return the compile date and time as a time_t value
bool timeChange(void);					//Change Hour
void LedErrors(void);					//RED (Error System) Blue(Busy System) Green(System is Work)
void setColor(int, int, int);			//LedError color blink
void offHot(void);						//All heat source turned OFF
void onHot(void);						//Heat source turned ON
void setHot(byte);						//Heat ON
void rotationBegin(void);				//Within the setup() function 
void rotationSolar(void);				//Turn on only the heat source associated with the rotation of the sun.


//GLOBAL
time_t t;
static time_t tLast;

// the setup function runs once when you press reset or power the board
void setup() {	
	rotationBegin();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	rotationSolar();
}



//FUNCTION DECLARATION
bool timeChange(void)
{
	t = now();
	if (t != tLast) {
		tLast = t;
		return true;
	}
	else return false;
}

void offHot(void) 
{
	for (byte i = 0; i <= 5; i++)
	{
		writeEasyNeoPixel(i, LOW);
	}
};

void setHot(byte _hour)
{
	//Turn On source hot
	switch (_hour)
	{
	case Zero:		writeEasyNeoPixel(1, 255, 0, 0);
		break;
	case One:		writeEasyNeoPixel(1, 0, 255, 0);
		break;
	case Two:		writeEasyNeoPixel(1, 0, 0, 255);
		break;
	case Three:		writeEasyNeoPixel(2, 255, 0, 0);
		break;
	case Four:		writeEasyNeoPixel(2, 0, 255, 0);
		break;
	case Five:		writeEasyNeoPixel(2, 0, 0, 255);
		break;
	case Six:		writeEasyNeoPixel(3, 255, 0, 0);
		break;
	case Seven:		writeEasyNeoPixel(3, 0, 255, 0);
		break;
	case Eight:		writeEasyNeoPixel(3, 0, 0, 255);
		break;
	case Nine:		writeEasyNeoPixel(4, 255, 0, 0);
		break;
	case Ten:		writeEasyNeoPixel(4, 0, 255, 0);
		break;
	case Eleven:	writeEasyNeoPixel(4, 0, 0, 255);
		break;
	case Twleve:	writeEasyNeoPixel(1, 255, 0, 0);
		break;
	case Thirteen:	writeEasyNeoPixel(1, 0, 255, 0);
		break;
	case Fourteen:	writeEasyNeoPixel(1, 0, 0, 255);
		break;
	case Fifteen:	writeEasyNeoPixel(2, 255, 0, 0);
		break;
	case Sixteen:	writeEasyNeoPixel(2, 0, 255, 0);
		break;
	case Seventeen:	writeEasyNeoPixel(2, 0, 0, 255);
		break;
	case Eighteen:	writeEasyNeoPixel(3, 255, 0, 0);
		break;
	case Nineteen:	writeEasyNeoPixel(3, 0, 255, 0);
		break;
	case Twenty:	writeEasyNeoPixel(3, 0, 0, 255);
		break;
	case TwentyOne:	writeEasyNeoPixel(4, 255, 0, 0);
		break;
	case TwentyTwo:	writeEasyNeoPixel(4, 0, 255, 0);
		break;
	case TwentyThree:	writeEasyNeoPixel(4, 0, 0, 255);
		break;
	default:
		break;
	}
};
void onHot(void) 
{	
	//Turn Off
	offHot();
	
	//Update Time
	byte h = hour(t);

	//TurnON
	setHot(h);

};

void rotationBegin(void)
{
	// COMMENT THIS LINE! set the RTC time and date to the compile time
	//	RTC.set(now());
	//	RTC.set(compileTime());   
	
	// SetUp-> setSyncProvider() causes the Time library to synchronize with the
	// external RTC by calling RTC.get() every five minutes by default.
	setSyncProvider(RTC.get);
	//ERROR CLOCK
	(timeStatus() != timeSet) ? status = TIME_SET : status = WORK;

	// SetUp-> Pixel Hot source
	setupEasyNeoPixels(PCINT3, 5); // (	4 MODULE ws2812 ) * (3 SourceHot ) = 12 Hours  + 1 Module for Led Indicator
}
void rotationSolar(void) 
{
	if (timeChange)
	{
		status = TIME_CHANGE;
		LedErrors();
		onHot();
	}
	else
	{
		status = WORK;
		LedErrors();
	}
};

time_t compileTime(void)
{
	const time_t FUDGE(10);    //fudge factor to allow for upload time, etc. (seconds, YMMV)
	const char *compDate = __DATE__, *compTime = __TIME__, *months = "JanFebMarAprMayJunJulAugSepOctNovDec";
	char compMon[3], *m;

	strncpy(compMon, compDate, 3);
	compMon[3] = '\0';
	m = strstr(months, compMon);

	tmElements_t tm;
	tm.Month = ((m - months) / 3 + 1);
	tm.Day = atoi(compDate + 4);
	tm.Year = atoi(compDate + 7) - 1970;
	tm.Hour = atoi(compTime);
	tm.Minute = atoi(compTime + 3);
	tm.Second = atoi(compTime + 6);

	time_t t = makeTime(tm);
	(t == -1) ? status = TIME_COMPILE : status = WORK;
	return t + FUDGE;        //add fudge factor to allow for compile time
};

void LedErrors()
{
	switch (status)
	{
	case WORK:			setColor(0, 255, 0); // Green Color
		break;
	case TIME_COMPILE:	setColor(255, 0, 0); // Red Color
		break;
	case TIME_SET:		setColor(255, 0, 0); // Red Color
		break;
	case TIME_GET:		setColor(255, 0, 0); // Red Color
		break;
	case TIME_CHANGE:	setColor(0, 0, 255);// Blue Color
		break;
	default:
		break;
	}
}

void setColor(int redValue, int greenValue, int blueValue) 
{
	for (byte i = 0; i <= status; i++)
	{
		writeEasyNeoPixel(0, redValue, greenValue, blueValue);
		delay(500);
		writeEasyNeoPixel(0, LOW);
	}
}