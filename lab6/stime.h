/**
 * @file stime.h
 * @author Alexander Ghyoot, Michal Kos
 * @date January 2022
 *
 * @brief Header file with declaration of public data types and variables for the the current instant of time module.
 *
 * A header file to be to be used by the user to control the current instant of time on a msp432p401r Launchpad board.
 *
 * @{
 */
#ifndef __STIME_H
#define __STIME_H

/* ---------------- #includes needed for this file ----------------- */

#include <stdint.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "common.h"
#include "stick.h"

/* --------------------------- Public macros ----------------------------- */


/* ----------------------- Public data types ------------------------- */


/* ---- Declaration of public variables (no definition, use extern) ----- */


/* -------- Declaration of public functions (optional extern) ------------ */

// Initialize the module
void stimeInit(uint32_t clkHz);
// Returns the milliseconds elapsed since the module initialization
uint64_t stimeElapsedMillis(void);
// Timed wait of the indicated milliseconds
void stimeWaitMillis(uint32_t millis);
// Sets the execution period of the function stimeCallback ()
void stimeExecMillis (uint32_t millis);
// Callback function called from the stickCallback
extern void stimeCallback(void);


/* @} */

#endif // __STIME_H
