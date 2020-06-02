/*
 * Aufgabe4.c
 *
 * Created: 31.05.2020 10:04:04
 * Author : Sam Harjung, Sören Krüger, Jens Langkammerer
 */ 

#include <avr/io.h>
#include "main.h"


// Aufgabenbeschreibung: PWM-Schaltung: LED wird zyklisch heller und dunkler

ISR (TIMER1_COMPA_vect)
{
	step();
}

int main(void)
{
	// initialisieren
	init();
	while(1);

}

