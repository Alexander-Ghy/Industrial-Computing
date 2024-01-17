/**
 * @file leds.h
 * @author Alexander Ghyoot, Michal Kos
 * @date October 2021
 *
 * @brief Header file with declaration of public data types and variables for the leds module.
 *
 * A header file to be to be used by the user to control the buttons on a msp432p401r Launchpad board.
 *The enum led_ref_t is used to determine the name of the led, ex. LED1.
 *The public function ledsInit() initializes the hardware to use the leds.
 *The public function ledOn and ledOff are used to turn on/off a led, this takes a led_ref_t type as parameter.
 *The public function ledToggle() can be used to toggle the state of a led, this takes a led_ref_t type as parameter.
 *The public function ledGet() returns the state of a led, either 1 (ON) or 0 (OFF), this takes a led_ref_t type as parameter.
 *The public functions ledsGetNum() return an integer value containing the amount of LEDS used in this implementation.
 *
 * @{
 */
#ifndef __LEDS_H
#define __LEDS_H

/* ---------------- #includes needed for this file ----------------- */
#include <stdint.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "common.h"

/* --------------------------- Public macros ----------------------------- */

/* ----------------------- Public data types ------------------------- */

/* ---- Declaration of public variables (no definition, use extern) ----- */
enum led_ref_e { LED1 , LED2 };
typedef enum led_ref_e led_ref_t ;

/* -------- Declaration of public functions (optional extern) ------------ */
void ledsInit(void);
void ledOn(led_ref_t led_ref);
void ledOff(led_ref_t led_ref);
void ledToggle(led_ref_t led_ref);
uint8_t ledGet(led_ref_t led_ref);
int ledsGetNum(void);

/* @} */

#endif // __LEDS_H
