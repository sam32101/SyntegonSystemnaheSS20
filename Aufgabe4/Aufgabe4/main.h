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
	 DDRD |= (1 << DDD6);
	 //PD6 als Ausgang
	 
	 OCR0A = 128;
	 // setze PWM auf 50 % für den Anfang
	 
	 TCCR0A |= (1 << COM0A1);
	 // setze nicht invertierenden Modus
	 
	 TCCR0A |= (1 << WGM02) | (1 << WGM00);
	 // setze "fast PWM" Modus
	 
	 TCCR0B |= (1 << CS01);
	 // setze prescaler auf 8 und starte PWM
	 
	 // init timer
	 OCR1A = 0x270;
	 // Mode 4, CTC on OCR1A
	 TCCR1B |= (1 << WGM12);
	 //Set interrupt on compare match
	 TIMSK1 |= (1 << OCIE1A);
	 // set prescaler to 1024 and start the timer
	 TCCR1B |= (1 << CS12) | (1 << CS10);
	 
	 sei();
	 // enable interrupts
	 
	 
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