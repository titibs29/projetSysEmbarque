#include "screen.h"

#define LENGTH 50
#define device "/dev/ttyS0"						// dossier de serial0, voir 'ls /dev -l'
#define baudrate 9600

int hmi = 0;

void sendCommand(const char* command)
{
	try {

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }	// vider le buffer

		serialPrintf(hmi, command);				// envoi de la commande
		serialPutchar(hmi, 0xFF);
		serialPutchar(hmi, 0xFF);
		serialPutchar(hmi, 0xFF);

	}
	catch (const char* msg) {
		std::cout << "erreur  à l'envoi de la commande: " << command << std::endl;
		std::cout << "erreur: " << msg << std::endl;
	}
}

void Init()
{
	try {

		hmi = serialOpen(device, baudrate);

		sendCommand("");
		sendCommand("bkcmd=1");					// définit le type de retour de l'écran (0=pas de retour; 1=uniquement cmd réussie; 2=uniquement cmd échouée; 3=tout)

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }

		sendCommand("page 0");					// retourne à la page 0 (reset également les valeurs)

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }

	}
	catch (const char* msg) {
		std::cout << "erreur à l'initialisation de la connexion à l'écran: " << msg << std::endl;
	}
}

void setTemp(double temp)
{
	try {

		int temperature = int(temp * 10);		// change la valeur en entier, puis l'intègre dans le texte
		char text[LENGTH * sizeof(char)];
		std::sprintf(text, "temp_val.val=%d", temperature);

		sendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }

	}
	catch (const char* msg) {
		std::cout << "erreur à l'envoi de la température: " << msg << std::endl;
	}
}

void setTemp(int temp)
{
	try {

		int temperature = temp * 10;
		char text[LENGTH * sizeof(char)];
		std::sprintf(text, "temp_val.val=%d", temperature);

		sendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }
	}
	catch (const char* msg) {
		std::cout << "erreur à l'envoi de la température: " << msg << std::endl;
	}
}

void setPwr(double pwr)
{
	try {

		int power = int(pwr * 10);
		char text[LENGTH * sizeof(char)];
		std::sprintf(text, "pow_val.val=%d", power);

		sendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }
	}
	catch (const char* msg) {
		std::cout << "erreur à l'envoi de la puissance: " << msg << std::endl;
	}
}

void setLatitude(int lat)
{
	try {

		char text[LENGTH * sizeof(char)];		// intègre la valeur dans le texte
		std::sprintf(text, "lat_val.val=%d", lat);

		sendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }
	}
	catch (const char* msg) {
		std::cout << "erreur à l'envoi de la latitude: " << msg << std::endl;
	}
}

void setLongitude(int lon)
{
	try {

		char text[LENGTH * sizeof(char)];
		std::sprintf(text, "lon_val.val=%d", lon);

		sendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }
	}
	catch (const char* msg) {
		std::cout << "erreur à l'envoi de la longitude: " << msg << std::endl;
	}
}

void setPosition(double lat, double lon)
{
	try {
		int latitude = int(lat * 1000000);
		int longitude = int(lon * 1000000);

		setLatitude(latitude);
		setLongitude(longitude);

	}
	catch (const char* msg) {
		std::cout << "erreur dans le formatage de la position GPS: " << msg << std::endl;
	}
}

void setSignal(int signal)
{
	try {

		char text[LENGTH * sizeof(char)];
		std::sprintf(text, "sig_val.val=%d", signal);

		sendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }
	}
	catch (const char* msg) {
		std::cout << "erreur à l'envoi du signal: " << msg << std::endl;
	}
}

int status()
{
	return hmi;
}

void close()
{
	try {
		serialClose(hmi);
	}
	catch (const char* msg) {
		std::cout << "erreur à la fermeture: " << msg << std::endl;
	}
}