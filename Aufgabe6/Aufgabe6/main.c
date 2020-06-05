/*
 * Aufgabe5.c
 *
 * Created: 30.05.2020 11:49:21
 * Author : Sam Harjung, Jens Langkammerer, Sören Krüger
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

// Aufgabenbeschreibung: Zwei analoge Eingänge (Potentiometer) zu digital wandeln 
// und über die serielle Schnittstelle in 8 Bit Auflösung abwechselnd an den PC übertragen (Kanalmultiplexer)

// input flag , verwendet um ADC Multiplexer korrekten eingang zu übergeben
volatile bool input = true;

// timer compare match interupt (alle .5 Sekunden)
ISR (TIMER1_COMPA_vect)
{
	// lese je nach input flag Analog Eingang 1 oder 0 ein
	// ändere flag wert
	if(input){
		ADCsingleREAD(0);
	}
	else{
		ADCsingleREAD(1);
	}
	
	// input flag flippen 
	input = !input;
	
	// Gelesenen wert in Transmitbuffer schreiben
	UDR0 = ADCH;
	
}


int main(void)
{
	// initialisieren	
	initSerial();
	initTimer();

	while (1);
}
