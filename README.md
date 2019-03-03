# Time_Sense

_Este sentido te permite tener una percepción del tiempo solar sobre la tierra._

## REQUISITOS

### Software
* Tener instalado `ATTinyCore` by Spence Konde [Más INFO](https://github.com/SpenceKonde/ATTinyCore).

### Hardware
* Atiny85 | Attiny45.
* Sensor UV.

## CODIGO

_Retorna la fecha en el momento de la compilación._
``` c++
time_t compileTime(void);				//Function to return the compile date and time as a time_t value
```
_Retorna ```TRUE``` si ha cambiado la hora._ 
	* _Ejemplo: if(17 != 16) ... retorna `TRUE`._
	* _Ejemplo: if(17 != 17) ... retorna `FALSE`._
``` c++
bool timeChange(void);					//Change Hour
```
void LedErrors(void);					//RED (Error System) Blue(Busy System) Green(System is Work)
void setColor(int, int, int);			//LedError color blink
void offHot(void);						//All heat source turned OFF
void onHot(void);						//Heat source turned ON
void setHot(byte);						//Heat ON
void rotationBegin(void);				//Within the setup() function 
void rotationSolar(void);				//Turn on only the heat source associated with the rotation of the sun.
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
