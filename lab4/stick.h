/**
 * @file stick.h
 * @author Alexander Ghyoot, Michal Kos
 * @date January 2022
 *
 * @brief Header file with declaration of public data types and variables for the SysTick module.
 *
 * A header file to be to be used by the user to control the SysTick on a msp432p401r Launchpad board.
 *
 * @{
 */
#ifndef __STICK_H
#define __STICK_H

/* ---------------- #includes needed for this file ----------------- */

#include <stdint.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "common.h"

/* --------------------------- Public macros ----------------------------- */


/* ----------------------- Public data types ------------------------- */


/* ---- Declaration of public variables (no definition, use extern) ----- */


/* -------- Declaration of public functions (optional extern) ------------ */

// Start the timer by activating the bit ENABLE
void stickStart(void);
// Stop the timer by clearing the bit ENABLE
void stickStop(void);
// Determine if the timer is running by analyzing the bit ENABLE. Returns 1 if counting, 0 otherwise
uint32_t stickIsStarted(void);
// Enable timer interrupts by setting bit TICKINT
void stickEnableInt(void);
// Disable timer interrupts by clearing the bit TICKINT
void stickDisableInt(void);
// Determine if timer interrupts are enabled by analyzing the bit TICKINT.Returns 1 if enabled, 0 otherwise
uint32_t stickIsIntEnabled(void);
// Set the timer period by writing the value p - 1 on record STRVR
void stickSetPeriod(uint32_t p);
// Returns the timer period. Returns q + 1, being q the registry value STRVR
uint32_t stickGetPeriod(void);
// Current value of the timer. Returns c, being c the registry value STCVR
uint32_t stickGetCount(void);
// Clear the flag COUNTFLAG timer interrupt
void stickClearIntFlag(void);
// Determines if the timer interrupt flag is set by parsing the bit COUNTFLAG.Returns 1 if the flag is activated, 0 otherwise.
uint32_t stickIsIntFlagActive(void);
// Callback function called from the timer interrupt handler
extern void stickCallback (void);

/* @} */

#endif // __STICK_H
