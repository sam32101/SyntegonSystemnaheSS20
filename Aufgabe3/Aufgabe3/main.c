/*
 * Aufgabe3.c
 *
 * Created: 31.05.2020 10:03:44
 * Author : Sam Harjung, Sören Krüger, Jens Langkammerer
 */ 


// Aufgabenbeschreibung: 6-Bit oder 10-Bit Lauflicht: LEDs werden so geschaltet, dass das Licht „wandert“. Jeweils am Ende wechselt das Licht die Richtung.

#include <avr/io.h>
#include <avr/interrupt.h>
#include "main.h"

 ISR(TIMER1_COMPA_vect)
 {
	setLights();
 }

int main(void)
{
	// initialisieren
	init();	
	while(1){}
}

