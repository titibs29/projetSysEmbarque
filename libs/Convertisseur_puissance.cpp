#include "Convertisseur_puissance.h"




using namespace std;

#define ADDR_I2C 0x68							//Adresse en hexa de la communication I2C
#define pinBase 100                     
#define Taux_echantillonnage 0
#define Gain 0





void Convertisseur()
{

	int channel_4 = analogRead(100);
	float val_channel_4 = (channel_4 / 2047.0) * 2.048;				//valeur Max/2.048V

	int channel_3 = analogRead(102);
	float val_channel_3 = (channel_3 / 2047.0) * 2.048;				//valeur Max/2.048V

	printf("Tension = : %.5f V \n", val_channel_4);
	printf("Courant = %.5f A \n", val_channel_3);
	printf("Puissance = %.1f W \n", val_channel_4 * val_channel_3);

}
