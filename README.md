# Time_Sense

_Este sentido te permite tener una percepción de la posición de la luz sol sobre la tierra, según esta vaya girando._



## REQUISITOS

### `Software`
* Instalar	Tarjeta:	------------------	by **Spence Konde**		[Más INFO](https://github.com/SpenceKonde/ATTinyCore).
* Instalar	Librería:	------------------	by **Adafruit**			[Más INFO](https://github.com/adafruit/Adafruit_NeoPixel).
* Instalar	Librería:	`<EasyNeoPixels.h>`	by **Evelyn Masso**		[Más INFO](https://github.com/outofambit/easy-neopixels).
* Instalar	Librería:	`<DS3232RTC.h>`		by **JChristensen**		[Más INFO](https://github.com/JChristensen/DS3232RTC).

### `Hardware`
* Atiny85	* 1	Unidad.
* 3231RTC	* 1 Unidad.
* WS2812	* 5 Unidades.
* Led RGB	* 1 Unidad.
* 330 ohm	* 3 Unidades.
* 33 uF		* 1 Unidad.
* Power 5v	* 1 Unidad.

### `E/S`
|	Attiny85	|		POWER		|		DS3231		|		WS2812		|			
|		----	|		----		|		----		|		----		|
|	PB4			|		GND			|		GND			|		GND			|
|	PB8			|		VCC			|		5V			|		5V			|
|	PB2	PCINT2	|		-			|		SCL			|		-			|
|	PB0 PCINT0	|		-			|		SDA			|		-			|
|	PB1 PCNINT1	|		-			|		-			|		DATA		|




## CÓDIGO
_Comentarios sobre las funciones y sus conexiones._

### Variables Globales
*	`time_t t;`				_Tiempo en milisegudos de la hora **actual**._
*	`static time_t tLast;`	_Tiempo en milisegudos de la hora **anterior**._

``` c++
time_t t;
static time_t tLast;
...
..
.
bool timeChange(void)
{
	t = now();
	if (t != tLast) {
		tLast = t;
		return true;...
.
```


### `compileTime()` Retorna la fecha en el momento de la compilación.
``` c++
time_t compileTime(void);
...
..
.
//La fecha en el momento de la compilación es pasada por parámetro
//al reloj DS3231 para ajustar la nueva hora.
RTC.set(compileTime());   
.
```



### `timeChange()` Retorna `TRUE` si ha cambiado la hora.
``` c++
bool timeChange(void);
...
..
.
void rotationSolar(void) 
{
	if (timeChange)
	{
		status = TIME_CHANGE;
		LedErrors();
		onHot(); ......
.
```
* _Ejemplo: if(17 != 16) ... retorna `TRUE` ._
* _Ejemplo: if(17 != 17) ... retorna `FALSE` ._



### `LedErrors()` Código de `Tipo`, `Color` y `Parpadeo` para indicar el `Estado` del *Sistema*.
``` c++
void LedErrors(void);
...
..
.
void LedErrors...
	switch (status)
		{
		case WORK:			setColor(0, 255, 0); // Green Color
			break;
		case TIME_COMPILE: ....
.
..
...
```
|	 Tipo				|	 Color		|		 Parpadeo	|		Estado		|
|	  ----				|	----		|		----		|		----		|
|	  Sistema			|	_Verde_		|			1		|		WORK		|
|	 Error Sistema		|	_Rojo_		|			2		|	TIME_COMPILE	|
|	 Error Sistema		|	_Rojo_		|			3		|	TIME_SET		|
|	 Error Sistema		|	_Rojo_		|			4		|	TIME_GET		|
|	  Sistema			|	_Azul_		|			5		|	TIME_CHANGE		|



###	`setColor()` Establece el color para el `LED indicador`.
``` c++
void setColor(int, int, int);
...
..
.
void setColor...
	    ..
		writeEasyNeoPixel(0, redValue, greenValue, blueValue);
		delay(500);
		writeEasyNeoPixel(0, LOW);
```



### `offHot()` Establece en `Off` todas las fuentes de calor
``` c++
void offHot(void);
...
..
.
void offHot...
{
	for (byte i = 0; i <= 5; i++)
	{
		writeEasyNeoPixel(i, LOW);...
.
..
...
```

### `onHot()` Establece en `On` la fuente de calor segun la rotacion de la tierra y la hora terrestre.
``` c++
void onHot(void);
```

### `setHot()` Estable `255` o `0` en WS2812
``` c++
void setHot(byte);						//Heat ON
```

### `rotationBegin()`  Setup()
``` c++
void rotationBegin(void);				//Within the setup()
...
..
.
void setup() {	
	rotationBegin();
}
```

### `rotationSolar()` Loop()
``` c++
void rotationSolar(void);
...
..
.
void loop() 
{
	rotationSolar();
}
 ```



## DESPLIEGUE
*PASOS*
* Asegurese de tener todo el hardware, conexiones, alimentación, tarjeta y librerías. 
* Monte en una tarjeta de desarrollo las conexiones o ensamble una PCB.
* Ten cuidado con la alimentación.
* Añade un condensador electrolitico entre el PIN RESET y GND del programador.
* Asegurate de tener configurado el DS3231 ¿Tienes el reloj con la hora ajustada?

_Descomenta estas líneas para ajustarlo con la hora de tu pc._
``` c++
.
..
..
void rotationBegin(void)
{
	// DESCOMMENT THIS LINE! 
	RTC.set(now()); 

	// OR DESCOMMENT THIS LINE!  
	//	RTC.set(compileTime());  
...
..
.
```




## DATASHEET

### ATtiny 25/45/85
![x5 pin mapping](http://drazzy.com/e/img/PinoutT85a.jpg "Arduino Pin Mapping for ATtiny 85/45/25")