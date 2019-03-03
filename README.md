# Time_Sense

_Este sentido te permite tener una percepción del tiempo solar sobre la tierra._

## REQUISITOS

### Software
* Tener instalado `ATTinyCore` by Spence Konde [Más INFO](https://github.com/SpenceKonde/ATTinyCore).

### Hardware
* Atiny85	* 1	Unidad.
* 3231RTC	* 1 Unidad.
* WS2812	* 5 Unidades.

|	Attiny85	|		POWER		|		DS3231		|		WS2812		|			
|		----	|		----		|		----		|		----		|
|	PB4			|		GND			|		GND			|		GND			|
|	PB8			|		VCC			|		5V			|		5V			|
|	PB2	PCINT2	|		-			|		SCL			|		-			|
|	PB0 PCINT0	|		-			|		SDA			|		-			|
|	PB1 PCNINT1	|		-			|		-			|		DATA		|

## CODIGO

### Retorna la fecha en el momento de la compilación.
``` c++
time_t compileTime(void);
```


### Retorna ```TRUE``` si ha cambiado la hora.
``` c++
bool timeChange(void);					
```
* _Ejemplo: if(17 != 16) ... retorna `TRUE` ._
* _Ejemplo: if(17 != 17) ... retorna `FALSE` ._


### Indicamediante Codigo de color y parpadeo si hay una error y cual es.
``` c++
void LedErrors(void);
```
|	 Tipo				|	 Color		|		 Parpadeo	|		Status		|
|	  ----				|	----		|		----		|		----		|
|	  Sistema			|	_Verde_		|			1		|		WORK		|
|	 Error Sistema		|	_Rojo_		|			2		|	TIME_COMPILE	|
|	 Error Sistema		|	_Rojo_		|			3		|	TIME_SET		|
|	 Error Sistema		|	_Rojo_		|			4		|	TIME_GET		|
|	  Sistema			|	_Azul_		|			5		|	TIME_CHANGE		|


###	Establece el color para el LED indicador
``` c++
void setColor(int, int, int);
```

### Establece en `Off` todas las fuentes de calor
``` c++
void offHot(void);
```

### Establece en `On` la fuente de calor segun la rotacion de la tierra y la hora terrestre.
``` c++
void onHot(void);
```

### Estable `255` o `0` en WS2812
``` c++
void setHot(byte);						//Heat ON
```

### Setup()
``` c++
void rotationBegin(void);				//Within the setup() function 
```

### Loop()
``` c++
void rotationSolar(void);				//Turn on only the heat source associated with the rotation of the sun.
 ```


### *Pasos*
* Para desplegar y construir por ti mismo este órgano y sentido sigue **Desplequegar**.
* Sigue cada unos de los pasos.
* Que hardware necesitas?

_Descripción del codigo de arduino_

``` c++

#include <TinyWireM>
#include <Time_Sense>

TimeSense newSense;

```
