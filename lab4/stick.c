/**
 * @file stick.c
 * @author Alexander Ghyoot, Michal Kos
 * @date January 2022
 *
 * @brief A source file for the SysTick module.
 *
 * A source file to be to be used by the user to control the SysTick timer on a msp432p401r Launchpad board.
 * This contains the implementation for the private and public functions for the SysTick module.
 *
 * @{
 */

/* ---------------- #includes needed for this file ----------------- */
#include "stick.h"

/* --------------------------- Private macros ----------------------------- */


/* ----------------------- Private data types ------------------------- */


/* ----------- Definition of private variables (with static) -------------- */


/* ----------------- Definition of public variables --------------------- */


/* ---------- Declaration of private functions (with static) -------------- */

void SysTick_Handler(void);

/* --------- Implementation of private functions (with static) ------------ */

void SysTick_Handler(void){
    stickClearIntFlag();
    stickCallback();
}

void stickCallback (void) __attribute__((weak));

/* ---------------- Implementation of public functions ------------------ */

void stickStart(void){
    SysTick->CTRL |= (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk);
}

void stickStop(void){
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

uint32_t stickIsStarted(void){
    return (SysTick->CTRL & SysTick_CTRL_ENABLE_Msk) >> SysTick_CTRL_ENABLE_Pos;
}

void stickEnableInt(void){
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}

void stickDisableInt(void){
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

uint32_t stickIsIntEnabled(void){
    return (SysTick ->CTRL & SysTick_CTRL_TICKINT_Msk) >> SysTick_CTRL_TICKINT_Pos;
}

void stickSetPeriod(uint32_t p){
    SysTick->LOAD = ((p - 1) & SysTick_LOAD_RELOAD_Msk);
}

uint32_t stickGetPeriod(void){
    return ((SysTick->LOAD & SysTick_LOAD_RELOAD_Msk) + 1);
}

uint32_t stickGetCount(void){
    return (SysTick->VAL & SysTick_VAL_CURRENT_Msk);
}

void stickClearIntFlag(void){
    SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk;
}

uint32_t stickIsIntFlagActive(void){
    return (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) >> SysTick_CTRL_COUNTFLAG_Pos;
}

/* @} */
