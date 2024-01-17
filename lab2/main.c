/**
 * @file main.c
 * @author Michal Kos, Alexander Ghyoot
 * @date October 2021
 *
 * @brief Main file of Practica 2
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

    buttonsInit();          /* Initialize all buttons */
    ledsInit();             /* Initialize all leds and turn them off */

    button_ref_t currentButStateLP_S1;
    button_ref_t previousButStateLP_S1 = buttonGet(LP_S1);

    button_ref_t currentButStateLP_S2;
    button_ref_t previousButStateLP_S2 = buttonGet(LP_S2);

    button_ref_t currentButStateBP_S1;
    button_ref_t previousButStateBP_S1 = buttonGet(BP_S1);

    button_ref_t currentButStateBP_S2;
    button_ref_t previousButStateBP_S2 = buttonGet(BP_S2);

    while (1)
    {
        currentButStateLP_S1 = buttonGet(LP_S1);
        if ((currentButStateLP_S1 == BUTTON_PRESSED) && (previousButStateLP_S1 == BUTTON_RELEASED))
        {
            led_ref_t led;
            for (led = LP_LED1 ; led <= BP_LED1_BLU ; ++led){
                ledOn(led);
            }
        }
        previousButStateLP_S1 = currentButStateLP_S1;


        currentButStateLP_S2 = buttonGet(LP_S2);
        if ((currentButStateLP_S2 == BUTTON_PRESSED) && (previousButStateLP_S2 == BUTTON_RELEASED))
        {
            led_ref_t led;
            for (led = LP_LED1 ; led <= BP_LED1_BLU ; ++led){
                ledOff(led);
            }
        }
        previousButStateLP_S2 = currentButStateLP_S2;


        currentButStateBP_S1 = buttonGet(BP_S1);
        if ((currentButStateBP_S1 == BUTTON_PRESSED) && (previousButStateBP_S1 == BUTTON_RELEASED))
        {
            led_ref_t led;
            for (led = LP_LED1 ; led <= LP_LED2_BLU ; ++led){
                ledToggle(led);
            }
        }
        previousButStateBP_S1 = currentButStateBP_S1;


        currentButStateBP_S2 = buttonGet(BP_S2);
        if ((currentButStateBP_S2 == BUTTON_PRESSED) && (previousButStateBP_S2 == BUTTON_RELEASED))
        {
            led_ref_t led;
            for (led = BP_LED1_RED ; led <= BP_LED1_BLU ; ++led){
                ledToggle(led);
            }
        }
        previousButStateBP_S2 = currentButStateBP_S2;
    }
}

