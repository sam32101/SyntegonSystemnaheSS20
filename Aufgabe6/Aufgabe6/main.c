/*
 * Aufgabe5.c
 *
 * Created: 30.05.2020 11:49:21
 * Author : Sam Harjung, Jens Langkammerer, S�ren Kr�ger
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

//Aufgabenbeschreibung: Zwei analoge Eing�nge (Potentiometer) zu digital wandeln 
// und �ber die serielle Schnittstelle in 8 Bit Aufl�sung an den PC �bertragen (Kanalmultiplexer)


int main(void)
{

	// initialisieren	
	initSerial();

	while (1)
	{
		// Eingang 0 von Analog zu Digital wandeln
		ADCsingleREAD(0);			
		// Ergebnis �bertragen
		UDR0 = ADCH;
		
		_delay_ms(100);
		// kurz warten um Fehler zu vermeiden
		
		// Eingang 1 zu Digital wandeln
		ADCsingleREAD(1);
		// Ergebnis �bertragen
		UDR0 = ADCH;
		
		// kurz warten um Fehler zu vermeiden
		_delay_ms(100);
		
	}
}
