/*
 * Aufgabe5.c
 *
 * Created: 30.05.2020 11:49:21
 * Author : Sam Harjung, Jens Langkammerer , Sören Krüger
 */ 

#include <avr/io.h>
#include <stdint.h>       // benötigt für uint8_t
#include <util/delay.h>
#include "main.h"

// Aufgabenbeschreibung: Analog-In 10Bit: Ein 10Bit Analogwert wird über ein Trim-Potentiometer abgegriffen und der aktuelle Wert via serieller Schnittstelle an den PC-übertragen.

// Variablen um ADCH / ADCL zwischenzuspeichern
volatile uint8_t highByte;
volatile uint8_t lowByte;

ISR(ADC_vect)
{
	// ADCL zuerst auslesen da beim auslesen von ADCH eine neue Konvertierung durchgeführt wird
	lowByte = ADCL;
	highByte = ADCH;
	
	// high und lowbyte nacheinander Übertragen ( In Transmit Buffer schreiben)
	
	UDR0 = highByte;			
	
	// zwischen high und low byte kurz warten, da es sonst zu Fehlern kommt bzw nur das high byte übertragen wird
	_delay_ms(50);	
	
	UDR0 = lowByte;

}

int main(void)
{
	// initialisieren
	init();
	while(1);
}
