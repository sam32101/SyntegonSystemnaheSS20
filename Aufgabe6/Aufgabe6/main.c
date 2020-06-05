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

// input flag , verwendet um ADC Multiplexer korrekten eingang zu �bergeben
volatile bool input = true;

// timer compare match interupt (alle .5 Sekunden)
ISR (TIMER1_COMPA_vect)
{
	// lese je nach input flag Analog Eingang 1 oder 0 ein
	// �ndere flag wert
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
