/*
 * main.h
 *
 * Created: 01.06.2020 09:48:30
 *  Author:  Sam Harjung, S�ren Kr�ger, Jens Langkammerer
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)


 void init() {
	 
	DDRB=0xFF;				// Register B als Ausgang
	PORTB=0x00;				// Register B auf Low
	
	DDRD &= ~(1 << DDD2);     // PD2 (INT0) zu Eingang machen

	PORTD |= (1 << PORTD2);   // Pullup f�r PD2
	
	DDRD &= ~(1 << DDD3);     // PD3 (INT1) zu Eingang machen

	PORTD |= (1 << PORTD3);   // Pullup f�r PD3

	EICRA |= (1 << ISC00);    // Interrupt l�st bei Wert�nderung auf INT0 aus
	EICRA |= (1 << ISC10);    // Interrupt l�st bei Wert�nderung auf INT1 aus
	EIMSK |= (1 << INT0);     // INT0 Interrupt aktivieren
	EIMSK |= (1 << INT1);     // INT1 Interrupt aktivieren
	
	// Timer Modus auf CDC (Clear Timer on Compare) setzen
	TCCR0A |= (1 << WGM01);
	
	TIMSK0 |= (1 << OCIE0A);    //ISR COMPA vect setzen (Interrupt wenn Timer auf Wert gez�hlt hat)

	TCCR0B |= (1 << CS02);		//prescaler auf 256 setzen und timer starten
	
	sei();                    // interrupts einschalten
	
 }
 
 // �ndert den 0CR0A Wert zu dem �bergebenen Parameter
 // �ndert somit frequenz des timers
  void setTimer(int value){
	  OCR0A = value;
  }