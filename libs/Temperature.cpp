#include "Temperature.h"

void Temperature(float *p_temp)
{

	if (analogRead(201))
	{
		throw "erreur";
	}
	else
	{
		int temperature = analogRead(202);
		*p_temp = temperature / 10.0f;
	}
}