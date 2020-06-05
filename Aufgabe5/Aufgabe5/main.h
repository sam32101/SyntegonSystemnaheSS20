/*
 * main.h
 *
 * Created: 30.05.2020 11:50:25
 *  Author: Sam Harjung, Jens Langkammerer , S�ren Kr�ger
 
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>       // ben�tigt f�r uint8_t

#define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)

#define FOSC 16000000UL                       
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD -1

void init(){
	
	// Analogen Eingang initialisieren 
	ADMUX = 0;                //  ADC0 als Input verwenden
	ADMUX |= (1 << REFS0);    //  AVcc als Referenz Spannung
	ADMUX &= ~(1 << ADLAR);   //  10 bit AUfl�sung 

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescaler f�r 16Mhz
	ADCSRA |= (1 << ADATE);   // Setze ADC Auto Trigger  (um freerunning Modus verwenden zu k�nnen)
	
	ADCSRB = 0;               // "free running" Modus ( durchgehende Umwandlung)

	ADCSRA |= (1 << ADEN);    // ADC aktivieren
	ADCSRA |= (1 << ADIE);    // Interrupts aktivieren
	ADCSRA |= (1 << ADSC);    // Starte die ADC
	
	// Serielle Kommunikation initialisieren
	//Setzte baud rate 
	UBRR0H = (MYUBRR >> 8); // obere 4 bits
	UBRR0L = MYUBRR;		// untere 4 bits
	
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // frame definieren: 8 bit char gr��e, 1 stp
	UCSR0B |= (1 << TXEN0);      // transmitter aktivieren
	
	sei();    // aktiviere interrupts
 
}





