/*
 * Aufgabe2.c
 *
 * Created: 31.05.2020 10:03:27
 * Author : Sam Harjung, Sören Krüger, Jens Langkammerer
 */ 

#include <avr/io.h>
#include "main.h"
#include <avr/interrupt.h>s

// Aufgabenbeschreibung: Ampelschaltung mit drei LEDs: Zunächst leuchtet die rote LED 1000 ms, danach rot-gelb 100ms, grün 1000 ms und gelb 100ms. Danach beginnt er Zyklus von Vorne.

// Vom Timer ausgelöster Interrupt, wird alle 100ms aufgerufen
ISR (TIMER1_COMPA_vect)
{
	step();
}

int main(void)
{
   init(); // initialisieren 
   while (1);
}

