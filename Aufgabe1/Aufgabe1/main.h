/*
 * main.h
 *
 * Created: 01.06.2020 09:48:30
 *  Author:  Sam Harjung, Sören Krüger, Jens Langkammerer
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)


void init() {
	 
	DDRB=0xFF;					// Register B als Ausgang
	PORTB=0x00;					// Register B auf Low
	
	CLEAR_BIT(DDRD,DDD2);		// PD2 (INT0) zu Eingang machen

	SET_BIT(PORTD,PORTD2);		// Pullup für PD2
	
	CLEAR_BIT(DDRD,DDD3);		// PD3 (INT1) zu Eingang machen

	SET_BIT(PORTD,PORTD3);		// Pullup für PD3

	SET_BIT(EICRA,ISC00);		// Interrupt löst bei Wertänderung auf INT0 aus
	SET_BIT(EICRA,ISC10);		// Interrupt löst bei Wertänderung auf INT1 aus
	SET_BIT(EIMSK,INT0);		// INT0 Interrupt aktivieren
	SET_BIT(EIMSK,INT1);		// INT1 Interrupt aktivieren
	
	SET_BIT(TCCR0A,WGM01);		// Timer Modus auf CDC (Clear Timer on Compare) setzen
	
	SET_BIT(TIMSK0,OCIE0A);		// ISR COMPA vect setzen (Interrupt wenn Timer auf Wert gezählt hat)

	SET_BIT(TCCR0B,CS02);		// Prescaler auf 256 setzen und timer starten
	
	sei();						// Interrupts einschalten
	
}
 
 // ändert den 0CR0A Wert zu dem übergebenen Parameter
 // ändert somit frequenz des timers
void setTimer(int value){
	OCR0A = value;
}