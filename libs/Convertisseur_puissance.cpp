#include "Convertisseur_puissance.h"

void Convertisseur(float *p_tension, float *p_courant, float *p_puissance)
{
	int channel_4 = analogRead(100);
	float val_channel_4 = (channel_4 / 2047.0) * 2.048; // valeur Max/2.048V

	int channel_3 = analogRead(102);
	float val_channel_3 = (channel_3 / 2047.0) * 2.048; // valeur Max/2.048V

	*p_tension = val_channel_4;
	*p_courant = val_channel_3;
	*p_puissance = val_channel_4 * val_channel_3;
}
