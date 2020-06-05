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

// Serielle Kommunikation initialisieren
void initSerial(){
	
	// serielle Kommunikation initialisieren
	// Setze baud rate
	UBRR0H = (MYUBRR >> 8);
	UBRR0L = MYUBRR;
	
	SET_BIT(UCSR0B,TXEN0);									// Aktiviere transmitter
	SET_BIT(UCSR0C,UCSZ01) | (1 << UCSZ00);					// Definiere frame: 8data, 1 stp
	
}

// ADC für gegbenen Eingang durchführen (einmalig)
void ADCsingleREAD(uint8_t adctouse)
{
	
	int ADCval;

	ADMUX = adctouse;										// Benutze gegebnen analogen Eingang
	SET_BIT(ADMUX,REFS0);									// Benutze AVcc als Referenz
	SET_BIT(ADMUX,ADLAR);									// 8 Bit Auflösung
	
	SET_BIT(ADCSRA,ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale für 8Mhz
	SET_BIT(ADCSRA,ADEN);									// Aktiviere die ADC

	SET_BIT(ADCSRA,ADSC);									// Starte die ADC

	while(ADCSRA & (1 << ADSC));							// Warte bis ADC abgeschlossen ist

}




