/*
 * main.h
 *
 * Created: 30.05.2020 11:50:25
 *  Author: Sam Harjung, Jens Langkammerer , Sören Krüger
 
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>       // benötigt für uint8_t

#define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)

#define FOSC 16000000UL                       
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD -1

void init(){
	
	// Analogen Eingang initialisieren 
	ADMUX = 0;                //  ADC0 verwenden
	ADMUX |= (1 << REFS0);    //  AVcc als Referenz
	ADMUX &= ~(1 << ADLAR);   //  10 bit AUflösung 

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale für 16Mhz
	ADCSRA |= (1 << ADATE);   // Setze ADC Auto Trigger 
	
	ADCSRB = 0;               // 0 für "free running" Modus

	ADCSRA |= (1 << ADEN);    // ADC aktivieren
	ADCSRA |= (1 << ADIE);    // Interrupts aktivieren
	ADCSRA |= (1 << ADSC);    // Starte die ADC
	
	// Serielle Kommunikation initialisieren
	/*Setzte baud rate */
	UBRR0H = (MYUBRR >> 8);
	UBRR0L = MYUBRR;
	
	UCSR0B |= (1 << TXEN0);      // Übertragung aktivieren
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // setze frame: 8data, 1 stp
	
	sei();    // aktiviere interrupts

}





