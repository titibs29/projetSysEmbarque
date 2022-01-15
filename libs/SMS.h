#include <stdio.h>
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

#pragma once

void SendSMS(char numero[20], char message[200]);

/*
Exemple de code :

int main()
{
	char numero[20] = "\"+32494801130\"";
	char message[200] = "Votre Message ici.";


	SendSMS(numero, message);
	return 0;
}

*/
