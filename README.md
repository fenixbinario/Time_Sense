# Time_Sense

_Este sentido te permite tener una percepción del tiempo solar sobre la tierra._

## REQUISITOS

### Software
* Tener instalado `ATTinyCore` by Spence Konde [Más INFO](https://github.com/SpenceKonde/ATTinyCore).

### Hardware
* Atiny85 | Attiny45.
* Sensor UV.

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
|	 Color		|		 Parpadeo	|		Status		|
|	----		|		----		|		----		|
|	_Verde_		|			1		|		WORK		|
|	_Rojo_		|			2		|	TIME_COMPILE	|
|	_Rojo_		|			3		|	TIME_SET		|
|	_Rojo_		|			4		|	TIME_GET		|
|	_Azul_		|			5		|	TIME_CHANGE		|



``` c++
void setColor(int, int, int);			//LedError color blink
```

``` c++
void offHot(void);						//All heat source turned OFF
```

``` c++
void onHot(void);						//Heat source turned ON
```

``` c++
void setHot(byte);						//Heat ON
```

``` c++
void rotationBegin(void);				//Within the setup() function 
```

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
