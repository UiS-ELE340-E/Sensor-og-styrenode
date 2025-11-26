//
// Main program
// File: main.c
// m.t.150715

// Prosjektet saman med eit passande python-skript, gir ein dataloggar for tre 16-bits
// akselerasjonsdata med tidsreferanse
//---------------------------------------

//---------------------------------------
// Inclusions and definitions
//---------------------------------------
#include <cmsis_boot/stm32f30x.h>
#include <dekl_globale_variablar.h>
#include "stm32f3_discovery/stm32f3_discovery_lsm303dlhc.h"
#include <metodar/sensor_card.h>
#include <metodar/control_card.h>

//---------------------------------------
// Global variables
//---------------------------------------

//---------------------------------------
// Function prototypes
//---------------------------------------
void init(void);
void test_code(void);

//---------------------------------------
// Function definitions
//---------------------------------------
int main(void)  {
    init();

    while(node == 0) {
    	if (new_sample == 1) {
    		control_card_logic();
    		new_sample = 0;
    	}
    }
    while(node == 1) {
    	if  (new_sample == 1) {
    		sensor_card_logic();
    		new_sample = 0;
    	}
    }
}
