#include "screen.h"

#define LENGTH 50
#define device "/dev/ttyS0"						// dossier de serial0, voir 'ls /dev -l'
#define baudrate 9600

int hmi = 0;

void screenSendCommand(const char* command)
{
	try {

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }	// vider le buffer

		serialPrintf(hmi, command);				// envoi de la commande
		serialPutchar(hmi, 0xFF);
		serialPutchar(hmi, 0xFF);
		serialPutchar(hmi, 0xFF);

	}
	catch (const char* msg) {
		std::cout << "erreur a l'envoi de la commande: " << command << std::endl;
		std::cout << "erreur: " << msg << std::endl;
	}
}

void screenInit()
{
	try {

		hmi = serialOpen(device, baudrate);

		screenSendCommand("");
		screenSendCommand("bkcmd=1");					// d�finit le type de retour de l'�cran (0=pas de retour; 1=uniquement cmd r�ussie; 2=uniquement cmd �chou�e; 3=tout)

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }

		screenSendCommand("page 0");					// retourne � la page 0 (reset �galement les valeurs)

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }

	}
	catch (const char* msg) {
		std::cout << "erreur � l'initialisation de la connexion � l'�cran: " << msg << std::endl;
	}
}

void screenSetTemp(float temp)
{
	try {

		int temperature = int(temp * 10);		// change la valeur en entier, puis l'integre dans le texte
		char text[LENGTH * sizeof(char)];
		std::sprintf(text, "temp_val.val=%d", temperature);

		screenSendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }

	}
	catch (const char* msg) {
		std::cout << "erreur � l'envoi de la temp�rature: " << msg << std::endl;
	}
}

void screenSetTemp(int temp)
{
	try {

		int temperature = temp * 10;
		char text[LENGTH * sizeof(char)];
		std::sprintf(text, "temp_val.val=%d", temperature);

		screenSendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }
	}
	catch (const char* msg) {
		std::cout << "erreur � l'envoi de la temp�rature: " << msg << std::endl;
	}
}

void screenSetPwr(float pwr)
{
	try {

		int power = int(pwr * 10);
		char text[LENGTH * sizeof(char)];
		std::sprintf(text, "pow_val.val=%d", power);

		screenSendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }
	}
	catch (const char* msg) {
		std::cout << "erreur � l'envoi de la puissance: " << msg << std::endl;
	}
}

void screenSetLatitude(int lat)
{
	try {

		char text[LENGTH * sizeof(char)];		// integre la valeur dans le texte
		std::sprintf(text, "lat_val.val=%d", lat);

		screenSendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }
	}
	catch (const char* msg) {
		std::cout << "erreur � l'envoi de la latitude: " << msg << std::endl;
	}
}

void screenSetLongitude(int lon)
{
	try {

		char text[LENGTH * sizeof(char)];
		std::sprintf(text, "lon_val.val=%d", lon);

		screenSendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }
	}
	catch (const char* msg) {
		std::cout << "erreur � l'envoi de la longitude: " << msg << std::endl;
	}
}

void screenSetPosition(float lat, float lon)
{
	try {
		int latitude = int(lat * 1000000);
		int longitude = int(lon * 1000000);

		screenSetLatitude(latitude);
		screenSetLongitude(longitude);

	}
	catch (const char* msg) {
		std::cout << "erreur dans le formatage de la position GPS: " << msg << std::endl;
	}
}

void screenSetGyro(float x, float y)
{
	try {

		int x_int = int(x * 100);		// change la valeur en entier, puis l'integre dans le texte
		int y_int = int(y * 100);

		char text_x[LENGTH * sizeof(char)];
		std::sprintf(text_x, "gyro_x_val.val=%d", x_int );

		screenSendCommand(text_x);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); } // vide le buffer

		char text_y[LENGTH * sizeof(char)];
		std::sprintf(text_y, "gyro_y_val.val=%d", y_int );

		screenSendCommand(text_y);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }

	}
	catch (const char* msg) {
		std::cout << "erreur a l'envoi des donnees du gyroscope : " << msg << std::endl;
	}
}

void screenSetAccel(float x, float y)
{
	try {

		int x_int = int(x * 100);		// change la valeur en entier, puis l'integre dans le texte
		int y_int = int(y * 100);

		char text_x[LENGTH * sizeof(char)];
		std::sprintf(text_x, "accel_x_val.val=%d", x_int );

		screenSendCommand(text_x);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); } // vide le buffer

		char text_y[LENGTH * sizeof(char)];
		std::sprintf(text_y, "accel_y_val.val=%d", y_int );

		screenSendCommand(text_y);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }

	}
	catch (const char* msg) {
		std::cout << "erreur a l'envoi des donnees de l'accelerometre : " << msg << std::endl;
	}
}

void screenSetTime(int hour, int min)
{
	try {

		char text[LENGTH * sizeof(char)];
		std::sprintf(text, 'time.txt="%d:%d"', hour, min);

		screenSendCommand(text);

		while (serialDataAvail(hmi)) { serialGetchar(hmi); }
	}
	catch (const char* msg) {
		std::cout << "erreur a l'envoi de l'heure: " << msg << std::endl;
	}
}

int screenStatus()
{
	return hmi;
}

void screenClose()
{
	try {
		serialClose(hmi);
	}
	catch (const char* msg) {
		std::cout << "erreur a la fermeture: " << msg << std::endl;
	}
}