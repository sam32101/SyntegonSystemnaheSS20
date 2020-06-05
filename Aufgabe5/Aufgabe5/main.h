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
	ADMUX = 0;												//  ADC0 als Input verwenden
	SET_BIT(ADMUX,REFS0);									//  AVcc als Referenz Spannung
	CLEAR_BIT(ADMUX,ADLAR);									//  10 bit AUfl�sung

	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS0);									// 128 prescaler f�r 16Mhz
	
	SET_BIT(ADCSRA,ADATE);									// Setze ADC Auto Trigger  (um freerunning Modus verwenden zu k�nnen)

	ADCSRB = 0;												// "free running" Modus ( durchgehende Umwandlung)

	SET_BIT(ADCSRA,ADEN);									// ADC aktivieren
	SET_BIT(ADCSRA,ADIE);									// Interrupts aktivieren
	SET_BIT(ADCSRA,ADSC);									// Starte die ADC

	// Serielle Kommunikation initialisieren
	// Setzte baud rate
	UBRR0H = (MYUBRR >> 8);									// obere 4 bits
	UBRR0L = MYUBRR;										// untere 4 bits

	SET_BIT(UCSR0B,TXEN0);									// �bertragung aktivieren
	
	SET_BIT(UCSR0C,UCSZ01);
	SET_BIT(UCSR0C, UCSZ00);								// frame definieren: 8data, 1 stp

	sei();													// aktiviere interrupts

}
