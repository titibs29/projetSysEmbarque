#include <wiringPi.h>
#include <iostream>
#include <time.h>
//#include <math.h>
#include <cmath>
#include <ctime>
using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#define PI          3.141592653589793238462643383279502884 


#define	CLK	27
#define DIR 26
#define BUTTON 16

//ordre de cablage côté CLK-DIR : CLK | DIR | + | -
//ordre de cablage côté stepper : - | + | bob1 | bob2

void CW_rotation()
{
	digitalWrite(DIR, HIGH);
}

void CCW_rotation()
{
	digitalWrite(DIR, LOW);
}

void stepper_1step()
{
	digitalWrite(CLK, HIGH);	// On
	delayMicroseconds(500);		// microseconds
	digitalWrite(CLK, LOW);		// Off
	delayMicroseconds(500);		// microseconds
}


//pour calculer la durée du jour selon date et position, puis calculer heure de levé du soleil et temps entre les steps
void step_day_light(time_t t, tm* tPtr, float lat, int &rise_time, int &time_between_steps)
{
	t = time(NULL);
	tPtr = localtime(&t);
	int ctr = 0, jour = 0;
	float full_step = 1.8;
	float half_step = full_step/2;
	float eigth_step = full_step / 8;
	float sixteenth_step = full_step / 16;
	int tab_months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	//on va chercher le nombre de jours écoulés depuis le début de l'année (besoin pour calcul durée du jour) :
	for(int j = 0; j<(tPtr->tm_mon);j++) jour += tab_months[j+1];
	jour += tPtr->tm_mday;
	cout << jour << endl;

	//Calcul de la durée du jour en heures
	double del = 23.44 * sin(((2*PI) / 365) * (284 + jour));//
	del = del * PI / 180;
	double day_length_h = acos(-tan(lat*PI/180)*tan(del))*180/PI;//
	day_length_h = day_length_h *2/(15);
	cout << "la durée du jour : " << day_length_h << endl;
	double day_length_m = day_length_h * 60;
	double day_length_s = day_length_m * 60;
	cout << "durée du jour en heures " << day_length_h << endl;
	cout << "durée du jour en secondes " << day_length_s << endl;
	
	//calcul de l'heure de levée du soleil
	float step_nbr = 180 / half_step;	//simplement connaitre cb de steps il faudra faire pour faire les 180° et suivre le soleil
	cout << "nbr de steps " << step_nbr << endl;

	rise_time = (24 * 3600 - round(day_length_s)) / 2; //en secondes
	cout << "rise time " << rise_time << endl;
	time_between_steps = day_length_s / step_nbr;
	cout << "tps entre steps " << time_between_steps << endl;
	//on peut approximer la durée entre les steps à la seconde, répercussions sur la durée du jour finale négligeables
}


//la fonction pour déplacer le stepper et donc le panneau solaire selon date, heure et position
void do_steps(time_t t, tm* tPtr, float lat, int &rise_time, int& temp_rise_time, int& time_between_steps)
{
	//bool hemi : 1 (NORD), hemi : 0 (SUD)
	bool hemi;
	if (lat < 0) hemi = 0;
	else hemi = 1;
	//on va chercher l'heure actuelle sur le raspi à chaque appel de cette fonction
	t = time(NULL);
	tPtr = localtime(&t);
	//heure actuelle en secondes
	int nbr_secs = tPtr->tm_sec + (tPtr->tm_min) * 60 + (tPtr->tm_hour) * 3600;
	
	//IF NEW DAY !
	//ici, on met <= 10 secondes (on considère comme nouvelle journée 00h00m10s)
	//si on a pas éteint et rallumé le pi et le projet pdt plus d'un jour, on revient à position de départ à minuit
	if (nbr_secs <= 10)
	{
		temp_rise_time == rise_time;	//si on passe au jour suivant, on reset la valeur de rise_time
		//on rappelle la fonction qui calcule le rise time et le time between steps qd on change de jour selon la latitude :
		step_day_light(t, tPtr, lat, rise_time, time_between_steps);

		//on tourne le stepper jusqu'à atteindre le bouton d'arrêt :
		while (digitalRead(BUTTON) != 1)
		{
			if(lat>=0)	CCW_rotation();		//tourner dans sens horlogique pour retour à l'est NORD
			else if(lat<0)	CW_rotation();		//tourner dans sens horlogique pour retour à l'est SUD
			stepper_1step();
		}
	}
	//CATCHUP STEPS
	//rattrapage de steps si on allume le projet en milieu de journée
	//il faut check si l'heure actuelle est plus grande que l'heure de levé du soleil calculée.
	//si c'est le cas, on compte le nombre de steps à faire pour aligner le stepper au soleil.
	if (nbr_secs > temp_rise_time)
	{
		int temp = nbr_secs - temp_rise_time;
		int catchup_steps = temp / time_between_steps;
		for (int i = 0; i < catchup_steps; i++)
		{
			if (lat >= 0)	CW_rotation(); 
			else if (lat < 0)	CCW_rotation();		
			stepper_1step();
		}
	}

	//STEPS NORMAUX
	//faire le step à l'heure prévue pour le step :
	if (nbr_secs >= temp_rise_time +time_between_steps)
	{
		//à l'heure de levé, on reset position du stepper
		if (temp_rise_time == rise_time)
		{
			//on tourne le stepper jusqu'à atteindre le bouton d'arrêt :
			while (digitalRead(BUTTON) != 1)
			{
				if (lat >= 0)	CCW_rotation();		//tourner dans sens horlogique pour retour à l'est
				else if (lat < 0)	CW_rotation();		//tourner dans sens horlogique pour retour à l'est
				stepper_1step();
			}
		}
		if (lat >= 0)	CCW_rotation();		//tourner dans sens horlogique pour retour à l'est
		else if (lat < 0)	CW_rotation();		//tourner dans sens horlogique pour retour à l'est
		stepper_1step();
		temp_rise_time = nbr_secs;
	}
}


int main(void)
{
	int ctr = 0;
	wiringPiSetupGpio();

	pinMode(CLK, OUTPUT);
	pinMode(DIR, OUTPUT);
	pinMode(BUTTON, INPUT);

	time_t t = time(NULL);
	tm* tPtr = localtime(&t);

	int rise_time = 1, time_between_steps = 1;
	float lat_heh = 1.352083; //MONS : 50.454241;

	step_day_light(t, tPtr, lat_heh, rise_time, time_between_steps);

	while (1)
	{
		int temp_rise_time = rise_time;		//garder en permanence en mémoire le rise time calculé au power on.
		do_steps(t, tPtr, lat_heh, rise_time, temp_rise_time, time_between_steps);
	}

	
	return 0;
}