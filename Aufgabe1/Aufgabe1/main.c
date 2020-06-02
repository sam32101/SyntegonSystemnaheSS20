/*
 * Aufgabe1.c
 *
 * Created: 31.05.2020 10:03:12
 * Author :  Sam Harjung, Sören Krüger, Jens Langkammerer
 */ 


// Aufgabenbeschreibung: 
//Timerschaltung für 2 Töne (Kammerton A und Kammerton C): Per Taster (Interrupt) wird zwischen den Tönen hin und her geschaltet.

#include <avr/io.h>#
#include <avr/interrupt.h>
#include "main.h"

extern int KammertonA = 10;
extern int KammertonC = 100;

ISR (INT0_vect)
{
	setTimer(KammertonA);
}

ISR (INT1_vect)
{
	setTimer(KammertonC);
}


ISR(TIMER0_COMPA_vect){
	TOGGLE_BIT(PORTB, PORTB5);
}

int main(void)
{
	init();	// initialisieren
	while(1);
}

