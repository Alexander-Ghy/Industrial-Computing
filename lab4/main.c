/**
 * @file main.c
 * @author Michal Kos, Alexander Ghyoot
 * @date January 2022
 *
 * @brief Main file of Practica 4
 *
 * Main file containing the initialization and a while loop that implements timed delay using the timer module.
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
    stimeInit(3000000);            /* Initialize the stime module for timed delay */

    Interrupt_enableMaster();

    while(1){
        ledOn(LP_LED1);
        stimeWaitMillis(1000);
        ledOff(LP_LED1);
        stimeWaitMillis(2000);
    }
}

