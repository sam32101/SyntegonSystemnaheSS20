/*
 * Aufgabe5.c
 *
 * Created: 30.05.2020 11:49:21
 * Author : Sam Harjung, Jens Langkammerer, Sören Krüger
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

//Aufgabenbeschreibung: Zwei analoge Eingänge (Potentiometer) zu digital wandeln 
// und über die serielle Schnittstelle in 8 Bit Auflösung an den PC übertragen (Kanalmultiplexer)


int main(void)
{

	// initialisieren	
	initSerial();

	while (1)
	{
		// Eingang 0 von Analog zu Digital wandeln
		ADCsingleREAD(0);			
		// Ergebnis übertragen
		UDR0 = ADCH;
		
		_delay_ms(100);
		// kurz warten um Fehler zu vermeiden
		
		// Eingang 1 zu Digital wandeln
		ADCsingleREAD(1);
		// Ergebnis Übertragen
		UDR0 = ADCH;
		
		// kurz warten um Fehler zu vermeiden
		_delay_ms(100);
		
	}
}
