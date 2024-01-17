/**
 * @file main.c
 * @author Michal Kos, Alexander Ghyoot
 * @date January 2022
 *
 * @brief Main file of Practica 5
 *
 * Main file containing the initialization of the leds module and timed delay module with an implementation of the
 * stimeCallback function.
 *
 * @{
 */

#include "leds.h"
#include "buttons.h"
#include "stime.h"


int main(void)
{
    WDT_A_holdTimer();      /* Stop watchdog timer */

    ledsInit();             /* Initialize all leds and turn them off */
    stimeInit(3000000);        /* Initialize the stime module for timed delay */

    stimeExecMillis(1000);  /* Initialize the stime module execution period for stimeCallabk */

    Interrupt_enableMaster();

    while(1){
        ledOn(LP_LED1);
        stimeWaitMillis(1000);
        ledOff(LP_LED1);
        stimeWaitMillis(2000);
    }
}

void stimeCallback(void){
    ledToggle(LP_LED2_RED);
    ledToggle(LP_LED2_GREEN);
    ledToggle(LP_LED2_BLU);
}

