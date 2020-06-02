/*
 * main.h
 *
 * Created: 01.06.2020 08:59:54
 * Author : Sam Harjung, S�ren Kr�ger, Jens Langkammerer * Author : Sam Harjung, S�ren Kr�ger, Jens Langkammerer
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^=(1<<BIT)

#define FOSC 16000000UL                       // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD -1

// Richtungs variable zeigt an in welche richtung das Licht L�uft
bool direction = true;
// Schrittz�hler bestimmt in welchem Status die Lichter sind
int stepCount = 0;


 void init(){
	 // Port B als Ausgang
	 DDRB = 0xFF;
	 DDRB = 0x00;
	 
	 // timer1 initialiiseren
	 // Wert wurde nicht durch ausrechnen ermittelt sondern so gew�lt das, dass Lauflicht cool aussieht
	 OCR1A = 0x270;

	 // Modus 4, CTC on OCR1A
	 TCCR1B |= (1 << WGM12);

	 //Intterrupt bei Vergleichs �bereinstimmung (Compare match)
	 TIMSK1 |= (1 << OCIE1A);

	 // Prescaler auf 1024 und Timer starten
	 TCCR1B |= (1 << CS12) | (1 << CS10);

	// Interrupts aktivieren
	 sei();
	 
 }
 
 // setzte je nach wert des StepCounts das korrekte licht auf an und die restelichen aus
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
  
  // Erh�ht bzw verringert den Schrittz�hler
  // dreht am Anfang bzw Ende die Richtung um
  void doStep(){
	  if(stepCount == 0){
		  if(!direction){
			  direction = true;
		  }
		  stepCount++;
	  }
	  else if(stepCount == 5){
		  if(direction){
			  direction = false;
		  }
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