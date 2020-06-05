/*
 * main.h
 *
 * Created: 01.06.2020 08:59:54
 * Author : Sam Harjung, Sören Krüger, Jens Langkammerer * Author : Sam Harjung, Sören Krüger, Jens Langkammerer
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)

// Richtungs Variable zeigt an in welche Richtung das Licht Läuft
bool direction = true;
// Schrittzähler bestimmt in welchem Status die Lichter sind
int stepCount = 0;


void init(){
	// Port B als Ausgang
	DDRB = 0xFF;
	 
	// Port B auf low setzen
	PORTB = 0x00;
	 
	// Timer1 initialiiseren
	// Wert wurde nicht durch ausrechnen ermittelt sondern so gewält das, dass Lauflicht cool aussieht
	OCR1A = 0x270;

	// Modus 4, CTC on OCR1A
	SET_BIT(TCCR1B,WGM12);

	//Interrupt bei Vergleichs Übereinstimmung (Compare match)
	SET_BIT(TIMSK1,OCIE1A);

	// Prescaler auf 1024 und Timer starten
	SET_BIT(TCCR1B,CS12); SET_BIT(TCCR1B,CS10) ;
	
	// Interrupts aktivieren
	sei();
}
 
// Setze je nach Wert des StepCounts das korrekte Licht auf an und die restlichen auf aus
void setLights(){
	if(stepCount == 0){
		PORTB = 0b100000;
	}
	else if( stepCount == 1){
		PORTB = 0b010000;
	}
	else if( stepCount == 2){
		PORTB = 0b001000;
	}
	else if( stepCount == 3){
		PORTB = 0b000100;
	}
	else if( stepCount == 4){
		PORTB = 0b000010;
	}
	else if( stepCount == 5){
		PORTB = 0b000001;
	}
	doStep();
	
}
  
// Erhöht bzw verringert den Schrittzähler
// Dreht am Anfang bzw Ende die Richtung um
void doStep(){
	if(stepCount == 0){
		direction = true;
		stepCount++;
	}
	else if(stepCount == 5){
		direction = false;
		stepCount--;
	}
	else if(direction){
		stepCount ++ ;
	}
	else{
		stepCount--;
	}
	return;
}