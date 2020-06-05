/*
 * main.h
 *
 * Created: 30.05.2020 11:50:25
 *  Author: Sam Harjung, Jens Langkammerer , Sören Krüger
  
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>       // needed for uint8_t

#define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)

#define FOSC 16000000UL                       // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD -1

// serielle Kommunikation initialisieren
void initSerial(){
	
	// serielle Kommunikation initialisieren
	/*Setze baud rate */
	UBRR0H = (MYUBRR >> 8);
	UBRR0L = MYUBRR;
	
	UCSR0B |= (1 << TXEN0);      // Aktiviere transmitter
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // definiere frame: 8data, 1 stp
	
}

// ADC für gegbenen Eingang durchführen (einmalig)
void ADCsingleREAD(uint8_t adctouse)
{
	int ADCval;

	ADMUX = adctouse;         // Benutze gegebnen analogen Eingang
	ADMUX |= (1 << REFS0);    // Benutze AVcc als Referenz
	ADMUX |= (1 << ADLAR);    // 8 Bit Auflösung
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale für 8Mhz
	ADCSRA |= (1 << ADEN);    // Aktiviere die ADC

	ADCSRA |= (1 << ADSC);    // Starte die ADC

	while(ADCSRA & (1 << ADSC));      //warte bis ADC abgeschlossen ist

}




