/*
 * main.h
 *
 * Created: 01.06.2020 09:14:05
 *  Author: Sam Harjung, S�ren Kr�ger, Jens Langkammerer
 */

#include <avr/interrupt.h>
#include <stdio.h>

#define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)

// Z�hlervariable um Intervalle zu z�hlen
int stepcount = 0;

void init(){

	// B als Ausgang
	DDRB = 0xFF;
	PORTB = 0x00;

	// Timer initialisieren
	// OcRN = [ (16MHz / 256) * 0.1]-1 = 6249 = 0x1869
	OCR1A = 0x1869;

	SET_BIT(TCCR1B,WGM12);
	// Modus 4, CTC auf OCR1A

	SET_BIT(TIMSK1,OCIE1A);
	// L�se Interupt bei Vergleichs�bereinstimmung ( compare match ) aus

	SET_BIT(TCCR1B,CS12)
	// Prescaler auf 256 und timer starten

	sei();
	// Interrupts aktivieren

}

// Setze je nach position die korrekten Farben und erh�he den Schrittz�hler
void step(){

	switch(stepcount)
	{
		case 0:
			// Rot (10 Intervalle)
			PORTB = 0b010000;
			stepcount++;
			break;
		case 10:
			// Rot, Gelb (1 Interval)
			PORTB = 0b010100;
			stepcount++;
			break;
		case 11:
			// Gr�n (10 Intervalle)
			PORTB = 0b000001;
			stepcount++;
			break;
		case 21:
			// Gelb (1 Interval)
			PORTB = 0b000100;
			// Schrittz�hler zur�cksetzen
			stepcount=0;
			break;
		default:
			stepcount++;
	}

}
