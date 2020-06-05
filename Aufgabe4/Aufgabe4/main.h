/*
 * main.h
 *
 * Created: 01.06.2020 08:50:21
 *  Author: Sam Harjung, Sören Krüger, Jens Langkammerer
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)

// Richtungsvariable bestimmt ob LED gerade heller oder dunkler geregelt wird
bool direction = true;

void init(){
	SET_BIT(DDRD,DDD6);						// PD6 als Ausgang
	 
	OCR0A = 128;							// setze PWM auf 50 % für den Anfang
	 
	SET_BIT(TCCR0A,COM0A1);					// setze nicht invertierenden Modus
	 
	SET_BIT(TCCR0A,WGM02); 	SET_BIT(TCCR0A,WGM00);	// setze "fast PWM" Modus
	 
	SET_BIT(TCCR0B,CS01);					// setze prescaler auf 8 und starte PWM
	 
	OCR1A = 0x270;							// Timer initialisieren
	 
	SET_BIT(TCCR1B,WGM12);					// Modus 4, CTC on OCR1A
	 
	SET_BIT(TIMSK1,OCIE1A);					// Interrupt bei Vergleichs Übereinstimmung (Compare match)
	 
	SET_BIT(TCCR1B,CS12); SET_BIT(TCCR1B,CS10);		// Prescaler auf 1024 setzen und Timer starten
	 
	sei();									// enable interrupts
	 
}

// Schritt Methode
// Erhöht bzw verringert OCR0A abhängig von der Richtung
// Wenn der minimale oder maximale Wert erreicht ist wird die richtung gedreht
void step(){
	
	if(OCR0A==0xFF){
		// maximaler Wert
		OCR0A--;
		direction = false;
	}
	else if(OCR0A==0x00){
		// minimaler Wert
		OCR0A++;
		direction = true;
	}
	else if(direction){
		OCR0A ++;
	}
	else{
		OCR0A--;
	}
	
}