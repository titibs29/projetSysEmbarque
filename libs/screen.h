#include <iostream>
#include <wiringSerial.h>

#pragma once

// utiliser uniquement pour envoyer une commande pas encore renseignee ci-dessous
void screenSendCommand(const char* cmd);

void screenInit();

// temperature avec max. 1 décimale
void screenSetTemp(float temp);

void screenSetTemp(int temp);

// puissance avec max. 1 décimale
void screenSetPwr(float pwr);

// fragment de SetPosition, ne pas utiliser
void screenSetLatitude(int lat);

// fragment de SetPosition, ne pas utiliser
void screenSetLongitude(int lon);

// entrer les coordonees suivie de max. 6 décimales
void screenSetPosition(float lat,float lon);

// les valeurs ont 2 décimales
void screenSetGyro(float x, float y);

// les valeurs ont 2 décimales
void screenSetAccel(float x, float y);

int screenStatus();

void screenClose();