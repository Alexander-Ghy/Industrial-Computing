/**
 * @file main.c
 * @author Michal Kos, Alexander Ghyoot
 * @date October 2021
 *
 * @brief Main file of Practica 3
 *
 * Main file containing the initialization and a while loop that implements polling of button S1 for LED1 toggle.
 *
 * @{
 */

#include "leds.h"
#include "buttons.h"
#include "servo.h"


int main(void)
{
    WDT_A_holdTimer();      /* Stop watchdog timer */

    //buttonsInit();          /* Initialize all buttons */
    //ledsInit();             /* Initialize all leds and turn them off */

    Interrupt_enableMaster();

    servoInit();

    while (1)
    {
        int i;
        for(i=100000; i>0; i--);
        servoSetAbsPosition(0);
        for(i=100000; i>0; i--);
        servoSetAbsPosition(180);
    }
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

