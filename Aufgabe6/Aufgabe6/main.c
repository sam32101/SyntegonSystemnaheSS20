/*
 * Aufgabe5.c
 *
 * Created: 30.05.2020 11:49:21
 * Author : Sam Harjung, Jens Langkammerer, S�ren Kr�ger
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

// Aufgabenbeschreibung: Zwei analoge Eing�nge (Potentiometer) zu digital wandeln 
// und �ber die serielle Schnittstelle in 8 Bit Aufl�sung abwechselnd an den PC �bertragen (Kanalmultiplexer)


int main(void)
{

	initSerial();				// Initialisieren

	while (1)
	{
		
		ADCsingleREAD(0);		// Eingang 0 von Analog zu Digital wandeln
		
		UDR0 = ADCH;			// Ergebnis �bertragen
		
		_delay_ms(100);			// kurz warten um Fehler zu vermeiden
		
		ADCsingleREAD(1);		// Eingang 1 zu Digital wandeln
		
		UDR0 = ADCH;			// Ergebnis �bertragen
		
		_delay_ms(100);			// kurz warten um Fehler zu vermeiden
		
	}
}
