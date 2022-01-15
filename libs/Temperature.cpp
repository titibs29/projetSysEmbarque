#include "Temperature.h"

void Temperature()
{
	if (analogRead(201))
	{
		printf("ERREUR\n");
	}
	else
	{
		int temperature = analogRead(202);
		printf("%d.%d C\n", temperature / 10, temperature % 10);
	}
}