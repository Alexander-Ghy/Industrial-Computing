/**
 * @file buttons.h
 * @author Alexander Ghyoot, Michal Kos
 * @date October 2021
 *
 * @brief Header file with declaration of public data types and variables for the buttons module.
 *
 *A header file to be to be used by a user to control the buttons on a msp432p401r Launchpad board.
 *The type button_val_t shows the state of the button, either pressed or released.
 *The type button_ref_t can be used to refer to one of the buttons on the board, either S1 or S2.
 *The public function buttons_init intializes the hardware for the buttons to be used.
 *The public function buttonGet() takes a button_ref_t parameter as input to return the state of this button.
 *The public function buttonsGetNum() returns an integer containing the amount of buttons on this board.
 *
 * @{
 */
#ifndef __BUTTONS_H
#define __BUTTONS_H

/* ---------------- #includes needed for this file ----------------- */
#include <stdint.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "common.h"

/* --------------------------- Public macros ----------------------------- */
/* ----------------------- Public data types ------------------------- */
    /* Enumeration of the status values of a button */
typedef enum button_val_e {BUTTON_PRESSED, BUTTON_RELEASED} button_val_t ;
    /* Enumeration of the buttons managed by the module.
    One value for each button (example with two buttons) */
typedef enum button_ref_e {
LP_S1 , /* LaunchPad , button S1 */
LP_S2 , /* LaunchPad , button S2 */
BP_S1 , /* BoosterPack , button S1 */
BP_S2 /* BoosterPack , button S2 */
} button_ref_t ;


/* ---- Declaration of public variables (no definition, use extern) ----- */

/* -------- Declaration of public functions (optional extern) ------------ */
void buttonsInit(void);
button_val_t buttonGet(button_ref_t button_ref);
int buttonsGetNum(void);
extern void buttonCallback(int button_index);

/* @} */

#endif // __BUTTONS_H
