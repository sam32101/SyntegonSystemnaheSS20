/*
 * main.h
 *
 * Created: 30.05.2020 11:50:25
 *  Author: Sam Harjung, Jens Langkammerer , S�ren Kr�ger
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

//timer initialisieren
void initTimer(){
	// Jeden wert 1x Pro Sekunde auslesen = 2 Aktionen pro Sekunde
	// [ (16MHz / 256) * 0.5]-1 = 31249 = 7A11
	OCR1A = 0x7A11;
	
	TCCR1B |= (1 << WGM12);
	// Modus 4, CTC auf OCR1A
	
	TIMSK1 |= (1 << OCIE1A);
	//L�se Interupt bei Vergleichs�bereinstimmung ( compare match ) aus
	
	TCCR1B |= (1 << CS12);
	// prescaler auf 256 und timer starten
	
	sei();
	// interrupts aktivieren
	
}

// ADC f�r gegbenen Eingang durchf�hren (einmalig)
void ADCsingleREAD(uint8_t adctouse)
{
	
	int ADCval;

	ADMUX = adctouse;										// Benutze gegebnen analogen Eingang
	SET_BIT(ADMUX,REFS0);									// Benutze AVcc als Referenz
	SET_BIT(ADMUX,ADLAR);									// 8 Bit Aufl�sung
	
	SET_BIT(ADCSRA,ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale f�r 8Mhz
	SET_BIT(ADCSRA,ADEN);									// Aktiviere die ADC

	SET_BIT(ADCSRA,ADSC);									// Starte die ADC

	while(ADCSRA & (1 << ADSC));							// Warte bis ADC abgeschlossen ist

}




