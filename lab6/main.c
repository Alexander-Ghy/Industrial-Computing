/**
 * @file main.c
 * @author Michal Kos, Alexander Ghyoot
 * @date January 2022
 *
 * @brief Main file of Practica 5
 *
 * Main file containing the initialization of the leds and the time module together with the callback function from the buttons module.
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
    buttonsInit();

    Interrupt_enableMaster();

}

void buttonCallback(int button_index)
{
    if(button_index == BP_S1){
        ledToggle(LP_LED1);
    }
    else if(button_index == BP_S2){
        ledToggle(LP_LED1);
    }
}

