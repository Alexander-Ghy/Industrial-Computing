/**
 * @file main.c
 * @author Michal Kos, Alexander Ghyoot
 * @date October 2021
 *
 * @brief Main file of Practica 1
 *
 * Main file containing the initialization and a while loop that implements polling of button S1 for LED1 toggle.
 *
 * @{
 */

#include "leds.h"
#include "buttons.h"


int main(void)
{
    WDT_A_holdTimer();      /* Stop watchdog timer */

    buttonsInit();
    ledsInit();

    button_ref_t currentButStateS1;
    button_ref_t previousButStateS1 = buttonGet(S1);

    while (1)
    {
        currentButStateS1 = buttonGet(S1);
        if ((currentButStateS1 == BUTTON_PRESSED) && (previousButStateS1 == BUTTON_RELEASED))
        {
            ledToggle(LED1);
        }
        previousButStateS1 = currentButStateS1;
    }
}

