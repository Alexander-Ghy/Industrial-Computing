/**
 * @file stime.c
 * @author Alexander Ghyoot, Michal Kos
 * @date January 2022
 *
 * @brief A source file for the current instant of time module.
 *
 * A source file to be to be used by the user to control the current instant of time on a msp432p401r Launchpad board.
 * This contains the implementation for the private and public functions for the current instant of time module.
 *
 * @{
 */

/* ---------------- #includes needed for this file ----------------- */
#include "stime.h"

/* --------------------------- Private macros ----------------------------- */


/* ----------------------- Private data types ------------------------- */


/* ----------- Definition of private variables (with static) -------------- */

// Number of milliseconds elapsed since initialization
uint64_t ms;

/* ----------------- Definition of public variables --------------------- */


/* ---------- Declaration of private functions (with static) -------------- */


/* --------- Implementation of private functions (with static) ------------ */

void stickCallback(void){
    ms++;
}

/* ---------------- Implementation of public functions ------------------ */

void stimeInit(uint32_t clkHz){
    ms = 0;
    stickStop();
    stickClearIntFlag();
    stickSetPeriod(clkHz/1000);
    stickEnableInt();
    stickStart();
}

uint64_t stimeElapsedMillis(void){
    uint64_t millis;
    stickDisableInt();
    millis = ms;
    stickEnableInt();
    return millis;
}

void stimeWaitMillis(uint32_t millis){
    uint64_t t0, k;
    t0 = stimeElapsedMillis();
    k = t0 + millis;
    do{}while(k > stimeElapsedMillis());
}


/* @} */
